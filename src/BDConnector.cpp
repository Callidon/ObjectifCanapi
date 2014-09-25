/*!
* \file BDConnector.cpp
* \brief Fichier contenant l'implémentation de la classe BDConnector
* \author Camille Le LUët
* \author Thomas Minier
* \date ?
*/
#include "BDConnector.hpp"
#include <iostream>
using namespace std;

//Fonction de callback [WORK IN PROGRESS]
//azColName = pointeur vers un tab de string contenant les noms de colonnes
//argv = pointeur vers un tab de tab de string contenant les valeurs de chaque colonnes
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
BDConnector::BDConnector(string fichier_db) {
	int rc;
	//connexion à la base de données
	rc = sqlite3_open(fichier_db, &db);
   if( rc ) { //si la connexion a échouée
      cout << "Erreur : impossible de se connecter à la base de données" << endl;
   }
   this.zErrMsg = 0; //initilisation de l'attribut zErrMsg
}
*
//--------------------------------------------------
/*!
* \brief Destructeur
*/
BDConnector::~BDConnector() {
	//fermeture de la connexion à la base
	sqlite3_close(this.db);
}
*
//--------------------------------------------------
/*!
* \brief Méthode qui exécute la requête SQL passée en en paramètre
*/
BDConnector::query(string sql_query) {
	//TODO
	//Hey ! Tu veux t'inscrire au club Math ? <3 <3 <3 <3
}
