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
* \param fichier_db NOm du fichier contenant la base de données
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
