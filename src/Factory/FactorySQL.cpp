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
shared_ptr<Film> FactorySQL::genererFilm(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays, bool vu, bool aVoir) {
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
* \brief Méthode créant et retournant un shared_ptr vers un nouvel Episode
* \return Un shared_ptr<Episode> qui pointe sur l'épisode nouvellement crée
*/
shared_ptr<Serie> FactorySQL::genererSerie(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays, bool vu, bool aVoir) {
	//création de la nouvelle série
	shared_ptr<Serie> nouvelleSerie (new Serie(id, titre, lien, annee, affiche, synopsis, pays));
	
	if(vu) {
		nouvelleSerie->marquerVu();
	}
	if(aVoir) {
		nouvelleSerie->marquerVoir();
	}
	
	//on ajoute tous les épisodes à la série
	//on récupère tous les épisodes liées à la série depuis la base
	string sql = "SELECT Series.id_serie, Episodes.id_episode, Episodes.titre, Episodes.lien, Episodes.annee, Episodes.affiche, "
		  "Episodes.numero, Episodes.saison, Episodes.id_serie, Episodes.synopsis, Episodes.pays, "
		  "Episodes.vu, Episodes.aVoir"
		  " FROM Series,Episodes"
		  " WHERE Series.id_serie = '" + id + "' AND Series.id_serie = Episodes.id_serie;";
	vector<vector<string> > episodes = bd->query(sql);
	
	//on parcours la liste des épisodes
	for(const auto &episode: episodes) {
		nouvelleSerie->addEpisode(this->genererEpisode(episode[0], episode[1], episode[2], atoi(episode[3].c_str()), episode[4], atoi(episode[5].c_str()), atoi(episode[6].c_str()), episode[7], episode[8], episode[9], atoi(episode[10].c_str()), atoi(episode[11].c_str())));
	}
	
	//on récupère tous les acteurs liés au film depuis la base
	sql = "SELECT nom, id_serie, id_personne, id_video, id_acteur"
				 " FROM Series,Personnes,Acteurs"
				 " WHERE id_serie = '" + id + "' AND Series.id_serie = Acteurs.id_video AND Personnes.id_personne = Acteurs.id_acteur;";
	vector<vector< string> > acteurs = bd->query(sql);
	
	//on parcours la liste des acteurs
	for(const auto &acteur: acteurs) {
		nouvelleSerie->addActeur(acteur[0]);
	}
	
	//on fait la même chose avec les réalisateurs
	//on récupère tous les acteurs liés au film depuis la base
	sql = "SELECT nom, id_serie, id_personne, id_video, id_real"
		  " FROM Series,Personnes,Realisateurs"
		  " WHERE id_serie = '" + id + "' AND Series.id_serie = Realisateurs.id_video AND Personnes.id_personne = Realisateurs.id_real;";
	vector<vector< string> > realisateurs = bd->query(sql);
	
	//on parcours la liste des acteurs
	for(const auto &realisateur: realisateurs) {
		nouvelleSerie->addReal(realisateur[0]);
	}
	
	return nouvelleSerie;
}

//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers un nouvel Episode
* \return Un shared_ptr<Episode> qui pointe sur l'épisode nouvellement crée
*/
shared_ptr<Episode> FactorySQL::genererEpisode(string id, string titre, string lien, int annee, string affiche, int numero, int saison, string id_serie, string synopsis, string pays, bool vu, bool aVoir) {
	//création du nouvel épisode
	shared_ptr<Episode> nouvelEpisode (new Episode(id, titre, lien, annee, affiche, numero, saison, id_serie, synopsis, pays));
	
	if(vu) {
		nouvelEpisode->marquerVu();
	}
	if(aVoir) {
		nouvelEpisode->marquerVoir();
	}
	
	//on récupère tous les acteurs liés au film depuis la base
	string sql = "SELECT nom, id_episode, id_personne, id_video, id_acteur"
				 " FROM Episodes,Personnes,Acteurs"
				 " WHERE id_episode = '" + id + "' AND Episodes.id_episode = Acteurs.id_video AND Personnes.id_personne = Acteurs.id_acteur;";
	vector<vector< string> > acteurs = bd->query(sql);
	
	//on parcours la liste des acteurs
	for(const auto &acteur: acteurs) {
		nouvelEpisode->addActeur(acteur[0]);
	}
	
	//on fait la même chose avec les réalisateurs
	//on récupère tous les acteurs liés au film depuis la base
	sql = "SELECT nom, id_episode, id_personne, id_video, id_real"
		  " FROM Episodes,Personnes,Realisateurs"
		  " WHERE id_episode = '" + id + "' AND Episodes.id_episode = Realisateurs.id_video AND Personnes.id_personne = Realisateurs.id_real;";
	vector<vector< string> > realisateurs = bd->query(sql);
	
	//on parcours la liste des acteurs
	for(const auto &realisateur: realisateurs) {
		nouvelEpisode->addReal(realisateur[0]);
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
	string sql = "SELECT * FROM Films;";
	vector<vector< string> > films = bd->query(sql);
	
	//on parcours la liste des films et on les ajoute à la liste de réponse
	for(const auto &film: films) {
		result.push_back(this->genererFilm(film[0], film[1], film[2], atoi(film[3].c_str()), film[4], film[5], film[6], atoi(film[7].c_str()), atoi(film[8].c_str())));
	}
	//on retourne le résultat
	return result;
}

//--------------------------------------------------
/*!
* \brief Méthode retournant la liste de tous les épisodes contenus dans la base de données
* \return Un vector de shared_ptr<Video> qui contient  tous les épisodes contenus dans la base de données
*/
vector<shared_ptr<Video> > FactorySQL::recupererAllSeries() {
	vector<shared_ptr<Video> > result;
	//on sélectionne tous les épisodes contenus la base via une requête sql
	string sql = "SELECT * FROM Series;";
	vector<vector< string> > series = bd->query(sql);
	
	//on parcours la liste des épisodes et on les ajoute à la liste de réponse
	for(const auto &serie: series) {
		result.push_back(this->genererSerie(serie[0], serie[1], serie[2], atoi(serie[3].c_str()), serie[4], serie[5], serie[6], atoi(serie[7].c_str()), atoi(serie[8].c_str())));
	}
	//on retourne le résultat
	return result;
}