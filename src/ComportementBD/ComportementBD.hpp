/*!
* \file ComportementBD.hpp
* \brief Fichier contenant les entêtes de l'interface ComportementBD
* \author Camille Le Luët
* \author Thomas Minier
* \date 22.11.2014
*/

#ifndef COMPORTEMENTBD_H
#define COMPORTEMENTBD_H
#include <string>
#include <vector>
#include <memory>
#include "../Video/Film.hpp"
#include "../Video/Serie.hpp"

//--------------------------------------------------
/*!
* \class ComportementBD
* \brief Interface représentant un comportement vis à vis d'une base de données
*/
class ComportementBD {
		
	protected:
		//Méthodes protected
		virtual void addActeur(std::string nom, std::string id_video) = 0;
		virtual void addRealisateur(std::string nom, std::string id_video) = 0; 
		
	public:
		//Méthodes publiques
		virtual void traiterFilm(std::shared_ptr<Film> film, bool vu, bool aVoir) = 0;
		virtual void traiterSerie(std::shared_ptr<Serie> serie, bool vu, bool aVoir) = 0;
		virtual void traiterEpisode(std::shared_ptr<Episode> episode, std::string id_serie, bool vu, bool aVoir) = 0;

};
//--------------------------------------------------
#endif
