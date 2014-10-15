/*!
* \file Factory.hpp
* \brief Fichier contenant la définition de l'interface Factory
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <vector>
#include <string>
#include "Film.hpp"
#include "Episode.hpp"

//--------------------------------------------------
/*!
* \class Factory
* \brief Interface représentant une fabrique d'objets de type Video
*/

class Factory {
	
	public:
		virtual std::shared_ptr<Video> genererFilm(std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis) = 0;
		virtual std::shared_ptr<Video> genererEpisode(std::string titre, std::string lien, int annee, int numero, int saison, std::string serie, std::string synopsis) = 0;
			
};

//--------------------------------------------------
#endif
