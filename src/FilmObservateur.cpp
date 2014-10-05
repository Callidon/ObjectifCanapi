/*!
* \file FilmObservateur.cpp
* \brief Fichier contenant l'implémentation de la classe FilmObservateur
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "FilmObservateur.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
FilmObservateur::FilmObservateur(BDConnector * base) {
	db = base;
};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FilmObservateur::~FilmObservateur() {
	//désallouer db ?
};

//--------------------------------------------------
/*!
* \brief Méthode mettant à jour les informations de la base de données avec le film passé en paramètre
*/
void FilmObservateur::notifier(Video video) {

}


