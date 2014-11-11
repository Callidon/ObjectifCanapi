/*!
* \file Bibliotheque.hpp
* \brief Fichier contenant les entêtes de la classe Bibliotheque
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Bibliotheque_H
#define Bibliotheque_H

#include "Video.hpp"
#include "FactorySQL.hpp"
#include "FactoryOMDB.hpp"

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
		std::shared_ptr<FactoryOMDB> factoryOMDB; //!< Factory servant à créer les nouveaux films & séries
		
	public:
		//Constructeur & destructeur
		Bibliotheque(std::string user);
		~Bibliotheque();
		//Methodes
		std::string getUser();
		void setUser(std::string user);
		std::vector<std::shared_ptr<Video> > getVideos();
		void addVideo(std::string nom_video, std::string type_video);
		void selectVideo(std::string titre);
		void setStatutCurrentVideo(bool vu, bool aVoir);
};
//--------------------------------------------------
#endif
