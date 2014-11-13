/*!
* \file Film.hpp
* \brief Fichier contenant les entêtes de la classe Film
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Film_H
#define Film_H

#include "Video.hpp"
#include "Serie.hpp"
#include "Episode.hpp"

#include <string>
//--------------------------------------------------
/*!
* \class Film
*/
class Film : public virtual Video {
	private:
		//Attributs
		
	public:
		//Constructeur & destructeur
		Film(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays);
		Film(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
		~Film();
		//Méthode héritée de Video
		virtual std::string getStatut();
		std::shared_ptr<Episode> filmToEpisode();
		std::shared_ptr<Serie> filmToSerie();
};
//--------------------------------------------------
#endif
