/*!
* \file FactoryOMDBSerie.cpp
* \brief Fichier contenant l'implémentation de la classe FactoryOMDBSerie
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#include "FactoryOMDBSerie.hpp"
#include "FactoryOMDBFilm.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
FactoryOMDBSerie::FactoryOMDBSerie() {};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FactoryOMDBSerie::~FactoryOMDBSerie() {};

//--------------------------------------------------
/*!
* \brief Méthode affectuant une recherche par titre de série
* \param title Titre de la série à rechercher sur OMDB
* \return Le resultat de la requête
*/
string FactoryOMDBSerie::queryTitle(string title){
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
* \brief Méthode permettant de creer un objet série en fonction du resultat de la requete
* \param title Le titre de la série à créer depuis OMDB
* \return Un shared_ptr vers la série crée 
*/
shared_ptr<Video> FactoryOMDBSerie::makeVideo(string title){
	
	//Factory pour instancier des films à partir d'omdb
	shared_ptr<FactoryOMDB> factoryFilm (new FactoryOMDBFilm());
	
	shared_ptr<Film> fserie = dynamic_pointer_cast<Film>(factoryFilm->makeVideo(title));
	shared_ptr<Serie> serie = fserie->filmToSerie();
	
	shared_ptr<Film> ep;
	shared_ptr<Episode> epi;
	
	string liste = queryTitle(serie->getTitre());
	
	string episode;
	int i = 0, j=0;
	int posd,posf,size;
	string find, titre, numero, season;
	int saison, num;
	string sep = "}";
	cout << "Recupération des données..... veuillez patienter et l'attente en vaut la peine" << endl;
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
			try{
				ep = dynamic_pointer_cast<Film>(factoryFilm->makeVideo(titre));
			}
			catch(int code){
				//cerr << "Exception " << code << endl;
			}
			epi = ep->filmToEpisode();
			epi->setSaison(saison);
			epi->setNumero(num);
			serie->addEpisode(epi);
			
		}
		i = j + 1;
	}
	return serie;
}
