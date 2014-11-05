/*!
* \file Bibliotheque.cpp
* \brief Fichier contenant l'implémentation de la classe Bibliotheque
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/

#include "Bibliotheque.hpp"
#include <iostream>
#include <sstream>

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

//--------------------------------------------------
/*!
* \brief Méthode qui met à jour le statut de la vidéo sélectionnée
* \param vu Si la vidéo est vu ou non
* \param aVoir Si la vidéo est a voir ou non
*/
void Bibliotheque::setStatutCurrentVideo(bool vu, bool aVoir) {
	string sql_test_existence, sql_update, sql_insert_film, sql_recherche;
	stringstream test_existence, update, insert_film;
	int id_acteur_courant, id_real_courant;
	
	//mise à jour de la vidéo courante
	if(vu) {
		this->currentVideo->marquerVu();
	}
	if(aVoir) {
		this->currentVideo->marquerVoir();
	}
	
	//en fonction du type de la vidéo courante, on crée les requêtes sql adéquates
	//on essaye de convertir la vidéo courante dans les différents types disponibles
	shared_ptr<Film> currentFilm(dynamic_pointer_cast<Film>(this->currentVideo));
	shared_ptr<Episode> currentEpisode(dynamic_pointer_cast<Episode>(this->currentVideo));
	
	if(currentFilm) { //si la conversion en Film a réussi, la vidéo est bien de type Film
		
		test_existence << "SELECT * FROM Films WHERE id_film = '" << currentFilm->getId() << "';";
		update << "UPDATE Films " 
				  "SET vu = " << vu 
				  << ", aVoir = " << aVoir 
				  << " WHERE id_film = " << currentFilm->getId() << "';";
		insert_film << "INSERT INTO Films "
				  "VALUES ('" << currentFilm->getId() 
				  << "','" << currentFilm->getTitre() 
				  << "', '" << currentFilm->getLien() 
				  << "', " << currentFilm->getAnnee() 
				  << ", '" << currentFilm->getSynopsis()
				  << "', '" << currentFilm->getAffiche() 
				  << ", '" << currentFilm->getPays()
				  << "', " << vu << ", " << aVoir << ");";
				  
	} else if (currentEpisode) { //si la conversion en Episode a réussi, la vidéo est bien de type Episode
		
		test_existence << "SELECT * FROM Episodes WHERE id_episode = '" << currentEpisode->getId() << "';";
		update << "UPDATE Episodes "
				  "SET vu = " << vu 
				  << ", aVoir = " << aVoir 
				  << " WHERE id_episode = " << currentEpisode->getId() << "';";
		insert_film << "INSERT INTO Episodes"
				  "VALUES ('" << currentEpisode->getId() 
				  << "', '" << currentEpisode->getTitre()
				   << "', '" << currentEpisode->getLien() 
				   << "', " << currentEpisode->getAnnee() 
				   << ", '" << currentEpisode->getSynopsis() 
				   << "', " << currentEpisode->getNumero()
				   << ", " << currentEpisode->getSaison() 
				   << ", '" << currentEpisode->getSerie()
				   << ", '" << currentEpisode->getPays()
				   << "', " << vu << ", " << aVoir << ");";
	}
	//conversion des stringstream en string
	sql_test_existence = test_existence.str();
	sql_update = update.str();
	sql_insert_film = insert_film.str();
	
	//si la vidéo est déjà présente en base, on la met à jour
	if(! this->database->isQueryEmpty(sql_test_existence) ) {
		
		this->database->query(sql_update);
		
	} else { //sinon, on l'ajoute dans la base
		
		//on ajoute la vidéo en elle-même
		this->database->query(sql_insert_film);
		
		//on insert les acteurs & réalisateurs en respectant la structure de la base de données
		//on récupère les deux listes
		vector<string> acteurs = this->currentVideo->getActeurs();
		vector<string> realisateurs = this->currentVideo->getReal();
		
		//on parcours la liste des acteurs
		for(const auto &acteur: acteurs) {
			sql_recherche = "SELECT * FROM Personnes WHERE nom = " + acteur + ";";
			
			//si c'est acteur n'est pas déjà présent en base
			if(this->database->isQueryEmpty(sql_recherche)) {
				stringstream insert_personne; //variable locale servant à la création de la requête
				//alors on l'insère dans la table Personnes
				id_acteur_courant = this->database->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				insert_personne << "INSERT INTO Personnes "
								   "VALUES (" << id_acteur_courant
								   << ", '" << acteur << "');";
				this->database->query(insert_personne.str()); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->database->query(sql_recherche);
				id_acteur_courant = atoi(table[0][0].c_str());
			}
			
			//on associe l'acteur au film grâce à la table Acteurs
			stringstream insert_acteur; //variable locale servant à la création de la requête
			insert_acteur << "INSERT INTO Acteurs "
							 "VALUES (" << id_acteur_courant 
							 << ", '" << this->currentVideo->getId() << "');";
			this->database->query(insert_acteur.str());
		}
		
		//on fait pareil avec les réalisateurs
		//TODO
		
	}
}
