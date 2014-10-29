/*!
* \file Bibliotheque.cpp
* \brief Fichier contenant l'implémentation de la classe Bibliotheque
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/

#include "Bibliotheque.hpp"
#include <iostream>

using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
* \param user Nom de l'utilisateur associé à la bibliothèque
*/
Bibliotheque::Bibliotheque(string user) {
	//initilisation des attributs
	this->user = user;
	shared_ptr<BDConnector> tmpDB(new BDConnector(user + ".db"));
	shared_ptr<FactoryOMDB> tmpOMDB(new FactoryOMDB(this->database));
	this->database = tmpDB;
	this->factoryOMDB = tmpOMDB;
	this->currentVideo = 0;
	
	//récupération des vidéos liées à cet utilisateur et enregistrées dans la base de données
	shared_ptr<FactorySQL> factorySQL(new FactorySQL(this->database));
	vector<shared_ptr<Video> > tmpFilms = factorySQL->recupererAllFilms();
	vector<shared_ptr<Video> > tmpEpisodes = factorySQL->recupererAllEpisodes();
	//ajouts des films & épisodes à la bibliothèque
	this->videos.insert(this->videos.end(), tmpFilms.begin(), tmpFilms.end());
	this->videos.insert(this->videos.end(), tmpEpisodes.begin(), tmpEpisodes.end());
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Bibliotheque::~Bibliotheque() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui renvoie le nom de l'utilisateur associé à la bibliothèque
* \return Le nom de l'utilisateur associé à la bibliothèque
*/
string Bibliotheque::getUser() {
	return this->user;
}

//--------------------------------------------------
/*!
* \brief Méthode qui définit le nom de l'utilisateur associé à la bibliothèque
* \param user Le nom de l'utilisateur à associer à la bibliothèque
*/
void Bibliotheque::setUser(string user) {
	this->user = user;
}

//--------------------------------------------------
/*!
* \brief Méthode qui
*/
vector<shared_ptr<Video>> Bibliotheque::getVideos() {
	return this->videos;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute une nouvelle vidéo (film ou episode) à la bibliothèque
* \param nom_video Titre de la vidéo à ajouter
* \param is_episode Si la vidéo est un épisode ou non
*/
void Bibliotheque::addVideo(string nom_video, bool is_episode) {
	//on récupère la requête OMDB lié à la vidéo
	string query = this->factoryOMDB->queryTitle(nom_video);
	//si la vidéo est un épisode
	if(is_episode) {
		
	} else { //sinon, c'est un film
		//on génère le nouveau film via la factory et on l'ajoute à la liste des vidéos
		this->videos.push_back(this->factoryOMDB->makeFilm(query));
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui sélectionne une vidéo de la bibliothèque
* \param titre Titre de la vidéo à sélectionner
*/
void Bibliotheque::selectVideo(string titre) {
	//on parcours la liste des vidéos
	for(const auto &video: this->videos) {
		//si le titre de la vidéo courante correspond au titre passé en paramètre
		if(video->getTitre() == titre) {
			this->currentVideo = video; //on mémorise la sélection
			break; //on arrête le parcours
		}
	}
}
