#include "Bibliotheque.hpp"
#include <iostream>

using namespace std;

int main() {
	
	shared_ptr<Bibliotheque> biblio (new Bibliotheque("database/test"));
	biblio->addVideo("","");
	
	//affichage des vidéos de la bibliothèque
	vector<shared_ptr<Video> > videos = biblio->getVideos();
	for(const auto &video: videos) {
		cout << video->getTitre() << endl;
	}
	
	cout << "on set le statut 'àvoir'" << endl;
	biblio->selectVideo("Game of Thrones");
	biblio->setStatutCurrentVideo(false,true);
	
	return 0;
}
