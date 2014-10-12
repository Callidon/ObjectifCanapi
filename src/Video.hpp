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
		std::string titre;
		std::string lien; //lien vers BA
		int annee;
		std::string synopsis;
		std::vector<std::shared_ptr<Personne> > acteurs;
		std::vector<std::shared_ptr<Personne> > realisateurs;
		
	protected:
		bool vu;
		bool aVoir;
		
	public:
		//Constructeur & destructeur
		Video(std::string titre, std::string lien, std::string synopsis, int annee);
		~Video();
		//Méthodes
		std::string getTitre();
		void setTitre(std::string titre);
		std::string getLien();
		void setLien(std::string lien);
		int getAnnee();
		void setAnnee(int annee);
		std::vector<std::shared_ptr<Personne> > getActeurs();
		void addActeur(std::shared_ptr<Personne> acteur);
		std::vector<std::shared_ptr<Personne> > getReal();
		void addReal(std::shared_ptr<Personne> real);
		
		virtual std::string getStatut() = 0; //"à voir" ou "vu"
		void marquerVu();
		void marquerVoir();
		
		void lire(); //lire BA
};
//--------------------------------------------------
#endif
