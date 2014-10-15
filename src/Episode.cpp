/*!
* \file Episode.cpp
* \brief Fichier contenant l'implémentation de la classe Episode
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/

#include "Episode.hpp"
#include <iostream>

using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Episode::Episode(string id, string titre, string lien, int annee, int numero, int saison, string serie, string synopsis):Video(id, titre, lien, synopsis, annee) {
	this->numero = numero;
	this->saison = saison;
	this->serie = serie; //nom de la série
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Episode::~Episode() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le numero de l'épiode
*/
int Episode::getNumero(){
	return this->numero;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le numero de l'épisode
*/
void Episode::setNumero(int num){
	this->numero = num;
}


//--------------------------------------------------
/*!
* \brief Méthode qui retourne le numero de la saison
*/
int Episode::getSaison(){
	return this->saison;
}


//--------------------------------------------------
/*!
* \brief Méthode qui modifie le numero de la saison
*/
void Episode::setSaison(int num){
	this->saison = saison;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le nom de la série
*/
string Episode::getSerie(){
	return this->serie;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le nom de la série
*/
void Episode::setSerie(string serie){
	this->serie = serie;
}
