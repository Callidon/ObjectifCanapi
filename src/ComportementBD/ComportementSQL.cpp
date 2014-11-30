/*!
* \file ComportementSQL.cpp
* \brief Fichier contenant l'implémentation de la classe ComportementSQL
* \author Camille Le Luët
* \author Thomas Minier
* \date 22.11.2014
*/
#include "ComportementSQL.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
* \param db Pointeur vers la base de données à utiliser
*/
ComportementSQL::ComportementSQL(shared_ptr<BDConnector> db) {
	this->database = db;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
ComportementSQL::~ComportementSQL() {}

//--------------------------------------------------
string ComportementSQL::escape_string(string str) {
	string res = "";
	for (string::iterator it = str.begin(); it != str.end(); ++it) {
		char c = *it;
		if(c == '\'') {
			res += "\'\'";
		} else {
			res += c;
		}
	}
	return res;
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant un acteur à la base
* \param acteur L'acteur (nom + prénom) à ajouter dans la base
* \param id_video L'id de la vidéo auquel l'acteur est associé
*/
void ComportementSQL::addActeur(string acteur, string id_video) {
	int id_acteur;
	string sql_insert;
	string sql_recherche = "SELECT * FROM Personnes WHERE nom = '" + acteur + "';";

			//si c'est acteur n'est pas déjà présent en base
			if(this->database->isReturnEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_acteur = this->database->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert = "INSERT INTO Personnes "
							"VALUES (" + to_string(id_acteur)
							+ ", '" + escape_string(acteur) + "');";
				this->database->query(sql_insert); 
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->database->query(sql_recherche);
				id_acteur = atoi(table[0][0].c_str());

			}
			
			//on associe l'acteur au film grâce à la table Acteurs
			sql_insert = "INSERT INTO Acteurs "
						"VALUES (" + to_string(id_acteur) 
						+ ", '" + id_video + "');";
			this->database->query(sql_insert);
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant un réalisateur à la base
* \param real Le réalisateur (nom + prénom) à ajouter dans la base
* \param id_video L'id de la vidéo auquel le réalisateur est associé
*/
void ComportementSQL::addRealisateur(string real, string id_video) {
	int id_real;
	string sql_insert;
	string sql_recherche = "SELECT * FROM Personnes WHERE nom = '" + real + "';";
			
			//si ce réalisateur n'est pas déjà présent en base
			if(this->database->isReturnEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_real = this->database->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert = "INSERT INTO Personnes "
							"VALUES (" + to_string(id_real)
							+ ", '" + escape_string(real) + "');";
				this->database->query(sql_insert); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->database->query(sql_recherche);
				id_real = atoi(table[0][0].c_str());
			}
			
			//on associe le réalisateur au film grâce à la table Realisateurs
			sql_insert = "INSERT INTO Realisateurs "
						"VALUES (" + to_string(id_real) 
						+ ", '" + id_video + "');";
			this->database->query(sql_insert);
	
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant ou mettant à jour jour un film dans la base
* \param film shared_ptr vers le film à traiter
*/
void ComportementSQL::traiterFilm(shared_ptr<Film> film, bool vu, bool aVoir) {
	
	string sql;
	string sql_test_existence = "SELECT * FROM Films WHERE id_film = '" + film->getId() + "';";
	
	//si le film n'est pas déjà présent en base, on l'ajoute
	if( this->database->isReturnEmpty(sql_test_existence) ) {	
			
		sql = "INSERT INTO Films "
				"VALUES ('" + film->getId() + "', '" 
				+ escape_string(film->getTitre()) + "', '" 
				+ escape_string(film->getLien()) + "', " 
				+ to_string(film->getAnnee()) + ", '" 
				+ escape_string(film->getSynopsis()) + "', '" 
				+ escape_string(film->getAffiche()) + "', '" 
				+ escape_string(film->getPays()) + "', " 
				+ to_string(vu) + ", " + to_string(aVoir) + ");";
				
		//on effectue la requête
		this->database->query(sql);
			
		//on insère les acteurs & les réalisateurs en base
		//on récupère les listes des acteurs & réalisateurs
		vector<string> acteurs = film->getActeurs();
		vector<string> realisateurs = film->getReal();
			
		//parcours de la liste des acteurs
		for(const auto &acteur: acteurs) {
			this->addActeur(acteur, film->getId());
		}
			
		//parcours de la liste des réalisateurs
		for(const auto &realisateur: realisateurs) {
			this->addRealisateur(realisateur, film->getId());
		}
			
	} else { //sinon, on le met à jour
		sql = "UPDATE Films " 
				"SET vu = " + to_string(vu) 
				+ ", aVoir = " + to_string(aVoir) 
				+ " WHERE id_film = '" + film->getId() + "';";
		//on effectue la requête
		this->database->query(sql);
	}
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant ou mettant à jour jour une série dans la base
* \param serie shared_ptr vers la série à traiter
*/
void ComportementSQL::traiterSerie(shared_ptr<Serie> serie, bool vu, bool aVoir) {
	
	string sql;
	string sql_test_existence = "SELECT * FROM Series WHERE id_serie = '" + serie->getId() + "';";
	
	//si le film n'est pas déjà présent en base, on l'ajoute
	if( this->database->isReturnEmpty(sql_test_existence) ) {	
			
		sql = "INSERT INTO Series "
				"VALUES ('" + serie->getId() + "', '" 
				+ escape_string(serie->getTitre()) + "', '" 
				+ escape_string(serie->getLien()) + "', " 
				+ to_string(serie->getAnnee()) + ", '" 
				+ escape_string(serie->getSynopsis()) + "', '" 
				+ escape_string(serie->getAffiche()) + "', '" 
				+ escape_string(serie->getPays()) + "', " 
				+ to_string(vu) + ", " + to_string(aVoir) + ");";
		
		//on effectue la requête
		this->database->query(sql);
			
		//on insère les acteurs & les réalisateurs en base
		//on récupère les listes des acteurs & réalisateurs
		vector<string> acteurs = serie->getActeurs();
		vector<string> realisateurs = serie->getReal();
			
		//parcours de la liste des acteurs
		for(const auto &acteur: acteurs) {
			this->addActeur(acteur, serie->getId());
		}
			
		//parcours de la liste des réalisateurs
		for(const auto &realisateur: realisateurs) {
			this->addRealisateur(realisateur, serie->getId());
		}
			
	} else { //sinon, on le met à jour
		sql = "UPDATE Series "
				"SET vu = " + to_string(vu) 
				+ ", aVoir = " + to_string(aVoir) 
				+ " WHERE id_serie = '" + serie->getId() + "';";
		//on effectue la requête
		this->database->query(sql);
	}
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant ou mettant à jour jour un épisode dans la base
* \param episode shared_ptr vers l'épisode à traiter
*/
void ComportementSQL::traiterEpisode(shared_ptr<Episode> episode, string id_serie, bool vu, bool aVoir) {
	
	string sql;
	string sql_test_existence = "SELECT * FROM Episodes WHERE id_episode = '" + episode->getId() + "';";
	
	//si le film n'est pas déjà présent en base, on l'ajoute
	if( this->database->isReturnEmpty(sql_test_existence) ) {	
			
		sql = "INSERT INTO Episodes "
				"VALUES ('" + episode->getId() 
				+ "', '" + escape_string(episode->getTitre())
				+ "', '" + escape_string(episode->getLien()) 
				+ "', " + to_string(episode->getAnnee()) 
				+ ", '" + escape_string(episode->getAffiche())
				+ "', '" + escape_string(episode->getSynopsis()) 
				+ "', " + to_string(episode->getNumero())
				+ ", " + to_string(episode->getSaison()) 
				+ ", '" + id_serie
				+ "', '" + escape_string(episode->getPays())
				+ "', " + to_string(vu) + ", " + to_string(aVoir) + ");";

		//on effectue la requête
		this->database->query(sql);
			
		//on insère les acteurs & les réalisateurs en base
		//on récupère les listes des acteurs & réalisateurs
		vector<string> acteurs = episode->getActeurs();
		vector<string> realisateurs = episode->getReal();
	
		//parcours de la liste des acteurs
		for(const auto &acteur: acteurs) {
			this->addActeur(acteur, episode->getId());
		}
	
		//parcours de la liste des réalisateurs
		for(const auto &realisateur: realisateurs) {
			this->addRealisateur(realisateur, episode->getId());
		}
	
	} else { //sinon, on le met à jour
		sql = "UPDATE Episodes "
				"SET vu = " + to_string(vu) 
				+ ", aVoir = " + to_string(aVoir) 
				+ " WHERE id_episode = '" + episode->getId() + "';";
		//on effectue la requête
		this->database->query(sql);
	}
}
