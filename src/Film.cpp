/*!
* \file Film.cpp
* \brief Fichier contenant l'implémentation de la classe Film
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "Film.hpp"
#include <iostream>
using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Film::Film(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays):Video(id, titre, lien, synopsis, annee, affiche, pays) {
}

Film::Film(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays):Video(id, titre, lien, synopsis, annee, affiche, acteurs, real, pays) {
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Film::~Film() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le statut du film ("a voir" ou "vu")
*/
string Film::getStatut(){
	if(this->vu){
		return("Film vu");
	}
	else if(this->aVoir){
		return("Film à voir");
	}
	else {
		return("aucun marquage");
	}
}


//--------------------------------------------------
/*!
* \brief Méthode qui converti le film en episode
*/
shared_ptr<Episode> Film::filmToEpisode(){
	shared_ptr<Episode> ep (new Episode(this->getId(), this->getTitre(), getLien(), getAnnee(), getAffiche(), getSynopsis(), getActeurs(), getReal(), getPays()));
	return ep;
}

//--------------------------------------------------
/*!
* \brief Méthode qui converti le film en serie
*/
shared_ptr<Serie> Film::filmToSerie(){
	shared_ptr<Serie> serie (new Serie(this->getId(), this->getTitre(), getLien(), getAnnee(), getAffiche(), getSynopsis(), getActeurs(), getReal(), getPays()));
	return serie;
}
