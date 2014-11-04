/*!
* \file FactoryOMDB.cpp
* \brief Fichier contenant l'implémentation de la classe FactoryOMDB
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "FactoryOMDB.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
FactoryOMDB::FactoryOMDB(shared_ptr<BDConnector> base): bd(base) {};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FactoryOMDB::~FactoryOMDB() {};


//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouveau film
* \return Un shared_ptr<Film> qui pointe sur le film nouvellement crée
*/
shared_ptr<Film> FactoryOMDB::genererFilm(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays) {
	shared_ptr<Film> nouveauFilm (new Film(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays));
	return nouveauFilm;
}

shared_ptr<Episode> FactoryOMDB::genererEpisode(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays) {
	shared_ptr<Episode> nouveauFilm (new Episode(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays));
	return nouveauFilm;
}

shared_ptr<Serie> FactoryOMDB::genererSerie(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays) {
	shared_ptr<Serie> nouveauFilm (new Serie(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays));
	return nouveauFilm;
}

//--------------------------------------------------
/*!
* \brief Méthode affectuant une recherche par titre de film
*/
string FactoryOMDB::queryTitle(string title){
	FILE *fp;
	fp=popen((char*)("wget --quiet -O - \"http://www.omdbapi.com/?t=" + title + "\"").c_str(), "r");
	char buffer[128];
	string res = "";
	while(!feof(fp)){
		if(fgets(buffer, 128, fp) != NULL){
			res += buffer;
		}
	}
	pclose(fp);
    return res;
}

//--------------------------------------------------
/*!
* \brief Méthode affectuant une recherche par titre de film
*/
string FactoryOMDB::querySerie(string title){
	FILE *fp;
	fp=popen((char*)("wget --quiet -O - \"http://imdbapi.poromenos.org/js/?name=" + title + "\"").c_str(), "r");
	char buffer[128];
	string res = "";
	while(!feof(fp)){
		if(fgets(buffer, 128, fp) != NULL){
			res += buffer;
		}
	}
	pclose(fp);
	
	string find = "\"episodes\":";
	int size = find.size();
	int posd = res.find(find) + size + 1;
	int posf = res.find("}]", posd);
	return res.substr(posd, posf - posd);
	
}


//--------------------------------------------------
/*!
* \brief Méthode permettant de creer un objet film/episode en fonction du resultat de la requete
*/
shared_ptr<Video> FactoryOMDB::makeVideo(string res, string type){
	if(res.substr(13,5) == "False"){
		cout << "Film non trouvé" << endl;
	}
	else {
		string separateur = "\","; string find; int size; int posd; int posf;
		vector<string> real;
		vector<string> acteurs;
		
		find = "\"Title\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string titre = res.substr(posd, posf - posd);
		
		find = "\"Year\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string year = res.substr(posd, posf - posd);
		int annee = atoi((char*)year.c_str());
		
		find = "\"Director\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		real.push_back(res.substr(posd, posf - posd));
		
		find = "\"Actors\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string listActors = res.substr(posd, posf - posd);
		int i = 0, j=0;
		string sep = ", ";
		while(i<listActors.size() && j!= -1){
			j = listActors.find(sep, i);
			//cout << j << endl;
			acteurs.push_back(listActors.substr(i, j - i));
			i = j + 2;
		}
		
		find = "\"Plot\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string synopsis = res.substr(posd, posf - posd);
		
		
		find = "\"Country\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string pays = res.substr(posd, posf - posd);
		
		find = "\"Poster\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string affiche = res.substr(posd, posf - posd);
		//system((char*)("firefox " + affiche).c_str());
		
		find = "\"imdbID\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string id = res.substr(posd, posf - posd);
		
		find = "\"Type\":";
		size = find.size();
		posd = res.find(find) + size + 1;
		posf = res.find(separateur, posd);
		string type = res.substr(posd, posf - posd);
		
		string titreLien = titre;
		i = 0; j = 0;
		while(i<titreLien.size() && j!= -1){
			j = titreLien.find(" ", i);
			titreLien[j] = '+';
			i = j + 2;
		}
		string lien = "https://www.youtube.com/results?search_query=" + titreLien + "+trailer";
		
		if(type=="Film"){
			return genererFilm(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays);
		} else if(type=="Serie"){
			return genererSerie(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays);
		} else if(type=="Episode"){
			return genererEpisode(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays);
		}
	}
}

//--------------------------------------------------
/*!
* \brief Méthode permettant de creer un objet film/episode en fonction du resultat de la requete
*/
shared_ptr<Serie> FactoryOMDB::makeSerie(string res){
	shared_ptr<Video> serie = makeVideo(res, "Serie");
	shared_ptr<Video> ep;
	string liste = querySerie(serie->getTitre());
	
	string episode;
	int i = 0, j=0;
	int posd,posf,size;
	string find, titre, numero, season;
	int saison, num;
	string sep = "}";
	while(i<liste.size() && j!= -1){
		j = liste.find(sep, i);
		episode = liste.substr(i, j - i);

		find = "\"season\":";
		size = find.size();
		posd = episode.find(find) + size + 1;
		posf = episode.find(", \"", posd);
		if(posd != -1 && posf != -1){
			season = episode.substr(posd, posf - posd);
			saison = atoi((char*)season.c_str());
		}

		find = "\"name\":";
		size = find.size();
		posd = episode.find(find) + size + 2;
		posf = episode.find(", \"", posd);
		if(posd != -1 && posf != -1){
			titre = episode.substr(posd, posf - posd - 1);
		}

		find = "\"number\":";
		size = find.size();
		posd = episode.find(find) + size + 1;
		posf = episode.size();
		if(posd != -1 && posf != -1){
			numero = episode.substr(posd, posf - posd);
			num = atoi((char*)numero.c_str());
		}
		if(titre != ("Episode #"+season+"."+numero)){
			ep = makeVideo(queryTitle(titre), "Episode");
			//cout << ep->getTitre() << endl
			//ep->setSaison(saison);
			//ep->setNumero(num);
			//cout << ep->getSaison() << "x" << ep->getNumero() << " : " << ep->getTitre() << endl;
		}
		i = j + 1;
	}
	//converson de serie en pointeur de Video vers Serie
	shared_ptr<Serie> ptrSerie(dynamic_pointer_cast<Serie>(serie));
	return ptrSerie;
}

