/*!
* \file FactoryBD.hpp
* \brief Fichier contenant la définition de l'interface FactoryBD
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORYBD_H
#define FACTORYBD_H

#include <memory>
#include <vector>
#include <string>
#include "../Video/Film.hpp"
#include "../Video/Episode.hpp"
#include "../Video/Serie.hpp"


//--------------------------------------------------
/*!
* \class FactoryBD
* \brief Interface représentant une fabrique instanciant des objets de type Film, Serie & Video à patir d'une base de données
*/

class FactoryBD {
		
	public:
		virtual std::vector<std::shared_ptr<Video> > recupererAllFilms() = 0;
		virtual std::vector<std::shared_ptr<Video> > recupererAllSeries() = 0;
		
		virtual std::shared_ptr<Serie> genererSerie(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir) = 0;
		virtual std::shared_ptr<Episode> genererEpisode(std::string id,std::string titre, std::string lien, int annee, std::string affiche, int numero, int saison, std::string id_serie, std::string synopsis, std::string pays, bool vu, bool aVoir) = 0;
		virtual std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir) = 0;
};

//--------------------------------------------------
#endif

