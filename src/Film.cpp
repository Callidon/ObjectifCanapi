/*!
* \file Film.cpp
* \brief Fichier contenant l'implémentation de la classe Film
* \author Camille Le LUët
* \author Thomas Minier
* \date ?
*/
#include "Film.hpp"
#include <iostream>
using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Film::Film(string titre, string lien, int annee, string affiche, Observateur obs, string synopsis) {
	Video::Video(titre, lien, synopsis, annee, obs);
	this->affiche = affiche;
	this->vu = false;
	this->aVoir = false;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Film::~Film() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le statut du film ("a voir" ou "vu")
*/
string Film::getStatut(){
	if(this->vu){
		return("Film vu");
	}
	else if(this->aVoir){
		return("Film à voir");
	}
	else {
		return("aucun marquage");
	}
}



//--------------------------------------------------
/*!
* \brief Méthode qui retourne l'affiche du film 
* gerer l'affichage de l'affiche à l'appel de cette méthode
*/
string Film::getAffiche(){
	return this->affiche;
}



//--------------------------------------------------
/*!
* \brief Méthode qui modifie le lien de l'affiche
*/
void Film::setAffiche(string aff){
	this->affiche = aff;
}
