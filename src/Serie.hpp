/*!
* \file Serie.hpp
* \brief Fichier contenant les entêtes de la classe Serie
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Serie_H
#define Serie_H

#include "Video.hpp"
#include "Episode.hpp"

#include <string>
//--------------------------------------------------
/*!
* \class Serie
* \brief Classe héritant de Video et représentant une série TV
*/
class Serie : public virtual Video {
	private:
		//Attributs
		std::vector<std::shared_ptr<Episode>> episodes;
		
	public:
		//Constructeur & destructeur
		Serie(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays);
		Serie(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
		~Serie();
		//Methodes
		void addEpisode(std::shared_ptr<Episode> ep);
		std::vector<std::shared_ptr<Episode>> getEpisodes();
		//Méthode héritée de Video
		virtual std::string getStatut();
};
//--------------------------------------------------
#endif
