/*!
* \file Observateur.hpp
* \brief Fichier contenant la définition de l'interface Observateur
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

class Video;
//--------------------------------------------------
/*!
* \class Observateur
* \brief Interface représentant un observateur générique
*/

class Observateur {
	
	public:
		virtual void notifier(Video * video) = 0;
			
};

//--------------------------------------------------
#endif
