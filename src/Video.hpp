/*!
* \file Video.hpp
* \brief Fichier contenant les entêtes de l'interface Video
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Video_H
#define Video_H


#include <string>
#include <vector>
#include <memory>
#include <stdlib.h>

//--------------------------------------------------
/*!
* \class Video
*/
class Episode;

class Video {
	private:
		//Attributs
		std::string id;
		std::string titre;
		std::string lien; //lien vers BA
		int annee;
		std::string affiche;
		std::string pays;
		std::string synopsis;
		std::vector<std::string> acteurs;
		std::vector<std::string> realisateurs;
		
	protected:
		bool vu;
		bool aVoir;
		
	public:
		//Constructeur & destructeur
		Video(std::string id, std::string titre, std::string lien, std::string synopsis, int annee, std::string affiche, std::string pays);
		Video(std::string id, std::string titre, std::string lien, std::string synopsis, int annee, std::string affiche, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
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
		std::string getAffiche();
		void setAffiche(std::string aff);
		std::string getPays();
		void setPays(std::string pays);
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
		/*
		virtual std::vector<std::shared_ptr<Episode> > getEpisodes();
		virtual void addEpisode(std::shared_ptr<Episode> ep);
		
		virtual int getNumero();
		virtual void setNumero(int num);
		
		virtual int getSaison();
		virtual void setSaison(int num);
		
		virtual std::string getSerie();
		virtual void setSerie(std::string serie);
		*/
};
//--------------------------------------------------
#endif
