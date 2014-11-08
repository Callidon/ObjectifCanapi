/*!
* \file Serie.cpp
* \brief Fichier contenant l'implémentation de la classe Serie
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "Serie.hpp"
#include <iostream>
using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
Serie::Serie(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays):Video(id, titre, lien, synopsis, annee, affiche, pays) {
}

Serie::Serie(string id, string titre, string lien, int annee, string affiche, string synopsis, vector<string> acteurs, vector<string> real, string pays):Video(id, titre, lien, synopsis, annee, affiche, acteurs, real, pays) {
}


//--------------------------------------------------
/*!
* \brief Destructeur
*/
Serie::~Serie() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne le statut du Serie ("a voir" ou "vu")
*/
string Serie::getStatut(){
	if(this->vu){
		return("Serie vu");
	}
	else if(this->aVoir){
		return("Serie à voir");
	}
	else {
		return("aucun marquage");
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute un episode a la liste
*/
void Serie::addEpisode(shared_ptr<Episode> episode){
	this->episodes.push_back(episode);
}

//--------------------------------------------------
/*!
* \brief Méthode qui retourne la liste des episodes
*/
vector<shared_ptr<Episode>> Serie::getEpisodes(){
	return this->episodes;
}

