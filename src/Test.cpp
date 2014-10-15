//#include "Film.hpp"
#include "Episode.hpp"

#include <iostream>
using namespace std;

int main()
{
/* 
*TEST CLASSE FILM
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

//TEST CLASSE EPISODE
	Episode* episode = new Episode("01", "Titre", "link", 2014, 02, 03, "Serie", "Synopsis");
	cout << episode->getNumero() << endl;
	cout << episode->getSaison() << endl;
	cout << episode->getSerie() << endl;
	episode->marquerVoir();
	cout << episode->getStatut() << endl;
	
	delete(episode);
	
	return(0);
}
