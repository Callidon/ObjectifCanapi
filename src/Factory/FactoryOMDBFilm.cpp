/*!
* \file FactoryOMDBFilm.cpp
* \brief Fichier contenant l'implémentation de la classe FactoryOMDBFilm
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#include "FactoryOMDBFilm.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
FactoryOMDBFilm::FactoryOMDBFilm() {};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FactoryOMDBFilm::~FactoryOMDBFilm() {};


//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouveau film
* \param id L'identifiant du film
* \param titre Le titre du film
* \param lien Le lien vers la bande-annonce
* \param annee L'année du film
* \param affiche Le lien vers l'affiche
* \param synopsis Le synopsis du film
* \param acteurs vector contenant les acteurs du film
* \param real vector contenant les réalisateurs du film
* \param pays Pays associé au film
* \return Un shared_ptr<Film> qui pointe sur le film nouvellement crée
*/
shared_ptr<Film> FactoryOMDBFilm::genererFilm(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays) {
	shared_ptr<Film> nouveauFilm (new Film(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays));
	return nouveauFilm;
}

//--------------------------------------------------
/*!
* \brief Méthode affectuant une recherche par titre de film
* \param title Titre du film à rechercher sur OMDB
* \return Le resultat de la requête
*/
string FactoryOMDBFilm::queryTitle(string title){
	FILE *fp;
	//Lance la requete OMDB
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
* \brief Méthode permettant de creer un objet film en fonction du resultat de la requete
* \param title Le titre du film à créer depuis OMDB
* \return Un shared_ptr vers le film crée 
*/
shared_ptr<Video> FactoryOMDBFilm::makeVideo(string title){
	string res = queryTitle(title);
	//si le film pas trouvé/pas dans le BD
	if(res.substr(13,5) == "False"){
		cout << "Film non trouvé" << endl;
		throw -1;
	}
	//sinon, on sépare les données pour correspondre aux attributs de film
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
		
		//appele la création de film
		return genererFilm(id, titre, lien, annee, affiche, synopsis, acteurs, real, pays);
	}
}
