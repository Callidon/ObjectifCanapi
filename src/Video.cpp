/*!
* \file Film.cpp
* \brief Fichier contenant l'implémentation de la classe Video
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "Video.hpp"

#include <iostream>
using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Video::Video(string titre, string lien, string synopsis, int annee) {
	this->titre = titre;
	this->lien = lien;
	this->annee = annee;
	this->synopsis = synopsis;
	this->vu = false;
	this->aVoir = false;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Video::~Video() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le titre du film
*/
string Video::getTitre(){
	return this->titre;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le titre du Video par celui passé en parametre
*/
void Video::setTitre(string titre){
	this->titre = titre;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le lien de la BA
*/
string Video::getLien(){
	return this->lien;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le lien de la BA par celui passé en parametre
*/
void Video::setLien(string lien){
	this->lien = lien;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne l'annee de production du Video
*/
int Video::getAnnee(){
	return this->annee;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie l'annee de prod par celle passé en parametre
*/
void Video::setAnnee(int annee){
	this->annee = annee;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des acteurs (principaux) du Videos
*/
vector<shared_ptr<Personne> > Video::getActeurs(){
	return this->acteurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un acteur à la liste
*/
void Video::addActeur(shared_ptr<Personne> acteur){
	this->acteurs.push_back(acteur);
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des réalisateurs du Video
*/
vector<shared_ptr<Personne> > Video::getReal(){
	return this->realisateurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un realisateur à la liste
*/
void Video::addReal(shared_ptr<Personne> real){
	this->realisateurs.push_back(real);
}

//--------------------------------------------------
/*!
* \brief Méthode qui marque le Video en tant que A VOIR
*/
void Video::marquerVoir(){
	this->aVoir = true;
}

//--------------------------------------------------
/*!
* \brief Méthode qui lance la lecture de la BA du Video
*/
void Video::lire(){
	string command = "firefox " + this->lien;
	system((char*)command.c_str());
}
 //lire BA
