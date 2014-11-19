/*!
* \file Responsable.cpp
* \brief Fichier contenant l'implémentation de la classe Responsable
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "Responsable.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
* \param suiv Pointeur vers le responsable suivant
*/
Responsable::Responsable(shared_ptr<BDConnector> db, shared_ptr<Video> suiv) {
	this->database = db;
	this->suivant = suiv;
}

Responsable::~Responsable() {}

void Responsable::passerAuSuivant(shared_ptr<Video> video) {
	this->suivant->traiter(video);
}
