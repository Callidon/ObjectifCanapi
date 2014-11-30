/*!
* \file Film.cpp
* \brief Fichier contenant l'implémentation de la classe Video
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#include "Video.hpp"

#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur n°1
* \param id Identifiant de la vidéo
* \param titre Titre de la vidéo
* \param lien Lien vers la bande-annonce
* \param synopsis Synopsis de la vidéo
* \param annee Année de la vidéo
* \param affiche Lien vers l'affiche
* \param pays pays associé à la vidéo
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

//--------------------------------------------------
/*!
* \brief Constructeur n°2
* \param id Identifiant de la vidéo
* \param titre Titre de la vidéo
* \param lien Lien vers la bande-annonce
* \param synopsis Synopsis de la vidéo
* \param annee Année de la vidéo
* \param affiche Lien vers l'affiche
* \param acteurs Liste (vector) des acteurs de la vidéo
* \param real Liste (vector) des réalisateurs de la vidéo
* \param pays pays associé à la vidéo
*/
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
* \brief Méthode qui retourne l'id de la vidéo
* \return L'identifiant de la vidéo
*/
string Video::getId(){
	return this->id;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie l'id de la Video par celui passé en parametre
* \param id Nouvel identifiant de la vidéo
*/
void Video::setId(string id){
	this->id = id;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le titre de la vidéo
* \return Le titre de la vidéo
*/
string Video::getTitre(){
	return this->titre;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le titre de la vidéo par celui passé en parametre
* \param titre Le nouveau titre de la vidéo
*/
void Video::setTitre(string titre){
	this->titre = titre;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le lien de la BA
* \return Le lien vers la bande-annonce
*/
string Video::getLien(){
	return this->lien;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le lien de la BA par celui passé en parametre
* \param lien Le nouveau lien vers la bande-annonce
*/
void Video::setLien(string lien){
	this->lien = lien;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne l'annee de production du Video
* \return L'année de la vidéo
*/
int Video::getAnnee(){
	return this->annee;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie l'annee de prod par celle passé en parametre
* \param annee La nouvelle année de la vidéo
*/
void Video::setAnnee(int annee){
	this->annee = annee;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne l'affiche de la Video
* \return Le lien vers l'affiche de la vidéo
*/
string Video::getAffiche(){
	return this->affiche;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie l'affiche de la video par celle passée en parametre
* \param aff le nouveau lien vers l'affiche de la vidéo
*/
void Video::setAffiche(string aff){
	this->affiche = aff;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le pays de la Video
* \return Le pays associé à la vidéo
*/
string Video::getPays(){
	return this->pays;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le pays de prod par celle passé en paramètre
* \param pays Le nouveau pays associé à la vidéo
*/
void Video::setPays(string pays){
	this->pays = pays;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le synopsis de la Video
* \return Le synopsis de la vidéo
*/
string Video::getSynopsis(){
	return this->synopsis;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le synopsis par celui passé en parametre
* \param syno Le nouveau synopsis de la vidéo
*/
void Video::setSynopsis(string syno){
	this->synopsis = syno;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des acteurs (principaux) du Videos
* \return Un vector contenant les noms des acteurs de la vidéo
*/
vector<string> Video::getActeurs(){
	return this->acteurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un acteur à la liste
* \param acteur Le nom de l'acteur à ajouter
*/
void Video::addActeur(string acteur){
	this->acteurs.push_back(acteur);
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des réalisateurs du Video
* \return Un vector contenant les noms des réalisateurs de la vidéo
*/
vector<string> Video::getReal(){
	return this->realisateurs;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un realisateur à la liste
* \param real Le nom du réalisateur à ajouter
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

//--------------------------------------------------
/*!
* \brief Méthode qui ouvre l'affiche dans un navigateur
*/
void Video::voirAffiche(){
	string command = "firefox " + this->affiche;
	system((char*)command.c_str());
}

//--------------------------------------------------
/*!
* \brief Méthodes retournant les statuts de la video
*/
bool Video::getVu(){
	return this->vu;
}
bool Video::getVoir(){
	return this->aVoir;
}
