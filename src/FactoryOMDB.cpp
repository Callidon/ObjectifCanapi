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
* \brief Méthode créant et retournant un shared_ptr vers une nouvelle Video
* \return Un shared_ptr<Video> qui pointe sur la video nouvellement crée
*/
shared_ptr<Video> FactoryOMDB::genererVideo(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real) {
	shared_ptr<Film> nouveauFilm (new Film(id, titre, lien, annee, affiche, synopsis, acteurs, real));
	return nouveauFilm;
}


//--------------------------------------------------
/*!
* \brief Méthode retournant la liste de tous les films contenus dans la base de données
* \return Un vector de shared_ptr<Video> qui contient  tous les films contenus dans la base de données
*/
vector<shared_ptr<Video> > FactoryOMDB::recupererAllFilms() {
	vector<shared_ptr<Video> > result;
//	//on sélectionne tous les films contenus dans la base via une requête sql
//	string sql = "SELECT * FROM Films";
//	vector<vector< string> > films = bd->query(sql);
	//on parcours la liste des films et on les ajoute à la liste de réponse
//	for(const auto &film: films) {
//		result.push_back(this->genererFilm(film[0], film[1], film[2], atoi(film[3].c_str()), film[4], film[5]));
//	}
	//on retourne le résultat
	return result;
}

//--------------------------------------------------
/*!
* \brief Méthode retournant la liste de tous les épisodes contenus dans la base de données
* \return Un vector de shared_ptr<Video> qui contient  tous les épisodes contenus dans la base de données
*/
vector<shared_ptr<Video> > FactoryOMDB::recupererAllEpisodes() {
	vector<shared_ptr<Video> > result;
	//on sélectionne tous les épisodes contenus la base via une requête sql
//	string sql = "SELECT * FROM Episodes";
//	vector<vector< string> > episodes = bd->query(sql);
	//on parcours la liste des épisodes et on les ajoute à la liste de réponse
//	for(const auto &episode: episodes) {
//		result.push_back(this->genererEpisode(episode[0], episode[1], episode[2], atoi(episode[3].c_str()), atoi(episode[4].c_str()), atoi(episode[5].c_str()), episode[6], episode[7]));
//	}
	//on retourne le résultat
	return result;
}


//--------------------------------------------------
/*!
* \brief Méthode affectuant une rechercher par titre de film
*/
string FactoryOMDB::queryTitle(string title){
	FILE *fp=popen((char*)("wget --quiet -O - \"http://www.omdbapi.com/?t=" + title + "\"").c_str(), "r");
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
* \brief Méthode permettant de creer un objet film/episode en fonction du resultat de la requete
*/
shared_ptr<Video> FactoryOMDB::makeFilm(string res){
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
		//system((char*)("firefox " + lien).c_str());
		
		return genererVideo(id, titre, lien, annee, affiche, synopsis, acteurs, real);
			
	}
}

