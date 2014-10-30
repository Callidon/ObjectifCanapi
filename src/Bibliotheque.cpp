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
* \brief Méthode qui vérifie si la vidéo actuellement sélectionnée est un film
* \return Un booléen qui indique si la vidéo actuellement sélectionnée est un film ou non
*/
bool Bibliotheque::currentIsFilm() {
	bool res = false; //booléen qui contient la réponse au test
	//on teste le type de la vidéo courante
	shared_ptr<Film> test_ptr(dynamic_pointer_cast<Film>(this->currentVideo));
	if (test_ptr) { //si c'est bel et bien un objet de type Film
		res = true;
	}
	return res;
}

//--------------------------------------------------
/*!
* \brief Méthode qui vérifie si la vidéo actuellement sélectionnée est un épisode
* \return Un booléen qui indique si la vidéo actuellement sélectionnée est un épisode ou non
*/
bool Bibliotheque::currentIsEpisode() {
	bool res = false; //booléen qui contient la réponse au test
	//on teste le type de la vidéo courante
	shared_ptr<Episode> test_ptr(dynamic_pointer_cast<Episode>(this->currentVideo));
	if (test_ptr) { //si c'est bel et bien un objet de type Episode
		res = true;
	}
	return res;
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

//--------------------------------------------------
/*!
* \brief Méthode qui met à jour le statut de la vidéo sélectionnée
* \param vu Si la vidéo est vu ou non
* \param aVoir Si la vidéo est a voir ou non
*/
void Bibliotheque::setStatutCurrentVideo(bool vu, bool aVoir) {
	string type_currentVideo = "null";
	string sql_test_existence, sql_update, sql_insert;
	
	//mise à jour de la vidéo courante
	if(vu) {
		this->currentVideo->marquerVu();
	}
	if(aVoir) {
		this->currentVideo->marquerVoir();
	}
	
	//en fonction du type de la vidéo courante, on crée les requêtes sql adéquates
	if(this->currentIsFilm) {
		sql_test_existence = "SELECT * FROM Films WHERE id_film = '" + this->currentVideo->getId() + "';";
		sql_update = "UPDATE Films "
					 "SET vu = " + int(vu) + ", aVoir = " + int(aVoir) + " WHERE id_film = " + this->currentVideo->getId() + "';";
		sql_insert = "INSERT INTO Films"
					 "VALUES ('" + this->currentVideo->getId() + "'"
							 ", '" + this->currentVideo->getTitre() + "'"
							 ", '" + this->currentVideo->getLien() + "'"
							 ", " + this->currentVideo->getAnnee() + ""
							 ", '" + this->currentVideo->getSynopsis + "'"
							 ", '" + this->currentVideo->getAffiche() + "'"
							 ", " + int(vu) + ", " + int(aVoir) +  ");";
	} else if(this->currentIsEpisode) {
		sql_test_existence = "SELECT * FROM Episodes WHERE id_episode = '" + this->currentVideo->getId() + "';";
		sql_update = "UPDATE Episodes "
					 "SET vu = " + int(vu) + ", aVoir = " + int(aVoir) + " WHERE id_episode = " + this->currentVideo->getId() + "';";
		sql_insert = "INSERT INTO Episodes"
					 "VALUES ('" + this->currentVideo->getId() + "'"
							 ", '" + this->currentVideo->getTitre() + "'"
							 ", '" + this->currentVideo->getLien() + "'"
							 ", " + this->currentVideo->getAnnee() + ""
							 ", '" + this->currentVideo->getSynopsis + "'"
							 ", " + this->currentVideo->getNumero() + ""
							 ", " + this->currentVideo->getSaison() + ""
							 ", '" + this->currentVideo->getSerie() + "'"
							 ", " + int(vu) + ", " + int(aVoir) +  ");";
	}
	
	//si la vidéo est déjà présente en base, on la met à jour
	vecto<vector<string> > table = this->database->query(sql_test_existence);
	if(! (table.size() == 0) ) {
		this->database->query(sql_update);
	} else { //sinon, on l'ajoute dans la base
		
		//on ajoute la vidéo en elle-même
		this->database->query(sql_insert);
		
		//on insert les acteurs & réalisateurs en respectant la structure de la base de données
		//TODO
	}
}
