/*!
* \file FactoryOMDB.hpp
* \brief Fichier contenant la définition de l'interface FactoryOMDB
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef FACTORYOMDB_H
#define FACTORYOMDB_H

#include <memory>
#include <vector>
#include <string>
#include "../Video/Film.hpp"
#include "../Video/Episode.hpp"
#include "../Video/Serie.hpp"


//--------------------------------------------------
/*!
* \class FactoryOMDB
* \brief Interface représentant une fabrique créant des objets de type Video à partir de l'APi du site IMDB
*/

class FactoryOMDB {
		
	private:
		//Méthode privée
		virtual std::string queryTitle(std::string title) = 0;
		
	public:
		//Méthode publique
		virtual std::shared_ptr<Video> makeVideo(std::string title) = 0;
};

//--------------------------------------------------
#endif

