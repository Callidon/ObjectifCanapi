/*!
* \file FactoryOMDBFilm.hpp
* \brief Fichier contenant la définition de la classe FactoryOMDBFilm
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef FACTORYOMDBFILM_H
#define FACTORYOMDBFILM_H

#include "FactoryOMDB.hpp"


//--------------------------------------------------
/*!
* \class FactoryOMDBFilm
* \brief Classe réalisant l'interface FactoryOMDB & instanciant des objets de type Film
*/

class FactoryOMDBFilm : public FactoryOMDB {
	
	private:
		//Méthodes privées
		std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
		std::string queryTitle(std::string title);
		
	public:
		//Constructeur & destructeur
		FactoryOMDBFilm();
		~FactoryOMDBFilm();
		
		//Méthode publique
		std::shared_ptr<Video> makeVideo(std::string title);
};

//--------------------------------------------------
#endif
