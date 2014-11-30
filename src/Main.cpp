/*!
* \file Main.cpp
* \brief Fichier contenant la classe principale, permettant l'interaction avec l'utilisateur
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/

#include "Bibliotheque.hpp"
#include <iostream>
#include <string>
#include <limits>

using namespace std;
//--------------------------------------------------
void menuVideo(shared_ptr<Bibliotheque> biblio);
void menuPrincipal(shared_ptr<Bibliotheque> biblio);
void menuConnexion();

void menuConnexion(){
	string user;
	
	cout << "Bonjour, veuillez rentrer votre pseudo afin de vous connecter. \nSi votre pseudo n'existe pas, votre compte sera créé automatiquement. \n Pseudo : ";
	cin >> user;
	
	shared_ptr<Bibliotheque> biblio (new Bibliotheque(user));
	
	cout << "Bienvenue " << user << endl;
	menuPrincipal(biblio);
}

void menuPrincipal(shared_ptr<Bibliotheque> biblio){
	char choix;
	char recherche;
	string titre;
	vector<shared_ptr<Video> > videos;
	
	int i = 0;
	char select;
	char vid;
	int choixVideo;
	bool test;
	cout << "\n Que voulez-vous faire?" << endl;
	cout << "1 : Mes videos marquées" << endl;
	cout << "2 : Recherche" << endl;
	cout << "3 : Déconnexion" << endl;
	cout << "4 : Quitter" << endl;
	do{
		cout << "Votre choix : ";
		cin >> choix;
	}while(!(choix=='1' || choix=='2' || choix=='3' || choix=='4'));
	
	switch(choix){
		case '1': //Mes videos
			videos = biblio->getVideos();
			cout << "\n";
			for(const auto &video: videos) {
				cout << ++i << " " << video->getTitre() << " - " << video->getAnnee() << endl;
			}
			do{
				cout << "Sélectionner une video? (y/n) ";
				cin >> select;
			}while(select != 'y' && select !='Y' && select!='n' && select!='N');
			
			if(select == 'y' || select == 'Y'){
					do{
						cout << "La quelle selectionner?";
						cin >> vid;
						choixVideo = (int)vid;
						cout << choixVideo-48 << endl;
					}while(!(choixVideo - 48 >= 1 && choixVideo-48 <= biblio->getVideos().size() + 1)); 
					
					biblio->selectVideo(biblio->getVideos().at(choixVideo-48-1)->getTitre());
					menuVideo(biblio);
			}
			else if(select == 'n' || select == 'N'){
					menuPrincipal(biblio);
			}
			break;
		
		case '2': //Rercherche
			do{
				cout << "\nVoulez-vous rechercher un film ou une série? (1 ou 2)  : ";
				cin >> recherche;
			}while(recherche!= '1' && recherche!='2');
			
			switch(recherche){
				case '1' :
					cout << "Titre du film à rechercher : ";
					//nettoie le buffer d'entrée
					std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
					getline (cin, titre); //pour lire plusieurs mots séparer par un espace (ce que le cin ne fait pas)
					cout << "titre : " << titre << endl;
					biblio->addVideo(titre, "Film");
					break;
					
				case '2' :
					cout << "Titre de la série à rechercher : ";
					cin >> titre;
					biblio->addVideo(titre, "Serie");
					break;
			}//switch recherche
			menuVideo(biblio);
			break;
		
		case '3': //Déconnexion
			cout << "Déconnexion" << endl;
			system("clear");
			menuConnexion();
			break;
		
		
		case '4': //Quitter
			cout << "A bientôt." << endl;
			exit(0);
			break;
		
	}//switch menu principal
}

void menuVideo(shared_ptr<Bibliotheque> biblio){
	shared_ptr<Video> video = biblio->getCurrentVideo();
	string titre = video->getTitre();
	
	cout << "\nQue voulez-vous faire de " << titre << "?" << endl;
	cout << "1 : Marquer " << titre << "\"a voir" << endl;
	cout << "2 : Marquer " << titre << "\"vu" << endl;
	cout << "3 : Voir statut" << endl;
	cout << "4 : Afficher les informations" << endl;
	cout << "5 : Voir l'affiche" << endl;
	cout << "6 : Rechercher la bande-annonce" << endl;
	cout << "7 : Retour" << endl;
	
	char ok;
	char choix;
	do{
		cin >> choix;
	}while(!(choix=='1' || choix=='2' || choix=='3' || choix=='4' || choix=='5' || choix=='6' || choix=='7'));
	
	vector<string> acteurs = video->getActeurs();
	vector<string> real = video->getReal();
	
	switch(choix){
		case '1': //marquer a voir
			biblio->setStatutCurrentVideo(video->getVu(), true);
			cout << "Retour au menu principal" << endl;
			menuPrincipal(biblio);
			break;
		
		case '2': //marcher vu
			biblio->setStatutCurrentVideo(true, video->getVoir());
			cout << "Retour au menu principal" << endl;
			menuPrincipal(biblio);
			break;
		
		case '3': //voir statut
			cout << biblio->getCurrentVideo()->getTitre() << " est " << biblio->getCurrentVideo()->getStatut() << endl;
			menuPrincipal(biblio);
			break;
		
		case '4': //informations
			cout << video->getTitre() << " - " << video->getAnnee() << " - " << video->getPays() << endl;
			cout << "De : ";
			for(string act : acteurs){
				cout << act << ", ";
			}
			cout << "Avec : ";
			for(string r : real){
				cout << r;
			}
			cout << video->getSynopsis() << endl;
			cout << "Retour au menu principal. Pressez une touche quand vous êtes prêt." << endl;
			cin >> ok;
				menuPrincipal(biblio);
			break;
		
		case '5': //affiche
			video->voirAffiche();
			break;
		
		case '6':  //BA
			video->lire();
			break;
	
		case '7': //retour
			menuPrincipal(biblio);
			break;
	}
}

int main(){
	menuConnexion();
	return(0);
}
