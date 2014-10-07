/*!
* \file Factory.hpp
* \brief Fichier contenant la définition de l'interface Factory
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORY_H
#define FACTORY_H

#include <list>
#include <string>
#include "Video.hpp"

//--------------------------------------------------
/*!
* \class Factory
* \brief Interface représentant une fabrique d'objets de type Video
*/

class Factory {
	
	public:
		virtual Video * generateMedia(std::list<std::string> listeParams, std::string typeVideo) = 0;
			
};

//--------------------------------------------------
#endif
