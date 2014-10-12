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
		//Méthodes héritée de Factory
		virtual std::shared_ptr<Video> genererFilm(std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis);
		virtual std::shared_ptr<Video> genererEpisode(std::string titre, std::string lien, int annee, int numero, int saison, std::string serie, std::string synopsis);
};

//--------------------------------------------------
#endif
