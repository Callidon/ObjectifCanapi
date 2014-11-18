/*!
* \file FactoryOMDB.hpp
* \brief Fichier contenant la définition de la classe FactoryOMDB
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORYOMDB_H
#define FACTORYOMDB_H
#include <memory>
#include <vector>
#include <string>
#include "../Video/Film.hpp"
#include "../Video/Serie.hpp"
#include "../Video/Episode.hpp"
#include "../BDConnector/BDConnector.hpp"

//--------------------------------------------------
/*!
* \class FactoryOMDB
* \brief Classe réalisant l'interface Factory & qui interargit avec l'api d'IMDB pour créer des objets Video
*/

class FactoryOMDB {
	
	private:
		std::shared_ptr<BDConnector> bd; //<! Connecteur vers la base de donnée où sont stocké les informations
		
	public:
		FactoryOMDB(std::shared_ptr<BDConnector> base);
		~FactoryOMDB();
		
		std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
		
		std::string queryTitle(std::string title);
		std::string querySerie(std::string title);
		std::shared_ptr<Film> makeVideo(std::string res);
		std::shared_ptr<Serie> makeSerie(std::string res);
};

//--------------------------------------------------
#endif
