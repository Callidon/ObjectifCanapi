/*!
* \file ResponsableSerie.cpp
* \brief Fichier contenant les entêtes de la classe ResponsableSerie
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
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
		sql_test_existence = "SELECT * FROM Series WHERE id_serie = '" + serie->getId() + "';";
		//si le film n'est pas déjà présent en base, on l'ajoute
		if( this->database->isReturnEmpty(sql_test_existence) ) {	
			
			sql = "INSERT INTO Series "
					"VALUES ('" + serie->getId() + "', '" 
					+ serie->getTitre() + "', '" 
					+ serie->getLien() + "', " 
					+ to_string(serie->getAnnee()) + ", '" 
					+ serie->getSynopsis() + "', '" 
					+ serie->getAffiche() + "', '" 
					+ serie->getPays() + "', " 
					+ to_string(vu) + ", " + to_string(aVoir) + ");";
					
			//on effectue la requête
			this->database->query(sql);
			
			//on insère tous les épisodes de la série en base
			//on récupère la liste des épisodes
			vector<shared_ptr<Episode> > episodes = serie->getEpisodes();
			
			//on parcours la liste des épisodes & on les insère en base via le responsable suivant
			for(const auto &episode: episodes) {
				this->suivant->traiter(episode,false,false);
			}
			
			//on insère les acteurs & les réalisateurs en base
			//on récupère les listes des acteurs & réalisateurs
			vector<string> acteurs = serie->getActeurs();
			vector<string> realisateurs = serie->getReal();
			
			//parcours de la liste des acteurs
			for(const auto &acteur: acteurs) {
				this->addActeur(acteur, serie->getId());
			}
			
			//parcours de la liste des réalisateurs
			for(const auto &realisateur: realisateurs) {
				this->addRealisateur(realisateur, serie->getId());
			}
			
		} else { //sinon, on le met à jour
			sql = "UPDATE Series "
					"SET vu = " + to_string(vu) 
					+ ", aVoir = " + to_string(aVoir) 
					+ " WHERE id_serie = '" + serie->getId() + "';";
			//on effectue la requête
			this->database->query(sql);
		}	
	} else { //sinon, on passe au responsable suivant
		this->passerAuSuivant(video,vu, aVoir);
	}
	
}

