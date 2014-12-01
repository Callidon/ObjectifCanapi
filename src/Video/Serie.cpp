/*!
* \file Serie.cpp
* \brief Fichier contenant l'implémentation de la classe Serie
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#include "Serie.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur n°1
* \param id Identifiant de la vidéo
* \param titre Titre de la vidéo
* \param lien Lien vers la bande-annonce
* \param annee Année de la vidéo
* \param affiche Lien vers l'affiche
* \param synopsis Synopsis de la vidéo
* \param pays pays associé à la vidéo
*/
Serie::Serie(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays)
	:Video(id, titre, lien, synopsis, annee, affiche, pays) 
	{}

//--------------------------------------------------
/*!
* \brief Constructeur n°2
* \param id Identifiant de la vidéo
* \param titre Titre de la vidéo
* \param lien Lien vers la bande-annonce
* \param annee Année de la vidéo
* \param affiche Lien vers l'affiche
* \param synopsis Synopsis de la vidéo
* \param acteurs Liste (vector) des acteurs de la vidéo
* \param real Liste (vector) des réalisateurs de la vidéo
* \param pays pays associé à la vidéo
*/
Serie::Serie(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays)
	:Video(id, titre, lien, synopsis, annee, affiche, acteurs, real, pays) 
	{}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Serie::~Serie() {
}
//--------------------------------------------------
/*!
* \brief Méthode qui retourne le statut du Serie ("a voir" ou "vu")
* \return Le statut de la série
*/
string Serie::getStatut(){
	if(this->vu){
		return("vue");
	}
	else if(this->aVoir){
		return("à voir");
	}
	else {
		return("aucun marquage");
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un episode a la liste
* \param episode Un shared_ptr vers l'épisode à ajouter
*/
void Serie::addEpisode(shared_ptr<Episode> episode){
	this->episodes.push_back(episode);
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des episodes
* \return Un vector de shared_ptr vers les épisodes de la série
*/
vector<shared_ptr<Episode>> Serie::getEpisodes(){
	return this->episodes;
}

