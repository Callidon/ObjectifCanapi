/*!
* \file Film.cpp
* \brief Fichier contenant l'implémentation de la classe Film
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#include "Film.hpp"
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
Film::Film(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays)
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
Film::Film(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays)
	:Video(id, titre, lien, synopsis, annee, affiche, acteurs, real, pays) 
	{}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Film::~Film() {
}
//--------------------------------------------------
/*!
* \brief Méthode qui retourne le statut du film ("a voir" ou "vu")
* \return Le statut du film
*/
string Film::getStatut(){
	if(this->vu){
		return("vu");
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
* \brief Méthode qui converti le film en episode
* \return Un shared_ptr vers un épisode formé à partir du film
*/
shared_ptr<Episode> Film::filmToEpisode(){
	shared_ptr<Episode> ep (new Episode(this->getId(), this->getTitre(), getLien(), getAnnee(), getAffiche(), getSynopsis(), getActeurs(), getReal(), getPays()));
	return ep;
}

//--------------------------------------------------
/*!
* \brief Méthode qui converti le film en serie
* \return Un shared_ptr vers une série formée à partir du film
*/
shared_ptr<Serie> Film::filmToSerie(){
	shared_ptr<Serie> serie (new Serie(this->getId(), this->getTitre(), getLien(), getAnnee(), getAffiche(), getSynopsis(), getActeurs(), getReal(), getPays()));
	return serie;
}
