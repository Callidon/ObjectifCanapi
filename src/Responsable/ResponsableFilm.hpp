/*!
* \file ResponsableFilm.hpp
* \brief Fichier contenant les entêtes de la classe ResponsableFilm
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef RESPONSABLEFILM_H
#define RESPONSABLEFILM_H
#include "Responsable.hpp"
#include "../Video/Film.hpp"

//--------------------------------------------------
/*!
* \class ResponsableFilm
* \brief Classe représentant un responsable chargé de traiter des objets Film
*/
class ResponsableFilm : public Responsable {
		
	public:
		//Constructeur & destructeur
		ResponsableFilm(std::shared_ptr<BDConnector> db);
		~ResponsableFilm();
		//Méthode publique
		void traiter(std::shared_ptr<Video> video, bool vu, bool aVoir);

};
//--------------------------------------------------
#endif


