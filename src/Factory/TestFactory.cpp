#include "FactorySQL.hpp"
#include <iostream>

using namespace std;

int main() {
	
	shared_ptr<BDConnector> testDB(new BDConnector("database/test.db"));
	shared_ptr<FactorySQL> facto(new FactorySQL(testDB));
	/*shared_ptr<Film> testFilm = facto->genererFilm("id","titre","lien",2014,"synopsis","affiche","pays",0,0);
	//Test pour la génération d'un film depuis la base de donnée
	vector<string > acteurs = testFilm->getActeurs();
	cout << testFilm->getId() << endl;
	cout << testFilm->getTitre() << endl;
	cout << testFilm->getAnnee() << endl;
	cout << testFilm->getSynopsis() << endl;
	cout << "affichage des acteurs" << endl;
	for(const auto &acteur: acteurs) {
		cout << acteur << endl;

	}*/
	
	//Test pour la génération d'un épisode depuis la base de donnée
	/*shared_ptr<Episode> testEp = facto->genererEpisode("id_ep","titre_ep","lien_ep",2014,"affiche_ep",1,5,"id_serie","synopsis","France",0,0);
	vector<string > acteurs = testEp->getActeurs();
	cout << testEp->getNumero() << endl;
	cout << testEp->getSaison() << endl;
	cout << testEp->getSerie() << endl;
	cout << "affichage des acteurs" << endl;
	for(const auto &acteur: acteurs) {
		cout << acteur << endl;

	}*/
	
	//Test pour la génération d'une série depuis la base de donnée
	shared_ptr<Serie> testSerie = facto->genererSerie("id_serie","Polkamon","lien_serie",2014,"affiche","synopsis_serie","France",0,0);
	vector<string > acteurs = testSerie->getActeurs();
	vector<shared_ptr<Episode> > episodes = testSerie->getEpisodes();
	cout << testSerie->getId() << endl;
	cout << testSerie->getTitre() << endl;
	cout << testSerie->getSynopsis() << endl;
	cout << "affichage des acteurs" << endl;
	for(const auto &acteur: acteurs) {
		cout << acteur << endl;

	}
	cout << "Affichage des épisodes" << endl;
	for(const auto &ep: episodes) {
		cout << "------------------" << endl;
		cout << ep->getTitre() << endl;
	}
	
	return 0;
}
