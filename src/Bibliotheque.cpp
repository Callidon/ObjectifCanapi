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
	vector<shared_ptr<Video> > tmpSeries = factorySQL->recupererAllSeries();
	//ajouts des films & séries à la bibliothèque
	this->videos.insert(this->videos.end(), tmpFilms.begin(), tmpFilms.end());
	this->videos.insert(this->videos.end(), tmpSeries.begin(), tmpSeries.end());
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
void Bibliotheque::addVideo(string nom_video, string type_video) {
	//en fonction du type de la vidéo
	if(type_video == "Film") {
		//stuff
	} else if(type_video == "Serie") {
		//stuff
	} else if(type_video == "Episode") {
		//stuff
	} else {
		cout << "Erreur : type de vidéo inconnu" << endl;
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
	string sql_test_existence, sql_update, sql_insert_video, sql_insert_personne, sql_insert_acteur, sql_insert_real, sql_recherche;
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
	shared_ptr<Serie> currentSerie(dynamic_pointer_cast<Serie>(this->currentVideo));
	shared_ptr<Episode> currentEpisode(dynamic_pointer_cast<Episode>(this->currentVideo));
	
	if(currentFilm) { //si la conversion en Film a réussi, la vidéo est bien de type Film
		
		sql_test_existence = "SELECT * FROM Films WHERE id_film = '" + currentFilm->getId() + "';";
		sql_update = "UPDATE Films " 
				  "SET vu = " + to_string(vu) 
				  + ", aVoir = " + to_string(aVoir) 
				  + " WHERE id_film = " + currentFilm->getId() + "';";
		sql_insert_video = "INSERT INTO Films "
				  "VALUES ('" + currentFilm->getId() + "', '" 
				  + currentFilm->getTitre() + "', '" 
				  + currentFilm->getLien() + "', " 
				  + to_string(currentFilm->getAnnee()) + ", '" 
				  + currentFilm->getSynopsis() + "', '" 
				  + currentFilm->getAffiche() + ", '" 
				  + currentFilm->getPays() + "', " 
				  + to_string(vu) + ", " + to_string(aVoir) + ");";
				  
	} else if(currentSerie) { //si la conversion en Serie a réussi, la vidéo est bien de type Serie
		
		sql_test_existence = "SELECT * FROM Series WHERE id_serie = '" + currentSerie->getId() + "';";
		sql_update = "UPDATE Series "
				  "SET vu = " + to_string(vu) 
				  + ", aVoir = " + to_string(aVoir) 
				  + " WHERE id_serie = " + currentSerie->getId() + "';";
		sql_insert_video = "INSERT INTO Series "
				  "VALUES ('" + currentFilm->getId() + "', '" 
				  + currentFilm->getTitre() + "', '" 
				  + currentFilm->getLien() + "', " 
				  + to_string(currentFilm->getAnnee()) + ", '" 
				  + currentFilm->getSynopsis() + "', '" 
				  + currentFilm->getAffiche() + ", '" 
				  + currentFilm->getPays() + "', " 
				  + to_string(vu) + ", " + to_string(aVoir) + ");";
		
	} else if (currentEpisode) { //si la conversion en Episode a réussi, la vidéo est bien de type Episode
		
		sql_test_existence = "SELECT * FROM Episodes WHERE id_episode = '" + currentEpisode->getId() + "';";
		sql_update = "UPDATE Episodes "
				  "SET vu = " + to_string(vu) 
				  + ", aVoir = " + to_string(aVoir) 
				  + " WHERE id_episode = " + currentEpisode->getId() + "';";
		sql_insert_video = "INSERT INTO Episodes"
				  "VALUES ('" + currentEpisode->getId() 
				  + "', '" + currentEpisode->getTitre()
				  + "', '" + currentEpisode->getLien() 
				  + "', " + to_string(currentEpisode->getAnnee()) 
				  + "', " + currentEpisode->getAffiche()
				  + ", '" + currentEpisode->getSynopsis() 
				  + "', " + to_string(currentEpisode->getNumero())
				  + ", " + to_string(currentEpisode->getSaison()) 
				  + ", '" + currentEpisode->getSerie()
				  + ", '" + currentEpisode->getPays()
				  + "', " + to_string(vu) + ", " + to_string(aVoir) + ");";
	}
	
	//si la vidéo est déjà présente en base, on la met à jour
	if(! this->database->isQueryEmpty(sql_test_existence) ) {
		
		this->database->query(sql_update);
		
	} else { //sinon, on l'ajoute dans la base
		
		//on ajoute la vidéo en elle-même
		this->database->query(sql_insert_video);
		
		//on insert les acteurs & réalisateurs en respectant la structure de la base de données
		//on récupère les deux listes
		vector<string> acteurs = this->currentVideo->getActeurs();
		vector<string> realisateurs = this->currentVideo->getReal();
		
		//on parcours la liste des acteurs
		for(const auto &acteur: acteurs) {
			sql_recherche = "SELECT * FROM Personnes WHERE nom = " + acteur + ";";
			
			//si c'est acteur n'est pas déjà présent en base
			if(this->database->isQueryEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_acteur_courant = this->database->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert_personne = "INSERT INTO Personnes "
								   "VALUES (" + to_string(id_acteur_courant)
								   + ", '" + acteur + "');";
				this->database->query(sql_insert_personne); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->database->query(sql_recherche);
				id_acteur_courant = atoi(table[0][0].c_str());
			}
			
			//on associe l'acteur au film grâce à la table Acteurs
			sql_insert_acteur = "INSERT INTO Acteurs "
							 "VALUES (" + to_string(id_acteur_courant) 
							 + ", '" + this->currentVideo->getId() + "');";
			this->database->query(sql_insert_acteur);
		}
		
		//on fait pareil avec les réalisateurs
		//on parcours la liste des réalisateurs
		for(const auto &realisateur: realisateurs) {
			sql_recherche = "SELECT * FROM Personnes WHERE nom = " + realisateur + ";";
			
			//si ce réalisateur n'est pas déjà présent en base
			if(this->database->isQueryEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_real_courant = this->database->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert_personne = "INSERT INTO Personnes "
								   "VALUES (" + to_string(id_real_courant)
								   + ", '" + realisateur + "');";
				this->database->query(sql_insert_personne); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->database->query(sql_recherche);
				id_real_courant = atoi(table[0][0].c_str());
			}
			
			//on associe le réalisateur au film grâce à la table Realisateurs
			sql_insert_real = "INSERT INTO Realisateurs "
							 "VALUES (" + to_string(id_real_courant) 
							 + ", '" + this->currentVideo->getId() + "');";
			this->database->query(sql_insert_real);
		}
		
	}
}
