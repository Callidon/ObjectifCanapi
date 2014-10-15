/*!
* \file Saison.hpp
* \brief Fichier contenant les entêtes de la classe Episodes
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Personne_H
#define Personne_H

class Video;

#include <string>
#include <vector>
#include <memory>
//--------------------------------------------------
/*!
* \class Personne
*/
class Personne {
	private:
		//Attributs
		std::string nom;
		std::string prenom;
		
	public:
		//Constructeur & destructeur
		Personne(std::string nom, std::string prenom);
		~Personne();
		//Methodes
		std::string getNom();
		void setNom(std::string nom);
		std::string getPrenom();
		void setPrenom(std::string prenom);
};
//--------------------------------------------------
#endif
