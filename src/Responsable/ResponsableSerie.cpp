/*!
* \file ResponsableSerie.cpp
* \brief Fichier contenant les entêtes de la classe ResponsableSerie
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/

#include "ResponsableSerie.hpp"
#include "ResponsableEpisode.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
ResponsableSerie::ResponsableSerie(std::shared_ptr<BDConnector> db)
	: Responsable(db, shared_ptr<ResponsableEpisode>(new ResponsableEpisode(db))) 
	{}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
ResponsableSerie::~ResponsableSerie() {}

//--------------------------------------------------
/*!
* \brief Méthode effectuant le traitement de l'objet si c'est une série
* \brief Si la série n'est pas présente dans la base, on l'insère. Sinon, on la met à jour
* \param video shared_ptr vers l'objet à traiter
*/
void ResponsableSerie::traiter(std::shared_ptr<Video> video, bool vu, bool aVoir) {
	string sql, sql_test_existence;
	
	//on essaye de convertir la vidéo en film
	shared_ptr<Serie> serie(dynamic_pointer_cast<Serie>(video));
	
	//si c'est bien un objet Film
	if(serie) {
		
		//on utilise le comportement pour effectuer les requêtes adéquates sur l'objet
		comportement->traiterSerie(serie, vu, aVoir);
			
		//on traite aussi tous les épisodes de la série
		//on récupère la liste des épisodes
		vector<shared_ptr<Episode> > episodes = serie->getEpisodes();
			
		//on parcours la liste des épisodes & on les insère en base via le responsable suivant
		for(const auto &episode: episodes) {
			this->suivant->traiter(episode,false,false);
		}

	} else { //sinon, on passe au responsable suivant
		this->passerAuSuivant(video,vu, aVoir);
	}
	
}

