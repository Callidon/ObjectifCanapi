/*!
* \file ResponsableEpisode.cpp
* \brief Fichier contenant les entêtes de la classe ResponsableEpisode
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/

#include "ResponsableEpisode.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
ResponsableEpisode::ResponsableEpisode(std::shared_ptr<BDConnector> db)
	: Responsable(db, 0) 
	{}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
ResponsableEpisode::~ResponsableEpisode() {}

//--------------------------------------------------
/*!
* \brief Méthode effectuant le traitement de l'objet si c'est un épisode
* \brief Si l'épisode n'est pas présent dans la base, on l'insère. Sinon, on le met à jour
* \param video shared_ptr vers l'objet à traiter
*/
void ResponsableEpisode::traiter(std::shared_ptr<Video> video, bool vu, bool aVoir) {
	
	//on essaye de convertir la vidéo en film
	shared_ptr<Episode> episode(dynamic_pointer_cast<Episode>(video));
	
	//si c'est bien un objet Film
	if(episode) {
		
		//on utilise le comportement pour effectuer les requêtes adéquates sur l'objet
		comportement->traiterEpisode(episode, "", vu, aVoir);
		
	} else {
		//Il n'y a plus de successeur après ce responsable, on affiche une erreur
		cout << "Erreur : aucun responsable ne peut traiter la requête" << endl;
	}
	
}


