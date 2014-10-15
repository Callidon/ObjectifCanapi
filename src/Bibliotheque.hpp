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
#include "BDConnector.hpp"

#include <string>
//--------------------------------------------------
/*!
* \class Bibliotheque
*/
class Bibliotheque {
	private:
		//Attributs
		std::vector<std::shared_ptr<Video> > videos;
		std::string user;
		std::shared_ptr<BDConnector> DataBase;
		
	public:
		//Constructeur & destructeur
		Bibliotheque(std::string user);
		~Bibliotheque();
		//Methodes
		std::string getUser();
		void setUser(std::string user);
		std::vector<std::shared_ptr<Video> > getVideos();
		void addVideo(std::shared_ptr<Video> video);
};
//--------------------------------------------------
#endif
