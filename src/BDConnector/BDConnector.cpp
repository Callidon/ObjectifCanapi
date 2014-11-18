/*!
* \file BDConnector.cpp
* \brief Fichier contenant l'implémentation de la classe BDConnector
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "BDConnector.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
* \param fichier_db Nom du fichier contenant la base de données
*/
BDConnector::BDConnector(string fichier_db) {
	int rc;
	//connexion à la base de données
	rc = sqlite3_open((char*)fichier_db.c_str(), &db);
   if( rc ) { //si la connexion a échouée
		cout << "Erreur : impossible de se connecter à la base de données " << fichier_db << endl;
   }
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
BDConnector::~BDConnector() {
	//fermeture de la connexion à la base
	sqlite3_close(this->db);
}

//--------------------------------------------------
/*!
* \brief Méthode qui permet de changer d'utilisateur
* \param fichier_db Nom du nouveau fichier contenant la base de données
*/
void BDConnector::swapUser(string fichier_db) {
	int rc;
	//fermeture de la connexion à la base actuelle
	sqlite3_close(this->db);
	//connexion à la nouvelle  base de données
	rc = sqlite3_open((char*)fichier_db.c_str(), &db);
	if( rc ) { //si la connexion a échouée
		cout << "Erreur : impossible de se connecter à la base de données " << fichier_db << endl;
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui crée une nouvelle base de donnée pour un nouvel utilisateur
* \param user Nom du nouvel utlisateur
*/
void BDConnector::creerNewBD(string user) {
	string nom_fichier = user + ".db";
	string commande = "cp database/default.db database/" + nom_fichier;
	system((char*)commande.c_str());
	
}

//--------------------------------------------------
/*!
* \brief Méthode qui exécute la requête SQL passée en en paramètre
* \param sql_query Requête SQL à exécuter
* \return Table correspondant à la requête SQL passée en paramètre
*/
vector<vector<string> > BDConnector::query(string sql_query) {
	sqlite3_stmt *statement;
	vector<vector<string> > results;
	char * requete = (char*)sql_query.c_str();
	int ind;
	//exécution de la requête & vérification que tout s'est bien passé
	if( sqlite3_prepare_v2(this->db, requete, -1, &statement, 0) == SQLITE_OK) {
		//on récupère le nombre de colonnes
		int nb_cols = sqlite3_column_count(statement);
		//on récupère la 1ère ligne
		int result = sqlite3_step(statement);
		//tant qu'il reste des lignes à traiter
		while(result == SQLITE_ROW) {
			//liste temporaire contenant la ligne courante
			vector<string> temp;
			//on insère toutes les valeurs de la ligne dans la liste temporaire
			for(ind = 0; ind < nb_cols; ind++) {
				string val((char*)sqlite3_column_text(statement, ind)); 
				temp.push_back(val);
			}
			//on ajoute la liste temporaire à la liste des résultats
			results.push_back(temp);
			//on avance à la ligne suivante
			result = sqlite3_step(statement);
		}
		sqlite3_finalize(statement);
	} else {
		cout << sqlite3_errmsg(this->db) << endl;
	}
	return results;
}

//--------------------------------------------------
/*!
* \brief Méthode qui compte le nombre de lignes dans une table de la base de données
* \param nom_table Nom de la table sur laquelle effectuer l'opération
* \return Nombre de lignes présentes dans la table
*/
int BDConnector::count(string nom_table) {
	//on fait la requête pour récupérer le nombre de lignes dans la table
	vector<vector<string> > table = this->query("SELECT COUNT(*) FROM " + nom_table + ";");
	int res = atoi(table[0][0].c_str()); //conversion de la string en int
	return res;
}

//--------------------------------------------------
/*!
* \brief Méthode qui renvoie l'id de la dernière ligne de la table. L'i d de cette dernière doit être de type INTEGER
* \param nom_id Nom de l'identifiant de la table
* \param nom_table Nom de la table dont on veut récupérer le dernier id
* \return Id de la dernière ligne de la table
*/
int BDConnector::lastId(string nom_id, string nom_table) {
	//on fait la requête pour récupérer les id de la table classés par ordre décroissant
	vector<vector<string> > table = this->query("SELECT " + nom_id + " FROM " + nom_table + " ORDER BY " + nom_id + " DESC;");
	int res = atoi(table[0][0].c_str()); //conversion de la string en int
	return res;
}

//--------------------------------------------------
/*!
* \brief Méthode qui renvoie le prochain id à insérer dans la table. L'id de cette dernière doit être de type INTEGER
* \param nom_id Nom de l'identifiant de la table
* \param nom_table Nom de la table dont on veut récupérer le prochain id à insérer
* \return Le prochain id à insérer dans la table
*/
int BDConnector::nextIdToInsert(string nom_id, string nom_table) {
	return this->lastId(nom_id, nom_table) + 1;
}

//--------------------------------------------------
/*!
* \brief Méthode qui vérifie si une requête renvoie une table vide
* \param sql_query La requête à tester
* \return Si la table renvoyée par la requête est vide ou non
*/
bool BDConnector::isQueryEmpty(string sql_query) {
	//on récupère la table liée à la requête et on teste si elle ne contient aucun élément
	vector<vector<string> > table = this->query(sql_query);
	return (table.size() == 0);
}

/*
 * Méthodes d'ajouts & de mises à jour des objets contenus dans la base
 */

//--------------------------------------------------
/*!
* \brief Méthode ajoutant un acteur à la base
* \param acteur L'acteur (nom + prénom) à ajouter dans la base
* \param id_video L'id de la vidéo auquel l'acteur est associé
*/
void BDConnector::addActeur(string acteur, string id_video) {
	int id_acteur;
	string sql_insert;
	string sql_recherche = "SELECT * FROM Personnes WHERE nom = '" + acteur + "';";
			
			//si c'est acteur n'est pas déjà présent en base
			if(this->isQueryEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_acteur = this->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert = "INSERT INTO Personnes "
							"VALUES (" + to_string(id_acteur)
							+ ", '" + acteur + "');";
				this->query(sql_insert); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->query(sql_recherche);
				id_acteur = atoi(table[0][0].c_str());
			}
			
			//on associe l'acteur au film grâce à la table Acteurs
			sql_insert = "INSERT INTO Acteurs "
						"VALUES (" + to_string(id_acteur) 
						+ ", '" + id_video + "');";
			this->query(sql_insert);
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant un réalisateur à la base
* \param real Le réalisateur (nom + prénom) à ajouter dans la base
* \param id_video L'id de la vidéo auquel le réalisateur est associé
*/
void BDConnector::addRealisateur(string real, string id_video) {
	int id_real;
	string sql_insert;
	string sql_recherche = "SELECT * FROM Personnes WHERE nom = '" + real + "';";
			
			//si ce réalisateur n'est pas déjà présent en base
			if(this->isQueryEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_real = this->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert = "INSERT INTO Personnes "
							"VALUES (" + to_string(id_real)
							+ ", '" + real + "');";
				this->query(sql_insert); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->query(sql_recherche);
				id_real = atoi(table[0][0].c_str());
			}
			
			//on associe le réalisateur au film grâce à la table Realisateurs
			sql_insert = "INSERT INTO Realisateurs "
						"VALUES (" + to_string(id_real) 
						+ ", '" + id_video + "');";
			this->query(sql_insert);
	
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant un film à la base
* \param film shared_ptr<Film> vers le film à ajouter
* \param vu Booléen indiquant si le film a été vu
* \param aVoir Booléen indiquant si le fim est à voir
*/
void BDConnector::addFilm(shared_ptr<Film> film, bool vu, bool aVoir) {
	//requêtes utilisées pour la recherche & l'ajout en base
	string sql_test_existence = "SELECT * FROM Films WHERE id_film = '" + film->getId() + "';";
			  
	string sql_insert = "INSERT INTO Films "
						"VALUES ('" + film->getId() + "', '" 
						+ film->getTitre() + "', '" 
						+ film->getLien() + "', " 
						+ to_string(film->getAnnee()) + ", '" 
						+ film->getSynopsis() + "', '" 
						+ film->getAffiche() + "', '" 
						+ film->getPays() + "', " 
						+ to_string(vu) + ", " + to_string(aVoir) + ");";
			  
	//si le film n'est pas déjà présent en base, on l'ajoute
	if( this->isQueryEmpty(sql_test_existence) ) {	
		this->query(sql_insert);
	}
}

//--------------------------------------------------
/*!
* \brief Méthode mettant à jour un film présent dans la base
* \param film shared_ptr<Film> vers le film à mettre à jour
* \param vu Booléen indiquant si le film a été vu
* \param aVoir Booléen indiquant si le fim est à voir
*/
void BDConnector::updateFilm(shared_ptr<Film> film, bool vu, bool aVoir) {
	//requêtes utilisées pour la recherche & la mise à jour
	string sql_test_existence = "SELECT * FROM Films WHERE id_film = '" + film->getId() + "';";
	
	string sql_update = "UPDATE Films " 
						"SET vu = " + to_string(vu) 
						+ ", aVoir = " + to_string(aVoir) 
						+ " WHERE id_film = '" + film->getId() + "';";
	
	//si le film est déjà présent en base, on le met à jour
	if(! this->isQueryEmpty(sql_test_existence) ) {	
		this->query(sql_update);
	}
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant une série à la base
* \param serie shared_ptr<Serie> vers la série à ajouter
* \param vu Booléen indiquant si le série a été vue
* \param aVoir Booléen indiquant si la série est à voir
*/
void BDConnector::addSerie(shared_ptr<Serie> serie, bool vu, bool aVoir) {
	//requêtes utlisées pour la recherche & l'ajout en base
	string sql_test_existence = "SELECT * FROM Series WHERE id_serie = '" + serie->getId() + "';";
	
	string sql_insert = "INSERT INTO Series "
						"VALUES ('" + serie->getId() + "', '" 
						+ serie->getTitre() + "', '" 
						+ serie->getLien() + "', " 
						+ to_string(serie->getAnnee()) + ", '" 
						+ serie->getSynopsis() + "', '" 
						+ serie->getAffiche() + "', '" 
						+ serie->getPays() + "', " 
						+ to_string(vu) + ", " + to_string(aVoir) + ");";
	
	//si la série n'est pas déjà présente en base, on l'ajoute
	if( this->isQueryEmpty(sql_test_existence) ) {	
		this->query(sql_insert);
		
		//on ajoute tout ses épisodes dans la base
		vector<shared_ptr<Episode> > episodes = serie->getEpisodes();
		
		for(const auto &episode: episodes) {
			this->addEpisode(episode,false,false);
		}
	}
}

//--------------------------------------------------
/*!
* \brief Méthode mettant à jour une série présente dans la base
* \param serie shared_ptr<Serie> vers la série à mettre à jour
* \param vu Booléen indiquant si le série a été vue
* \param aVoir Booléen indiquant si la série est à voir
*/
void BDConnector::updateSerie(shared_ptr<Serie> serie, bool vu, bool aVoir) {
	//requêtes utlisées pour la recherche & la mise à jour
	string sql_test_existence = "SELECT * FROM Series WHERE id_serie = '" + serie->getId() + "';";
	
	string sql_update = "UPDATE Series "
						"SET vu = " + to_string(vu) 
						+ ", aVoir = " + to_string(aVoir) 
						+ " WHERE id_serie = '" + serie->getId() + "';";
						
	//si la série est déjà présente en base, on la met à jour
	if(! this->isQueryEmpty(sql_test_existence) ) {	
		this->query(sql_update);
	}
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant un épisode à la base
* \param serie shared_ptr<Episode> vers l'épisode à ajouter
* \param vu Booléen indiquant si l'épisode a été vu
* \param aVoir Booléen indiquant si l'épisode est à voir
*/
void BDConnector::addEpisode(shared_ptr<Episode> episode, bool vu, bool aVoir) {
	//requêtes utlisées pour la recherche & l'ajout en base
	string sql_test_existence = "SELECT * FROM Episodes WHERE id_episode = '" + episode->getId() + "';";
	
	string sql_insert = "INSERT INTO Episodes"
						"VALUES ('" + episode->getId() 
						+ "', '" + episode->getTitre()
						+ "', '" + episode->getLien() 
						+ "', " + to_string(episode->getAnnee()) 
						+ "', '" + episode->getAffiche()
						+ "', '" + episode->getSynopsis() 
						+ "', " + to_string(episode->getNumero())
						+ ", " + to_string(episode->getSaison()) 
						+ ", '" + episode->getSerie()
						+ ", '" + episode->getPays()
						+ "', " + to_string(vu) + ", " + to_string(aVoir) + ");";
	
	//si l'épisode n'est pas déjà présent en base, on l'ajoute
	if( this->isQueryEmpty(sql_test_existence) ) {	
		this->query(sql_insert);
	}
}

//--------------------------------------------------
/*!
* \brief Méthode mettant à jour un épisode présent dans la base
* \param serie shared_ptr<Episode> vers l'épisode à mettre à jour
* \param vu Booléen indiquant si l'épisode a été vu
* \param aVoir Booléen indiquant si l'épisode est à voir
*/
void BDConnector::updateEpisode(shared_ptr<Episode> episode, bool vu, bool aVoir) {
	//requêtes utlisées pour la recherche & l'ajout en base
	string sql_test_existence = "SELECT * FROM Episodes WHERE id_episode = '" + episode->getId() + "';";
	
	string sql_update = "UPDATE Episodes "
						"SET vu = " + to_string(vu) 
						+ ", aVoir = " + to_string(aVoir) 
						+ " WHERE id_episode = '" + episode->getId() + "';";
	
	//si l'épisode est déjà présent en base, on le met à jour
	if(! this->isQueryEmpty(sql_test_existence) ) {	
		this->query(sql_update);
	}
}
