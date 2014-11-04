/*!
* \file Episode.hpp
* \brief Fichier contenant les entêtes de la classe Episodes
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Episode_H
#define Episode_H

#include "Video.hpp"

#include <string>
#include <vector>

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
		Episode(std::string id, std::string titre, std::string lien, int annee, std::string affiche, int numero, int saison, std::string serie, std::string synopsis, std::string pays);
		Episode(std::string id, std::string titre, std::string lien, int annee, std::string affiche, int numero, int saison, std::string serie, std::string synopsis , std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
		Episode(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis , std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
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
