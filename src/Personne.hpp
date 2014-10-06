/*!
* \file Saison.hpp
* \brief Fichier contenant les entêtes de la classe Episodes
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Personne_H
#define Personne_H

#include "Video.hpp" 

#include <string>
#include <list>
//--------------------------------------------------
/*!
* \class Personne
*/
class Personne {
	private:
		//Attributs
		std::string nom;
		std::string prenom;
		std::list<Video> films;
		
	public:
		//Constructeur & destructeur
		Personne(std::string nom, std::string prenom);
		~Personne();
		//Methodes
		std::string getNom();
		void setNom(std::string nom);
		std::string getPrenom();
		void setPrenom(std::string prenom);
		std::list<Video> getFilms();
};
//--------------------------------------------------
#endif
