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
Video::Video(string id, string titre, string lien, string synopsis, int annee, string affiche, string pays) {
	this->id = id;
	this->titre = titre;
	this->lien = lien;
	this->annee = annee;
	this->affiche = affiche;
	this->synopsis = synopsis;
	this->vu = false;
	this->aVoir = false;
	this->pays = pays;
}

Video::Video(string id, string titre, string lien, string synopsis, int annee, string affiche, vector<string> acteurs, vector<string> real, string pays){
	this->id = id;
	this->titre = titre;
	this->lien = lien;
	this->annee = annee;
	this->affiche = affiche;
	this->pays = pays;
	this->synopsis = synopsis;
	this->vu = false;
	this->aVoir = false;
	this->acteurs = acteurs;
	this->realisateurs = real;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Video::~Video() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne l'id du film
*/
string Video::getId(){
	return this->id;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie l'id de la Video par celui passé en parametre
*/
void Video::setId(int id){
	this->id = id;
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
* \brief Méthode qui retourne l'affiche de la Video
*/
string Video::getAffiche(){
	return this->affiche;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie l'affiche de la video par celle passée en parametre
*/
void Video::setAffiche(string aff){
	this->affiche = aff;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le pays de la Video
*/
string Video::getPays(){
	return this->pays;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le pays de prod par celle passé en parametre
*/
void Video::setPays(string pays){
	this->pays = pays;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le synopsis de la Video
*/
string Video::getSynopsis(){
	return this->synopsis;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le synopsis par celui passé en parametre
*/
void Video::setSynopsis(string syno){
	this->synopsis = syno;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des acteurs (principaux) du Videos
*/
vector<string> Video::getActeurs(){
	return this->acteurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un acteur à la liste
*/
void Video::addActeur(string acteur){
	this->acteurs.push_back(acteur);
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des réalisateurs du Video
*/
vector<string> Video::getReal(){
	return this->realisateurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un realisateur à la liste
*/
void Video::addReal(string real){
	this->realisateurs.push_back(real);
}

//--------------------------------------------------
/*!
* \brief Méthode qui marque le Video en tant que VU
*/
void Video::marquerVu(){
	this->vu = true;
	this->aVoir = false;
}

//--------------------------------------------------
/*!
* \brief Méthode qui marque le Video en tant que A VOIR
*/
void Video::marquerVoir(){
	this->vu = false;
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