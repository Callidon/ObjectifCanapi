/*!
* \file ResponsableEpisode.cpp
* \brief Fichier contenant les entêtes de la classe ResponsableEpisode
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
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
	string sql, sql_test_existence;
	
	//on essaye de convertir la vidéo en film
	shared_ptr<Episode> episode(dynamic_pointer_cast<Episode>(video));
	
	//si c'est bien un objet Film
	if(episode) {
		sql_test_existence = "SELECT * FROM Episodes WHERE id_episode = '" + episode->getId() + "';";
		//si le film n'est pas déjà présent en base, on l'ajoute
		if( this->database->isReturnEmpty(sql_test_existence) ) {	
			
			sql = "INSERT INTO Episodes"
					"VALUES ('" + episode->getId() 
					+ "', '" + episode->getTitre()
					+ "', '" + episode->getLien() 
					+ "', " + to_string(episode->getAnnee()) 
					+ "', '" + episode->getAffiche()
					+ "', '" + episode->getSynopsis() 
					+ "', " + to_string(episode->getNumero())
					+ ", " + to_string(episode->getSaison()) 
					+ ", '" + episode->getSerie()
					+ ", '" + episode->getPays()
					+ "', " + to_string(vu) + ", " + to_string(aVoir) + ");";
					
			//on effectue la requête
			this->database->query(sql);
			
			//on insère les acteurs & les réalisateurs en base
			//on récupère les listes des acteurs & réalisateurs
			vector<string> acteurs = episode->getActeurs();
			vector<string> realisateurs = episode->getReal();
			
			//parcours de la liste des acteurs
			for(const auto &acteur: acteurs) {
				this->addActeur(acteur, episode->getId());
			}
			
			//parcours de la liste des réalisateurs
			for(const auto &realisateur: realisateurs) {
				this->addRealisateur(realisateur, episode->getId());
			}
			
		} else { //sinon, on le met à jour
			sql = "UPDATE Episodes "
					"SET vu = " + to_string(vu) 
					+ ", aVoir = " + to_string(aVoir) 
					+ " WHERE id_episode = '" + episode->getId() + "';";
			//on effectue la requête
			this->database->query(sql);
		}	
	} else {
		cout << "Erreur : aucun responsable ne peut traiter la requête" << endl;
	}
	
}


