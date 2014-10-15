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
*/
void BDConnector::creerNewBD(string user) {
	string nom_fichier = user + ".db";
	string commande = "cp database/default.db database/" + nom_fichier;
	system((char*)commande.c_str());
	
}

//--------------------------------------------------
/*!
* \brief Méthode qui exécute la requête SQL passée en en paramètre
*/
vector<vector<string> > BDConnector::query(string sql_query) {
	sqlite3_stmt *statement;
	vector<vector<string> > resultats;
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
			resultats.push_back(temp);
			//on avance à la ligne suivante
			result = sqlite3_step(statement);
		}
		sqlite3_finalize(statement);
	}
	return resultats;
}

//--------------------------------------------------
/*!
* \brief Méthode qui compte le nombre de lignes dans une table de la base de données
*/
int BDConnector::count(string nom_table) {
	vector<vector<string> > table = this->query("SELECT COUNT(*) FROM " + nom_table + ";");
	int res = atoi(table[0][0].c_str());
	return res;
}
