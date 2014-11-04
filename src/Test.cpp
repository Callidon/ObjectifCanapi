#include "Film.hpp"
#include "Episode.hpp"
#include "Bibliotheque.hpp"

#include "FactoryOMDB.hpp"

#include <iostream>
using namespace std;

int main()
{
 
//TEST CLASSE FILM -> OK
/*
	Film* film = new Film("01", "titre", "lien", 2014, "affiche", "synopsis");

	cout << film->getId() << endl;
	cout << film->getTitre() << endl;
	cout << film->getAnnee() << endl;
	cout << film->getAffiche() << endl;
	cout << film->getSynopsis() << endl;
	//film->lire();
	film->marquerVu();
	cout << film->getStatut() << endl;
	
	delete(film);
*/

//TEST CLASSE EPISODE -> OK
/*
	Episode* episode = new Episode("01", "Titre", "www.google.com", 2014, 02, 03, "Serie", "Synopsis");

	cout << episode->getNumero() << endl;
	cout << episode->getSaison() << endl;
	cout << episode->getSerie() << endl;
	episode->marquerVoir();
	episode->marquerVu();
	cout << episode->getStatut() << endl;
	//episode->lire();

	delete(episode);
*/

//TEST CLASS PERSONNE
/*
	Personne* personne = new Personne("nom","prenom");
	cout << personne->getNom() << endl;
	cout << personne->getPrenom() << endl;
	
	delete(personne);
*/

	string user;
	cout << "User : ";
	cin >> user;
	
	Bibliotheque* biblio = new Bibliotheque(user);
	cout << biblio->getUser() << endl;
	
	shared_ptr<Film> film1(new Film("01", "Film1", "lien", 2014, "affiche", "synopsis"));
	film1->marquerVu();
	shared_ptr<Film> film2(new Film("02", "Film2", "lien", 2013, "affiche", "synopsis"));
	film2->marquerVoir();
	shared_ptr<Film> film3(new Film("03", "Film3", "lien", 2012, "affiche", "synopsis"));
	shared_ptr<Film> film4(new Film("04", "Film4", "lien", 2011, "affiche", "synopsis"));
	film4->marquerVu();
	
	shared_ptr<Episode> episode1(new Episode("11", "Episode1", "www.google.com", 2014, 01, 01, "Serie", "Synopsis"));
	episode1->marquerVoir();
	shared_ptr<Episode> episode2(new Episode("12", "Episode2", "www.google.com", 2014, 02, 01, "Serie", "Synopsis"));
	shared_ptr<Episode> episode3(new Episode("13", "Episode3", "www.google.com", 2014, 03, 01, "Serie", "Synopsis"));
	episode3->marquerVu();
	
	biblio->addVideo(film1);
	biblio->addVideo(film2);
	biblio->addVideo(film3);
	biblio->addVideo(film4);
	biblio->addVideo(episode1);
	biblio->addVideo(episode2);
	biblio->addVideo(episode3);
	
	for(shared_ptr<Video> v : biblio->getVideos()){
		cout << v->getStatut() << endl;
	}

	return(0);
}
