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
	string sql, sql_test_existence;
	
	//on essaye de convertir la vidéo en film
	shared_ptr<Film> film(dynamic_pointer_cast<Film>(video));
	
	//si c'est bien un objet Film
	if(film) {
		sql_test_existence = "SELECT * FROM Films WHERE id_film = '" + film->getId() + "';";
		//si le film n'est pas déjà présent en base, on l'ajoute
		if( this->database->isReturnEmpty(sql_test_existence) ) {	
			
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
		this->passerAuSuivant(video,vu, aVoir);
	}
	
}
