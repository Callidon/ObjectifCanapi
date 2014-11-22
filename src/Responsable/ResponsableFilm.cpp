/*!
* \file ResponsableFilm.cpp
* \brief Fichier contenant les entêtes de la classe ResponsableFilm
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/

#include "ResponsableFilm.hpp"
#include "ResponsableSerie.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
ResponsableFilm::ResponsableFilm(std::shared_ptr<BDConnector> db)
	:Responsable(db, shared_ptr<ResponsableSerie>(new ResponsableSerie(db))) 
	{}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
ResponsableFilm::~ResponsableFilm() {}

//--------------------------------------------------
/*!
* \brief Méthode effectuant le traitement de l'objet si c'est un film
* \brief Si le film n'est pas présent fans la base, on l'insère. Sinon, on le met à jour
* \param video shared_ptr vers l'objet à traiter
*/
void ResponsableFilm::traiter(std::shared_ptr<Video> video, bool vu, bool aVoir) {
	
	//on essaye de convertir la vidéo en film
	shared_ptr<Film> film(dynamic_pointer_cast<Film>(video));
	
	//si c'est bien un objet Film
	if(film) {
		
		//on utilise le comportement pour effectuer les requêtes adéquates sur l'objet
		comportement->traiterFilm(film, vu, aVoir);
		
	} else { //sinon, on passe au responsable suivant
		this->passerAuSuivant(video,vu, aVoir);
	}
	
}
