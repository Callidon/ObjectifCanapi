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
		virtual std::vector<std::shared_ptr<Video> > recupererAll() = 0;
		
		/*virtual std::shared_ptr<Serie> genererSerie(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir) = 0;
		virtual std::shared_ptr<Episode> genererEpisode(std::string id,std::string titre, std::string lien, int annee, std::string affiche, int numero, int saison, std::string id_serie, std::string synopsis, std::string pays, bool vu, bool aVoir) = 0;
		virtual std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir) = 0;
	*/
};

//--------------------------------------------------
#endif

