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
#include <vector>
#include <memory>
#include "../libs/sqlite/sqlite3.h"
class Video;

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
		void swapUser(std::string fichier_db);
		void creerNewBD(std::string user);
		std::vector<std::vector<std::string> > query(std::string sql_query);
		int count(std::string nom_table);
		int lastId(std::string nom_id, std::string nom_table);
		int nextIdToInsert(std::string nom_id, std::string nom_table);
};
//--------------------------------------------------
#endif
