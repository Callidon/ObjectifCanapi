/*!
* \file Factory.hpp
* \brief Fichier contenant la définition de l'interface Factory
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <vector>
#include <string>
#include "../Video/Film.hpp"
#include "../Video/Episode.hpp"
#include "../Video/Serie.hpp"

//--------------------------------------------------
/*!
* \class Factory
* \brief Interface représentant une fabrique d'objets de type Video
*/

class Factory {
	
	/*public:
		virtual std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir) = 0;
		virtual std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays) = 0;
		*/
};

//--------------------------------------------------
#endif
