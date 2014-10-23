#include "FactoryOMDB.hpp"
#include <iostream>

using namespace std;

int main() {
	
	shared_ptr<BDConnector> testDB(new BDConnector("database/test.db"));
	shared_ptr<FactoryOMDB> facto(new FactoryOMDB(testDB));
	/*
	shared_ptr<Film> testFilm = facto->genererFilm("id","titre","lien",2014,"affiche","synopsis");
	//Test pour la génération d'un film depuis la base de donnée
	vector<shared_ptr<Personne> > acteurs = testFilm->getActeurs();
	cout << testFilm->getId() << endl;
	cout << testFilm->getTitre() << endl;
	cout << testFilm->getAnnee() << endl;
	cout << testFilm->getSynopsis() << endl;
	cout << "affichage des acteurs" << endl;
	for(const auto &acteur: acteurs) {
		cout << acteur->getNom() << endl;
	}
	*/
	
	shared_ptr<Video> testFilm = facto->makeFilm(facto->queryTitle("Catch me if you can"));
	cout << testFilm->getId() << endl;
	cout << testFilm->getTitre() << endl;
	cout << testFilm->getAnnee() << endl;
	cout << testFilm->getSynopsis() << endl;
	for(string act : testFilm->getActeurs()){
		cout << act << endl;
	}
	testFilm->lire();
	
	/*
	//Test pour la génération d'un épisode depuis la base de donnée
	shared_ptr<Episode> testEp = facto->genererEpisode("11", "Episode1", "www.google.com", 2014, 01, 01, "Serie", "Synopsis");
	vector<shared_ptr<Personne> > acteurs = testEp->getActeurs();
	cout << testEp->getNumero() << endl;
	cout << testEp->getSaison() << endl;
	cout << testEp->getSerie() << endl;
	cout << "affichage des acteurs" << endl;
	for(const auto &acteur: acteurs) {
		cout << acteur->getNom() << endl;

	}*/
	return 0;
}
