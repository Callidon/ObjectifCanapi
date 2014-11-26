/*!
* \file Episode.cpp
* \brief Fichier contenant l'implémentation de la classe Episode
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/

#include "Episode.hpp"
#include <iostream>

using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur n°1
* \param id Identifiant de la vidéo
* \param titre Titre de la vidéo
* \param lien Lien vers la bande-annonce
* \param affiche Lien vers l'affiche
* \param annee Année de la vidéo
* \param numero Numéro de l'épisode dans la saion
* \param saison Numéro de la saison de l'épisode
* \param serie identifiant de la série associée à l'épisode
* \param synopsis Synopsis de la vidéo
* \param pays pays associé à la vidéo
*/
Episode::Episode(string id, string titre, string lien, int annee, string affiche, int numero, int saison, string serie, string synopsis, string pays)
	:Video(id, titre, lien, synopsis, annee, affiche, pays) {
	this->numero = numero;
	this->saison = saison;
	this->serie = serie;
}

//--------------------------------------------------
/*!
* \brief Constructeur n°2
* \param id Identifiant de la vidéo
* \param titre Titre de la vidéo
* \param lien Lien vers la bande-annonce
* \param annee Année de la vidéo
* \param affiche Lien vers l'affiche
* \param numero Numéro de l'épisode dans la saion
* \param saison Numéro de la saison de l'épisode
* \param serie identifiant de la série associée à l'épisode
* \param synopsis Synopsis de la vidéo
* \param acteurs Liste (vector) des acteurs de la vidéo
* \param real Liste (vector) des réalisateurs de la vidéo
* \param pays pays associé à la vidéo
*/
Episode::Episode(string id, string titre, string lien, int annee, string affiche, int numero, int saison, string serie, string synopsis, vector<string> acteurs, vector<string> real, string pays)
	:Video(id, titre, lien, synopsis, annee, affiche, acteurs, real, pays) {
	this->numero = numero;
	this->saison = saison;
	this->serie = serie;
}

//--------------------------------------------------
/*!
* \brief Constructeur n°3
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
Episode::Episode(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays)
	:Video(id, titre, lien, synopsis, annee, affiche, acteurs, real, pays) 
	{}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Episode::~Episode() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le numero de l'épiode
* \return Le numéro de l'épisode
*/
int Episode::getNumero(){
	return this->numero;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie le numero de l'épisode
* \param num Le nouveau numéro de l'épisode
*/
void Episode::setNumero(int num){
	this->numero = num;
}


//--------------------------------------------------
/*!
* \brief Méthode qui retourne le numero de la saison
* \return La saison de l'épisode
*/
int Episode::getSaison(){
	return this->saison;
}


//--------------------------------------------------
/*!
* \brief Méthode qui modifie le numero de la saison
* \param num Le nouveau numéro de la saison
*/
void Episode::setSaison(int num){
	this->saison = num;
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne l'identifiant de la série
* \return L'identifiant de la série associée à l'épisode
*/
string Episode::getSerie(){
	return this->serie;
}

//--------------------------------------------------
/*!
* \brief Méthode qui modifie l'identifiant de la série
* \param serie Le nouvel ideitnfiant de la série associée à l'épisode
*/
void Episode::setSerie(string serie){
	this->serie = serie;
}


//--------------------------------------------------
/*!
* \brief Méthode qui retourne le statut du episode ("a voir" ou "vu")
* \return Le statut de l'épisode
*/
string Episode::getStatut(){
	if(this->vu){
		return("Episode vu");
	}
	else if(this->aVoir){
		return("Episode à voir");
	}
	else {
		return("aucun marquage");
	}
}

