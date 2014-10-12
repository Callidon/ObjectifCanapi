/*!
* \file Episode.cpp
* \brief Fichier contenant l'implémentation de la classe Personne
* \author Camille Le LUët
* \author Thomas Minier
* \date ?
*/
#include "Personne.hpp"
#include <iostream>

using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Personne::Personne(string nom, string prenom) {
	this->nom = nom;
	this->prenom = prenom;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Personne::~Personne() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le nom
*/
string Personne::getNom(){
	return this->nom;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le prénom
*/
void Personne::setNom(string nom){
	this->nom = nom;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le prenom
*/
string Personne::getPrenom(){
	return this->prenom;
}


//--------------------------------------------------
/*!
* \brief Méthode qui modifie le prenom
*/
void Personne::setPrenom(string prenom){	
	this->prenom  = prenom;
}


//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des films;
*/
vector<shared_ptr<Video> > Personne::getFilms(){
	return this->films;
}


//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un film à la liste;
*/
void Personne::addFilms(Video video){
	this->films.push_back(video);
}
