/*!
* \file FactoryOMDBSerie.hpp
* \brief Fichier contenant la définition de la classe FactoryOMDBSerie
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef FACTORYOMDBSERIE_H
#define FACTORYOMDBSERIE_H

#include "FactoryOMDB.hpp"


//--------------------------------------------------
/*!
* \class FactoryOMDB
* \brief Classe réalisant l'interface FactoryIMDB & qui interargit avec l'api OMDB pour créer des objets Video
*/

class FactoryOMDBSerie : public FactoryOMDB {
	
	private:
		//Méthode privée	
		std::string queryTitle(std::string title);
	
	public:
		FactoryOMDBSerie();
		~FactoryOMDBSerie();
		
		std::shared_ptr<Video> makeVideo(std::string title);
};

//--------------------------------------------------
#endif
