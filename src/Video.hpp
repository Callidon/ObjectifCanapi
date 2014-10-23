/*!
* \file Video.hpp
* \brief Fichier contenant les entêtes de l'interface Video
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Video_H
#define Video_H

#include "Personne.hpp"

#include <string>
#include <vector>
#include <memory>
#include <stdlib.h>

//--------------------------------------------------
/*!
* \class Video
*/
class Video {
	private:
		//Attributs
		std::string id;
		std::string titre;
		std::string lien; //lien vers BA
		int annee;
		std::string synopsis;
		std::vector<std::string> acteurs;
		std::vector<std::string> realisateurs;
		
	protected:
		bool vu;
		bool aVoir;
		
	public:
		//Constructeur & destructeur
		Video(std::string id, std::string titre, std::string lien, std::string synopsis, int annee);
		Video(std::string id, std::string titre, std::string lien, std::string synopsis, int annee, std::vector<std::string> acteurs, std::vector<std::string> real);
		~Video();
		//Méthodes
		std::string getId();
		void setId(int id);
		std::string getTitre();
		void setTitre(std::string titre);
		std::string getLien();
		void setLien(std::string lien);
		int getAnnee();
		void setAnnee(int annee);
		std::string getSynopsis();
		void setSynopsis(std::string syno);
		std::vector<std::string> getActeurs();
		void addActeur(std::string acteur);
		std::vector<std::string> getReal();
		void addReal(std::string real);
		
		virtual std::string getStatut() = 0; //"à voir" ou "vu"
		void marquerVu();
		void marquerVoir();
		
		void lire(); //lire BA
};
//--------------------------------------------------
#endif
