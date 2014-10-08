/*!
* \file Bibliotheque.cpp
* \brief Fichier contenant l'implémentation de la classe Bibliotheque
* \author Camille Le LUët
* \author Thomas Minier
* \date ?
*/

#include "Bibliotheque.hpp"
#include <iostream>

using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Bibliotheque::Bibliotheque(string user) {
	this->user = user;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Bibliotheque::~Bibliotheque() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui
*/
string Bibliotheque::getUser() {
	return this->user;
}

//--------------------------------------------------
/*!
* \brief Méthode qui
*/
void Bibliotheque::setUser(string user) {
	this->user = user;
}

//--------------------------------------------------
/*!
* \brief Méthode qui
*/
list<Video*> Bibliotheque::getVideos() {
	return this->videos;
}

//--------------------------------------------------
/*!
* \brief Méthode qui
*/
void Bibliotheque::addVideo(Video * video) {
	this->videos.push_back(video);
}