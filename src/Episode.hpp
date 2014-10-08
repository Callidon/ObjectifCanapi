/*!
* \file Saison.hpp
* \brief Fichier contenant les entêtes de la classe Episodes
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Episode_H
#define Episode_H

#include "Video.hpp"

#include <string>

//--------------------------------------------------
/*!
* \class Episode
*/
class Episode : public virtual Video {
	private:
		//Attributs
		int numero;
		int saison;
		std::string serie;
		
	public:
		//Constructeur & destructeur
		Episode(std::string titre, std::string lien, int annee, int numero, int saison, std::string serie, std::string synopsis);
		~Episode();
		//Methodes
		int getNumero();
		void setNumero(int num);
		int getSaison();
		void setSaison(int num);
		std::string getSerie();
		void setSerie(std::string serie);
		//Méthode héritée de Video
		virtual std::string getStatut();
};
//--------------------------------------------------
#endif
