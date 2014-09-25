/*!
* \file BDConnector.hpp
* \brief Fichier contenant les entêtes de la classe BDConnector
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef BDConnector_H
#define BDConnector_H
#include <string>
#include "../libs/sqlite3/sqlite3.hpp"

//--------------------------------------------------
/*!
* \class BDConnector
* \brief Classe simplifiant l'usage de la bibliothèque sqlite3
*/
class BDConnector {
	private:
		//Attributs
		sqlite3 * db; //!<Pointeur vers la base de données
		char *zErrMsg; //!<Pointeur vers le message d'erreur
		
	public:
		//Constructeur & destructeur
		BDConnector(string fichier_db);
		~BDConnector();
		//Méthodes
		void query(string sql_query);
};
//--------------------------------------------------
#endif
