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
#include "../../libs/sqlite/sqlite3.h"
#include "../Video/Film.hpp"
#include "../Video/Serie.hpp"

//--------------------------------------------------
/*!
* \class BDConnector
* \brief Classe simplifiant l'usage de la bibliothèque sqlite3
*/
class BDConnector {
	private:
		//Attributs
		sqlite3 * db; //!<Pointeur vers la base de données
		//Méthodes privées
		void addActeur(std::string acteur, std::string id_video);
		void addRealisateur(std::string real, std::string id_video);
		
	public:
		//Constructeur & destructeur
		BDConnector(std::string fichier_db);
		~BDConnector();
		//Méthodes publiques
		void swapUser(std::string fichier_db);
		void creerNewBD(std::string user);
		std::vector<std::vector<std::string> > query(std::string sql_query);
		int count(std::string nom_table);
		int lastId(std::string nom_id, std::string nom_table);
		int nextIdToInsert(std::string nom_id, std::string nom_table);
		bool isReturnEmpty(std::string sql_query);
};
//--------------------------------------------------
#endif
