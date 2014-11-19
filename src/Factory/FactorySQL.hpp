/*!
* \file FactorySQL.hpp
* \brief Fichier contenant la définition de la classe FactorySQL
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORYSQL_H
#define FACTORYSQL_H

#include <memory>
#include <vector>
#include <string>
#include "Factory.hpp"
#include "../BDConnector/BDConnector.hpp"

//--------------------------------------------------
/*!
* \class FactorySQL
* \brief Classe réalisant l'interface Factory & instanciant des objets de type Video
*/

class FactorySQL: public Factory {
	
	private:
		std::shared_ptr<BDConnector> bd; //!< Connecteur vers la base de donnée où sont stocké les informations
		
	public:
		FactorySQL(std::shared_ptr<BDConnector> base);
		~FactorySQL();
		std::vector<std::shared_ptr<Video> > recupererAllFilms();
		std::vector<std::shared_ptr<Video> > recupererAllSeries();
		std::shared_ptr<Serie> genererSerie(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir);
		std::shared_ptr<Episode> genererEpisode(std::string id,std::string titre, std::string lien, int annee, std::string affiche, int numero, int saison, std::string id_serie, std::string synopsis, std::string pays, bool vu, bool aVoir);

		std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir);
};

//--------------------------------------------------
#endif
