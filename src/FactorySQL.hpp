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

class FactorySQL: public Factory {
	
	public:
		FactorySQL();
		~FactorySQL();
		std::list<Video> generateMedia(std::list<std::string>);
}

//--------------------------------------------------
#endif
