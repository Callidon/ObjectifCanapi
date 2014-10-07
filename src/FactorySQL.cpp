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
* \brief Méthode générant des trucs (à préciser)
*/
Video * FactorySQL::generateMedia(list<string> listeParams, string typeVideo) {
	Video * media;
	//si c'est un film que l'on doit instancier
	if(typeVideo == "Film") {
		media = new Film(...);
	} else if(typeVideo == "Episode") { //sinon, si c'est un épisode
		media = new Episode(...);
	} else { //sinon, on retourne le pointeur vers un objet vide
		return media;
	}
}

