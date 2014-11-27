/*!
* \file Video.hpp
* \brief Fichier contenant les entêtes de l'interface Video
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
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
* \brief Classe représentant une vidéo générique
*/
class Episode;

class Video {
	private:
		//Attributs privés
		std::string id; //!< Identifiant (unique) de la vidéo
		std::string titre; //!< Titre de la vidéo
		std::string lien; //!< Lien vers la bande-annonce
		int annee; //!< Année de diffusion
		std::string affiche; //!< Lien vers l'affiche de la vidéo
		std::string pays; //!< Pays associé
		std::string synopsis; //!< Synopsis de la vidéo
		std::vector<std::string> acteurs; //!< Liste des acteurs jouant dans la vidéo
		std::vector<std::string> realisateurs; //!< Liste des réalisateurs ayant participé à la video
		
	protected:
		//Attributs protected
		bool vu; //!< Si la vidéo a été vu
		bool aVoir; //!< Si la vidéo est à voir
		
	public:
		//Constructeurs & destructeur
		Video(std::string id, std::string titre, std::string lien, std::string synopsis, int annee, std::string affiche, std::string pays);
		Video(std::string id, std::string titre, std::string lien, std::string synopsis, int annee, std::string affiche, std::vector<std::string> acteurs, std::vector<std::string> real, std::string pays);
		~Video();
		//Méthodes publiques
		std::string getId();
		void setId(string id);
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
};
//--------------------------------------------------
#endif
