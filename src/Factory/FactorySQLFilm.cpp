/*!
* \file FactorySQLFilm.cpp
* \brief Fichier contenant l'implémentation de la classe FactorySQLFilm
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#include "FactorySQLFilm.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
FactorySQLFilm::FactorySQLFilm(shared_ptr<BDConnector> base): bd(base) {};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FactorySQLFilm::~FactorySQLFilm() {};

//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouveau Film
* \return Un shared_ptr<Film> qui pointe sur le film nouvellement crée
*/
shared_ptr<Film> FactorySQLFilm::genererFilm(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays, bool vu, bool aVoir) {
	//création du nouveau film
	shared_ptr<Film> nouveauFilm (new Film(id, titre, lien, annee, affiche, synopsis, pays));
	
	if(vu) {
		nouveauFilm->marquerVu();
	}
	if(aVoir) {
		nouveauFilm->marquerVoir();
	}
	
	//on récupère tous les acteurs liés au film depuis la base
	string sql = "SELECT nom, id_film, id_personne, id_video, id_acteur" 
				 " FROM Films,Personnes,Acteurs"
				 " WHERE id_film = '" + id + "' AND Films.id_film = Acteurs.id_video AND Personnes.id_personne = Acteurs.id_acteur;";
	vector<vector< string> > acteurs = bd->query(sql);
	
	//on parcours la liste des acteurs
	for(const auto &acteur: acteurs) {
		nouveauFilm->addActeur(acteur[0]);
	}
	
	//on fait la même chose avec les réalisateurs
	//on récupère tous les acteurs liés au film depuis la base
	sql = "SELECT nom, id_film, id_personne, id_video, id_real"
		  " FROM Films,Personnes,Realisateurs"
		  " WHERE id_film = '" + id + "' AND Films.id_film = Realisateurs.id_video AND Personnes.id_personne = Realisateurs.id_real;";
	vector<vector< string> > realisateurs = bd->query(sql);
	
	//on parcours la liste des acteurs
	for(const auto &realisateur: realisateurs) {
		nouveauFilm->addReal(realisateur[0]);
	}
	return nouveauFilm;
}

//--------------------------------------------------
/*!
* \brief Méthode retournant la liste de tous les films contenus dans la base de données
* \return Un vector de shared_ptr<Video> qui contient  tous les films contenus dans la base de données
*/
vector<shared_ptr<Video> > FactorySQLFilm::recupererAll() {
	vector<shared_ptr<Video> > result;
	//on sélectionne tous les films contenus dans la base via une requête sql
	string sql = "SELECT * FROM Films;";
	vector<vector< string> > films = bd->query(sql);
	
	//on parcours la liste des films et on les ajoute à la liste de réponse
	for(const auto &film: films) {
		result.push_back(this->genererFilm(film[0], film[1], film[2], atoi(film[3].c_str()), film[4], film[5], film[6], atoi(film[7].c_str()), atoi(film[8].c_str())));
	}
	//on retourne le résultat
	return result;
}
