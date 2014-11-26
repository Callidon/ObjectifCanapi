/*!
* \file Bibliotheque.hpp
* \brief Fichier contenant les entêtes de la classe Bibliotheque
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef Bibliotheque_H
#define Bibliotheque_H

#include "Video/Video.hpp"
#include "Factory/FactorySQL.hpp"
#include "Factory/FactoryOMDBFilm.hpp"
#include "Factory/FactoryOMDBSerie.hpp"
#include "Responsable/ResponsableFilm.hpp"

#include <string>
//--------------------------------------------------
/*!
* \class Bibliotheque
* \brief Classe gérant et pilotant une collection de vidéos (films et épisodes)
*/
class Bibliotheque {
	private:
		//Attributs
		std::string user; //!< Utilisateur lié à la bibliothèque
		std::shared_ptr<Video> currentVideo; //!< Vidéo actuellement sélectionnée par la bibliothèque
		std::vector<std::shared_ptr<Video> > videos; //!< Liste des vidéos de la bibliothèque
		std::shared_ptr<BDConnector> database; //!< Base de données liée à la bibliothèque
		std::shared_ptr<ResponsableFilm> responsable; //!< Chaîne de responsabilité chargée de l'ajout & la mise à jour des objets en base
		
	public:
		//Constructeur & destructeur
		Bibliotheque(std::string user);
		~Bibliotheque();
		//Méthodes
		std::string getUser();
		void setUser(std::string user);
		std::vector<std::shared_ptr<Video> > getVideos();
		void addVideo(std::string nom_video, std::string type_video);
		void selectVideo(std::string titre);
		void selectEpisode(std::string titre);
		void setStatutCurrentVideo(bool vu, bool aVoir);
		std::shared_ptr<Video> getCurrentVideo();
};
//--------------------------------------------------
#endif
