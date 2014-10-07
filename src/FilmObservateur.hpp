/*!
* \file FilmObservateur.hpp
* \brief Fichier contenant la définition de la classe FilmObservateur
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef FILMOBSERVATEUR_H
#define FILMOBSERVATEUR_H

#include "Observateur.hpp"
#include "BDConnector.hpp"

//--------------------------------------------------
/*!
* \class FilmObservateur
* \brief Classe réalisant l'interface Observateur & mettant à jour les informations des films dans la base 
*/

class FilmObservateur: virtual public Observateur {
	
	private:
		//Attribut
		BDConnector * db; //!<Attribut servant à interargir avec la base de données
	
	public:
		//Constructeur & destructeur
		FilmObservateur(BDConnector * base);
		~FilmObservateur();
		//Méthode héritée de Observateur
		virtual void notifier(Video * video);
};

//--------------------------------------------------
#endif
