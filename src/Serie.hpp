/*!
* \file Serie.hpp
* \brief Fichier contenant les entêtes de la classe Serie
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef Video_H
#define Video_H

#include "Observateur.hpp"

#include <string>
//--------------------------------------------------
/*!
* \class Serie
*/
class Serie {
	private:
		//Attributs
		std::string titre;
		int annee;
		bool en_cours;
		std::string lien; //lien vers BA
		std::string affiche;
		bool vu;
		bool aVoir;
		Observateur * observateur;
		
	public:
		//Constructeur & destructeur
		Serie(string titre, int annee, string lien, string affiche);
		~Serie();
		//Methodes
		void lire();
		string getStatutSerie(); //en cours ou terminée
		void setStatutSerie(bool ec); //ec = en cours
		string getLien();
		void setLien(string lien);
		//void marquerVu();
		//void marquerVoir();
		
};
//--------------------------------------------------
#endif
