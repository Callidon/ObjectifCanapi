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

#include <string>
//--------------------------------------------------
/*!
* \class Bibliotheque
*/
class Bibliotheque {
	private:
		//Attributs
		std::list<Video*> videos;
		std::string user;
		
	public:
		//Constructeur & destructeur
		Bibliotheque(std::string user);
		~Bibliotheque();
		//Methodes
		std::string getUser();
		void setUser(std::string user);
		std::list<Video*> getVideos();
		void addVideo(Video * video);
};
//--------------------------------------------------
#endif
