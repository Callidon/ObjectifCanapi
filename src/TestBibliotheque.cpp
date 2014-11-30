#include "Bibliotheque.hpp"
#include <iostream>

using namespace std;

int main() {
	
	shared_ptr<Bibliotheque> biblio (new Bibliotheque("test"));
	
	//affichage des vidéos de la bibliothèque
	vector<shared_ptr<Video> > videos = biblio->getVideos();
	for(const auto &video: videos) {
		cout << video->getTitre() << endl;
	}	

	//biblio->addVideo("Sherlock","Serie");
	
	cout << "on set le statut 'à voir'" << endl;
	biblio->selectVideo("Sherlock");
	//biblio->setStatutCurrentVideo(true,false);
	cout << biblio->getCurrentVideo()->getStatut() << endl;
	shared_ptr<Serie> serie(dynamic_pointer_cast<Serie>(biblio->getCurrentVideo()));
	vector<shared_ptr<Episode> > eps = serie->getEpisodes();
	
	for(const auto &ep: eps) {
		cout << ep->getTitre();
	}
	
	return 0;
}
