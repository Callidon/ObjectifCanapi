/*!
* \file Film.cpp
* \brief Fichier contenant l'implémentation de la classe Film
* \author Camille Le Luët
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
Film::Film(string id, string titre, string lien, int annee, string affiche, string synopsis):Video(id, titre, lien, synopsis, annee) {
	this->affiche = affiche;
}

Film::Film(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real):Video(id, titre, lien, synopsis, annee, acteurs, real) {
	this->affiche = affiche;
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
