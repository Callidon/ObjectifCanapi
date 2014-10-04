/*!
* \file BDConnector.hpp
* \brief Fichier contenant les entêtes de la classe BDConnector
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef BDCONNECTOR_H
#define BDCONNECTOR_H
#include <string>
#include "../libs/sqlite/sqlite3.h"

//--------------------------------------------------
/*!
* \class BDConnector
* \brief Classe simplifiant l'usage de la bibliothèque sqlite3
*/
class BDConnector {
	private:
		//Attributs
		sqlite3 * db; //!<Pointeur vers la base de données
		
	public:
		//Constructeur & destructeur
		BDConnector(std::string fichier_db);
		~BDConnector();
		//Méthodes
		std::list<std::list<std::string> > query(std::string sql_query);
};
//--------------------------------------------------
#endif
