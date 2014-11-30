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
	
	/*cout << "on ajoute Hot Fuzz" << endl;
	biblio->addVideo("Hot Fuzz","Film");*/
	
	//cout << "on set le statut 'à voir'" << endl;
	biblio->selectVideo("Game of Thrones");
	vector<shared_ptr<Episode>> ep = biblio->getCurrentVideo()->getEpisodes();
	for(shared_ptr<Episode> e : ep){
		cout << ep->getTitre() << endl;
	}
	//biblio->setStatutCurrentVideo(false,true);
	
	return 0;
}
