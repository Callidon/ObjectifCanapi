/*!
* \file Serie.cpp
* \brief Fichier contenant l'implémentation de la classe Serie
* \author Camille Le LUët
* \author Thomas Minier
* \date ?
*/
#include "Serie.hpp"
#include <iostream>
using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Serie::Serie(string titre, int annee, string lien, string affiche, Observateur * obs) {
	this->titre = titre;
	this->annee = annee;
	this->lien = lien;
	this->affiche = affiche;
	this->en_cours = true;
	this->vu = false;
	this->aVoir = false;
	this->observateur = obs;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Serie::~Serie() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le statut de la série (en cours ou terminée)
*/
string Serie::getStatutSerie(){
	if(this->en_cours){
		return("Série en cours");
	}
	else{
		return("Série terminée");
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le statut de la série
*/
void Serie::setStatutSerie(bool ec){
	this->en_cours = ec;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le lien vers la BA de la série
*/
string Serie::getLien(){
	return this->lien;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le lien vers la BA
*/
void Serie::setLien(string lien){
	this->lien = lien;
}

//--------------------------------------------------
/*!
* \brief Méthode qui lance la lecture de la BA du film
*/
void Serie::lire(){
}
 //lire BA
