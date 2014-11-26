/*!
* \file ResponsableEpisode.hpp
* \brief Fichier contenant les entêtes de la classe ResponsableEpisode
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef RESPONSABLEEPISODE_H
#define RESPONSABLEEPISODE_H
#include "Responsable.hpp"
#include "../Video/Episode.hpp"

//--------------------------------------------------
/*!
* \class ResponsableEpisode
* \brief Classe représentant un responsable chargé de traiter des objets Episode
*/
class ResponsableEpisode : public Responsable {
		
	public:
		//Constructeur & destructeur
		ResponsableEpisode(std::shared_ptr<BDConnector> db);
		~ResponsableEpisode();
		//Méthode publique
		void traiter(std::shared_ptr<Video> video, bool vu, bool aVoir);

};
//--------------------------------------------------
#endif




