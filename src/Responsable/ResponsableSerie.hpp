/*!
* \file ResponsableSerie.hpp
* \brief Fichier contenant les entêtes de la classe ResponsableSerie
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef RESPONSABLESERIE_H
#define RESPONSABLESERIE_H
#include "Responsable.hpp"
#include "../Video/Serie.hpp"

//--------------------------------------------------
/*!
* \class ResponsableSerie
* \brief Classe représentant un responsable chargé de traiter des objets Serie
*/
class ResponsableSerie : public Responsable {
		
	public:
		//Constructeur & destructeur
		ResponsableSerie(std::shared_ptr<BDConnector> db);
		~ResponsableSerie();
		//Méthode publique
		void traiter(std::shared_ptr<Video> video, bool vu, bool aVoir);

};
//--------------------------------------------------
#endif



