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
* \return Un shared_ptr<Film> qui pointe sur le film nouvellement crée
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
		shared_ptr<Personne> newReal (new Personne(realisateur[0], realisateur[1]));
		nouveauFilm->addReal(newReal);
	}
	return nouveauFilm;
}

//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouvel Episode
* \return Un shared_ptr<Episode> qui pointe sur l'épisode nouvellement crée
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
		shared_ptr<Personne> newReal (new Personne(realisateur[0], realisateur[1]));
		nouvelEpisode->addReal(newReal);
	}
	return nouvelEpisode;
}
//--------------------------------------------------
/*!
* \brief Méthode retournant la liste de tous les films contenus dans la base de données
* \return Un vector de shared_ptr<Video> qui contient  tous les films contenus dans la base de données
*/
vector<shared_ptr<Video> > FactorySQL::recupererAllFilms() {
	vector<shared_ptr<Video> > result;
	//on sélectionne tous les films contenus dans la base via une requête sql
	string sql = "SELECT * FROM Films";
	vector<vector< string> > films = bd->query(sql);
	//on parcours la liste des films et on les ajoute à la liste de réponse
	for(const auto &film: films) {
		result.push_back(this->genererFilm(film[0], film[1], film[2], atoi(film[3].c_str()), film[4], film[5]));
	}
	//on retourne le résultat
	return result;
}

//--------------------------------------------------
/*!
* \brief Méthode retournant la liste de tous les épisodes contenus dans la base de données
* \return Un vector de shared_ptr<Video> qui contient  tous les épisodes contenus dans la base de données
*/
vector<shared_ptr<Video> > FactorySQL::recupererAllEpisodes() {
	vector<shared_ptr<Video> > result;
	//on sélectionne tous les épisodes contenus la base via une requête sql
	string sql = "SELECT * FROM Episodes";
	vector<vector< string> > episodes = bd->query(sql);
	//on parcours la liste des épisodes et on les ajoute à la liste de réponse
	for(const auto &episode: episodes) {
		result.push_back(this->genererEpisode(episode[0], episode[1], episode[2], atoi(episode[3].c_str()), atoi(episode[4].c_str()), atoi(episode[5].c_str()), episode[6], episode[7]));
	}
	//on retourne le résultat
	return result;
}
