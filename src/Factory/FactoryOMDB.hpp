/*!
* \file FactoryOMDB.hpp
* \brief Fichier contenant la définition de la classe FactoryOMDB
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef FACTORYOMDB_H
#define FACTORYOMDB_H

#include "FactoryIMDB.hpp"


//--------------------------------------------------
/*!
* \class FactoryOMDB
* \brief Classe réalisant l'interface FactoryIMDB & qui interargit avec l'api OMDB pour créer des objets Video
*/

class FactoryOMDB : public FactoryIMDB {
		
	public:
		FactoryOMDB();
		~FactoryOMDB();
		
		std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
		
		std::string queryTitle(std::string title);
		std::string querySerie(std::string title);
		std::shared_ptr<Film> makeVideo(std::string res);
		std::shared_ptr<Serie> makeSerie(std::string res);
};

//--------------------------------------------------
#endif
