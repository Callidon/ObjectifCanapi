/*!
* \file FactorySQL.hpp
* \brief Fichier contenant la définition de l'interface FactorySQL
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef FACTORYSQL_H
#define FACTORYSQL_H

#include <memory>
#include <vector>
#include <string>
#include "../Video/Film.hpp"
#include "../Video/Episode.hpp"
#include "../Video/Serie.hpp"


//--------------------------------------------------
/*!
* \class FactorySQL
* \brief Interface représentant une fabrique instanciant des objets de type Video à patir d'une base de données
*/

class FactorySQL {
	
	
	public:
		//Méthode publique
		virtual std::vector<std::shared_ptr<Video> > recupererAll() = 0;
		
};

//--------------------------------------------------
#endif

