/*!
* \file FactorySQL.cpp
* \brief Fichier contenant l'implémentation de la classe FactorySQL
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#include "FactorySQL.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
*/
FactorySQL::FactorySQL(shared_ptr<BDConnector> base): bd(base) {};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FactorySQL::~FactorySQL() {};

//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouveau Film
*/
shared_ptr<Film> FactorySQL::genererFilm(string id, string titre, string lien, int annee, string affiche, string synopsis) {
	shared_ptr<Film> nouveauFilm (new Film(id, titre, lien, annee, affiche, synopsis));
	//on récupère tous les acteurs liés au film depuis la base
	string sql = "SELECT nom, prenom, id_film, id_personne, id_video, id_acteur FROM Films,Personnes,Acteurs WHERE id_film = '" + id + "' AND Films.id_film = Acteurs.id_video AND Personnes.id_personne = Acteurs.id_acteur;";
	vector<vector< string> > acteurs = bd->query(sql);
	//on parcours la liste des acteurs
	for(const auto &acteur: acteurs) {
		shared_ptr<Personne> newAct (new Personne(acteur[0], acteur[1]));
		nouveauFilm->addActeur(newAct);
	}
	//on fait la même chose avec les réalisateurs
	//on récupère tous les acteurs liés au film depuis la base
	sql = "SELECT nom, prenom, id_film, id_personne, id_video, id_real FROM Films,Personnes,Realisateurs WHERE id_episode = '" + id + "' AND Films.id_film = Realisateurs.id_video AND Personnes.id_personne = Realisateurs.id_real;";
	vector<vector< string> > realisateurs = bd->query(sql);
	//on parcours la liste des acteurs
	for(const auto &realisateur: realisateurs) {
		shared_ptr<Personne> newAct (new Personne(realisateur[0], realisateur[1]));
		nouveauFilm->addReal(newAct);
	}
	return nouveauFilm;
}

//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouvel Episode
*/
shared_ptr<Episode> FactorySQL::genererEpisode(string id, string titre, string lien, int annee, int numero, int saison, string serie, string synopsis) {
	shared_ptr<Episode> nouvelEpisode (new Episode(id, titre, lien, annee, numero, saison, serie, synopsis));
	//on récupère tous les acteurs liés au film depuis la base
	string sql = "SELECT nom, prenom, id_episode, id_personne, id_video, id_acteur FROM Episodes,Personnes,Acteurs WHERE id_episode = '" + id + "' AND Episodes.id_episode = Acteurs.id_video AND Personnes.id_personne = Acteurs.id_acteur;";
	vector<vector< string> > acteurs = bd->query(sql);
	//on parcours la liste des acteurs
	for(const auto &acteur: acteurs) {
		shared_ptr<Personne> newAct (new Personne(acteur[0], acteur[1]));
		nouvelEpisode->addActeur(newAct);
	}
	//on fait la même chose avec les réalisateurs
	//on récupère tous les acteurs liés au film depuis la base
	sql = "SELECT nom, prenom, id_episode, id_personne, id_video, id_real FROM Episodes,Personnes,Realisateurs WHERE id_episode = '" + id + "' AND Episodes.id_episode = Realisateurs.id_video AND Personnes.id_personne = Realisateurs.id_real;";
	vector<vector< string> > realisateurs = bd->query(sql);
	//on parcours la liste des acteurs
	for(const auto &realisateur: realisateurs) {
		shared_ptr<Personne> newAct (new Personne(realisateur[0], realisateur[1]));
		nouvelEpisode->addReal(newAct);
	}
	return nouvelEpisode;
}
