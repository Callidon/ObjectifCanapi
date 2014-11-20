/*!
* \file Responsable.cpp
* \brief Fichier contenant l'implémentation de la classe Responsable
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "Responsable.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
* \param suiv Pointeur vers le responsable suivant
*/
Responsable::Responsable(shared_ptr<BDConnector> db, shared_ptr<Responsable> suiv) {
	this->database = db;
	this->suivant = suiv;
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Responsable::~Responsable() {}

//--------------------------------------------------
/*!
* \brief Méthode passant l'objet Video au responsable suivant
* \param video shared_ptr de l'objet Video à transmettre
*/
void Responsable::passerAuSuivant(shared_ptr<Video> video, bool vu, bool aVoir) {
	this->suivant->traiter(video, vu, aVoir);
}


//--------------------------------------------------
/*!
* \brief Méthode ajoutant un acteur à la base
* \param acteur L'acteur (nom + prénom) à ajouter dans la base
* \param id_video L'id de la vidéo auquel l'acteur est associé
*/
void Responsable::addActeur(string acteur, string id_video) {
	int id_acteur;
	string sql_insert;
	string sql_recherche = "SELECT * FROM Personnes WHERE nom = '" + acteur + "';";
			
			//si c'est acteur n'est pas déjà présent en base
			if(this->database->isReturnEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_acteur = this->database->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert = "INSERT INTO Personnes "
							"VALUES (" + to_string(id_acteur)
							+ ", '" + acteur + "');";
				this->database->query(sql_insert); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->database->query(sql_recherche);
				id_acteur = atoi(table[0][0].c_str());
			}
			
			//on associe l'acteur au film grâce à la table Acteurs
			sql_insert = "INSERT INTO Acteurs "
						"VALUES (" + to_string(id_acteur) 
						+ ", '" + id_video + "');";
			this->database->query(sql_insert);
}

//--------------------------------------------------
/*!
* \brief Méthode ajoutant un réalisateur à la base
* \param real Le réalisateur (nom + prénom) à ajouter dans la base
* \param id_video L'id de la vidéo auquel le réalisateur est associé
*/
void Responsable::addRealisateur(string real, string id_video) {
	int id_real;
	string sql_insert;
	string sql_recherche = "SELECT * FROM Personnes WHERE nom = '" + real + "';";
			
			//si ce réalisateur n'est pas déjà présent en base
			if(this->database->isReturnEmpty(sql_recherche)) {
				//alors on l'insère dans la table Personnes
				id_real = this->database->nextIdToInsert("id_personne","Personnes"); //on récupère son id
				sql_insert = "INSERT INTO Personnes "
							"VALUES (" + to_string(id_real)
							+ ", '" + real + "');";
				this->database->query(sql_insert); 
				
			} else { //sinon, on récupère son id
				vector<vector<string> > table = this->database->query(sql_recherche);
				id_real = atoi(table[0][0].c_str());
			}
			
			//on associe le réalisateur au film grâce à la table Realisateurs
			sql_insert = "INSERT INTO Realisateurs "
						"VALUES (" + to_string(id_real) 
						+ ", '" + id_video + "');";
			this->database->query(sql_insert);
	
}
