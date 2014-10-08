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
	this->observateur = 0;
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
	this->observateur->notifier(this);
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
	this->observateur->notifier(this);
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
	this->observateur->notifier(this);
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des acteurs (principaux) du Videos
*/
list<Personne> Video::getActeurs(){
	return this->acteurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un acteur à la liste
*/
void Video::addActeur(Personne acteur){
	this->acteurs.push_back(acteur);
	this->observateur->notifier(this);
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des réalisateurs du Video
*/
list<Personne> Video::getReal(){
	return this->realisateurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un realisateur à la liste
*/
void Video::addReal(Personne real){
	this->realisateurs.push_back(real);
	this->observateur->notifier(this);
}

//--------------------------------------------------
/*!
* \brief Méthode qui renvoie l'observateur associé à la classe
*/
void Video::setObservateur(FilmObservateur * obs){
	this->observateur = obs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui marque le Video en tant que VU
*/
FilmObservateur * Video::getObservateur(){
	return this->observateur;
}

//--------------------------------------------------
/*!
* \brief Méthode qui marque le Video en tant que A VOIR
*/
void Video::marquerVoir(){
	this->aVoir = true;
	this->observateur->notifier(this);
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
