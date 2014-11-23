/*!
* \file FactoryIMDB.hpp
* \brief Fichier contenant la définition de l'interface FactoryIMDB
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FACTORYIMDB_H
#define FACTORYIMDB_H

#include <memory>
#include <vector>
#include <string>
#include "../Video/Film.hpp"
#include "../Video/Episode.hpp"
#include "../Video/Serie.hpp"


//--------------------------------------------------
/*!
* \class FactoryIMDB
* \brief Interface représentant une fabrique créant des objets de type Film et Serie à partir de l'APi du site IMDB
*/

class FactoryIMDB {
		
	public:
		
		virtual std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays) = 0;
		
		virtual std::string queryTitle(std::string title) = 0;
		virtual std::string querySerie(std::string title) = 0;
		virtual std::shared_ptr<Film> makeVideo(std::string res) = 0;
		virtual std::shared_ptr<Serie> makeSerie(std::string res) = 0;
};

//--------------------------------------------------
#endif

