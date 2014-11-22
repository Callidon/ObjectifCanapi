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
* \param
* \param suiv Pointeur vers le responsable suivant
*/
Responsable::Responsable(shared_ptr<BDConnector> db, shared_ptr<Responsable> suiv) {
	this->database = db;
	this->suivant = suiv;
	comportement = 0; //le comportement est indéfini par défaut
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Responsable::~Responsable() {}

//--------------------------------------------------
/*!
* \brief Méthode passant l'objet Video au responsable suivant
* \param video shared_ptr de l'objet Video à transmettre
*/
void Responsable::passerAuSuivant(shared_ptr<Video> video, bool vu, bool aVoir) {
	//si le pointeur vers le responsable suivant existe
	if(suivant != 0) {
		this->suivant->traiter(video, vu, aVoir);
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui définit kle comportement utilisé par le Responsable et ses successeurs pour traiter les objets
* \param comp shared_ptr vers le comportement à utiliser
*/
void Responsable::setComportement(std::shared_ptr<ComportementBD> comp) {
	
	//on set le comportement
	comportement = comp;
	
	//si le responsable a un successeur, on set aussi le comportement de ce successeur
	if(suivant != 0) {
		suivant->setComportement(comp);
	}
}

//--------------------------------------------------
/*!
* \brief Accesseur qui renvoie le comportement utiliser par le responsable pour traiter les objets
* \return shared_ptr vers le comportement utilisé par le responsable
*/
shared_ptr<ComportementBD> Responsable::getComportement() {
	return comportement;
}
