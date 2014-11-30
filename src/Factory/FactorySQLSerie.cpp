/*!
* \file FactorySQLSerie.cpp
* \brief Fichier contenant l'implémentation de la classe FactorySQLSerie
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#include "FactorySQLSerie.hpp"
#include <iostream>
using namespace std;

//--------------------------------------------------
/*!
* \brief Constructeur de base
* \param base shared_ptr vers un BDConnector accédant à la base de données
*/
FactorySQLSerie::FactorySQLSerie(shared_ptr<BDConnector> base): bd(base) {};


//--------------------------------------------------
/*!
* \brief Destructeur
*/
FactorySQLSerie::~FactorySQLSerie() {};


//--------------------------------------------------
/*!
* \brief Méthode créant et retournant un shared_ptr vers une nouvelle série
* \param id Identifiant de la série à créer
* \param titre Titre de la série
* \param lien Lien vers la bande-annonce
* \param annee Année de la série
* \param affiche Lien vers l'affiche de la série
* \param synopsis Synopsis de la série
* \param pays Pays associé à la série
* \param vu Si la série a été vue
* \param aVoir Si la série est à voir
* \return Un shared_ptr<Serie> qui pointe sur la série nouvellement crée
*/
shared_ptr<Serie> FactorySQLSerie::genererSerie(string id, string titre, string lien, int annee, string affiche, string synopsis, string pays, bool vu, bool aVoir) {
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
		nouvelleSerie->addEpisode(this->genererEpisode(episode[1], episode[2], episode[3], atoi(episode[4].c_str()), episode[5], atoi(episode[6].c_str()), atoi(episode[7].c_str()), episode[8], episode[9], episode[10], atoi(episode[11].c_str()), atoi(episode[12].c_str())));
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
* \param id Identifiant de l'épisode à créer
* \param titre Titre de l'épisode
* \param lien Lien vers la bande-annonce
* \param annee Année de l'épisode
* \param affiche Lien vers l'affiche de l'épisode
* \param numero Numéro de l'épisode dans la saison
* \param saison Numéro de la saison
* \param id_serie Identifiant de la série associée à l'épisode
* \param synopsis Synopsis de l'épisode
* \param pays Pays associé à l'épisode
* \param vu Si l'épisode a été vu
* \param aVoir Si l'épisode est à voir
* \return Un shared_ptr<Episode> qui pointe sur l'épisode nouvellement crée
*/
shared_ptr<Episode> FactorySQLSerie::genererEpisode(string id, string titre, string lien, int annee, string affiche, int numero, int saison, string id_serie, string synopsis, string pays, bool vu, bool aVoir) {
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
* \brief Méthode retournant la liste de toutes les séries contenus dans la base de données
* \return Un vector de shared_ptr<Video> qui contient  tous les épisodes contenus dans la base de données
*/
vector<shared_ptr<Video> > FactorySQLSerie::recupererAll() {
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
