/*!
* \file FactorySQL.cpp
* \brief Fichier contenant l'implémentation de la classe FactorySQL
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "FactorySQL.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
FactorySQL::FactorySQL() {};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FactorySQL::~FactorySQL() {};

//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouveau Film
*/
shared_ptr<Video> FactorySQL::generateMedia(string titre, string lien, int annee, string affiche, string synopsis) {
	shared_ptr<Video> nouveauFilm (new Film(titre, lien, annee, affiche, synopsis));
	//ajouter les acteurs & réalisateurs
	return nouveauFilm;
}

//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouvel Episode
*/
shared_ptr<Video> FactorySQL::generateMedia(string titre, string lien, int annee, int numero, int saison, string serie, string synopsis) {
	shared_ptr<Video> nouvelEpisode (new Episode(titre, lien, annee, affiche, numero, saison, serie, synopsis));
	//ajouter les acteurs & réalisateurs
	return nouvelEpisode;
}

