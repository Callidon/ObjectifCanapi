/*!
* \file ResponsableFilm.cpp
* \brief Fichier contenant les entêtes de la classe ResponsableFilm
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/

#include "ResponsableFilm.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
ResponsableFilm::ResponsableFilm()
	: Responsable(db, new ResponsableSerie()) 
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
void traiter(std::shared_ptr<Video> video) {
	//requêtes sql
	string sql;
	string sql_test_existence = "SELECT * FROM Films WHERE id_film = '" + film->getId() + "';";
	
	//on essaye de convertir la vidéo en film
	shared_ptr<Film> film(dynamic_pointer_cast<Film>(video));
	
	//si c'est bien un objet Film
	if(film) {
		//si le film n'est pas déjà présent en base, on l'ajoute
		if( this->database->isQueryEmpty(sql_test_existence) ) {	
			
			sql = "INSERT INTO Films "
					"VALUES ('" + film->getId() + "', '" 
					+ film->getTitre() + "', '" 
					+ film->getLien() + "', " 
					+ to_string(film->getAnnee()) + ", '" 
					+ film->getSynopsis() + "', '" 
					+ film->getAffiche() + "', '" 
					+ film->getPays() + "', " 
					+ to_string(vu) + ", " + to_string(aVoir) + ");";
					
			//on effectue la requête
			this->database->query(sql);
			
			//on insère les acteurs & les réalisateurs en base
			//on récupère les listes des acteurs & réalisateurs
			vector<string> acteurs = film->getActeurs();
			vector<string> realisateurs = film->getReal();
			
			//parcours de la liste des acteurs
			for(const auto &acteur: acteurs) {
				this->addActeur(acteur, film->getId());
			}
			
			//parcours de la liste des réalisateurs
			for(const auto &realisateur: realisateurs) {
				this->addRealisateur(realisateur, film->getId());
			}
			
		} else { //sinon, on le met à jour
			sql = "UPDATE Films " 
					"SET vu = " + to_string(vu) 
					+ ", aVoir = " + to_string(aVoir) 
					+ " WHERE id_film = '" + film->getId() + "';";
			//on effectue la requête
			this->database->query(sql);
		}	
	} else { //sinon, on passe au responsable suivant
		this->passerAuSuivant(video);
	}
	
}
