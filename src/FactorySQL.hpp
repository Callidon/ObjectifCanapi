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
#include "BDConnector.hpp"

//--------------------------------------------------
/*!
* \class FactorySQL
* \brief Classe réalisant l'interface Factory & instanciant des objets de type Video
*/

class FactorySQL {
	
	private:
		std::shared_ptr<BDConnector> bd; //<! Connecteur vers la base de donnée où sont stocké les informations
		
	public:
		FactorySQL(std::shared_ptr<BDConnector> base);
		~FactorySQL();
		//Méthodes héritée de Factory
		virtual std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis);
		virtual std::shared_ptr<Episode> genererEpisode(std::string id,std::string titre, std::string lien, int annee, int numero, int saison, std::string serie, std::string synopsis);
};

//--------------------------------------------------
#endif
