/*!
* \file Video.hpp
* \brief Fichier contenant les entêtes de la classe Film
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Film_H
#define Film_H

#include "Video.hpp"

#include <string>
//--------------------------------------------------
/*!
* \class Film
*/
class Film : public virtual Video {
	private:
		//Attributs
		std::string affiche; //lien vers affiche
		
	public:
		//Constructeur & destructeur
		Film(std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis);
		~Film();
		//Methodes
		std::string getAffiche(); //afficher l'affiche
		void setAffiche(std::string aff);
		//Méthode héritée de Video
		virtual std::string getStatut();
};
//--------------------------------------------------
#endif