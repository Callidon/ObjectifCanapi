/*!
* \file FactorySQL.hpp
* \brief Fichier contenant la définition de la classe FactorySQL
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORYSQL_H
#define FACTORYSQL_H

#include "Factory.hpp"

//--------------------------------------------------
/*!
* \class FactorySQL
* \brief Classe réalisant l'interface Factory & instanciant des objets de type Video
*/

class FactorySQL: virtual public Factory {
	
	public:
		FactorySQL();
		~FactorySQL();
		//Méthode héritée de Factory
		virtual Video * generateMedia(std::list<std::string> listeParams, std::string typeVideo);
};

//--------------------------------------------------
#endif
