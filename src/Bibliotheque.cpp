/*!
* \file Bibliotheque.cpp
* \brief Fichier contenant l'implémentation de la classe Bibliotheque
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/

#include "Bibliotheque.hpp"
#include <iostream>
#include <sstream>

using namespace std;
//--------------------------------------------------
/*!
* \brief Constructeur de base
* \param user Nom de l'utilisateur associé à la bibliothèque
*/
Bibliotheque::Bibliotheque(string user) {
	//initilisation des attributs
	this->user = user;
	this->database = shared_ptr<BDConnector>(new BDConnector(user + ".db"));
	this->factoryOMDB = shared_ptr<FactoryOMDB>(new FactoryOMDB());
	this->responsable = shared_ptr<ResponsableFilm>(new ResponsableFilm(this->database));
	this->currentVideo = 0;
	
	//récupération des vidéos liées à cet utilisateur et enregistrées dans la base de données
	shared_ptr<FactorySQL> factorySQL(new FactorySQL(this->database));
	vector<shared_ptr<Video> > tmpFilms = factorySQL->recupererAllFilms();
	vector<shared_ptr<Video> > tmpSeries = factorySQL->recupererAllSeries();
	//ajouts des films & séries à la bibliothèque
	this->videos.insert(this->videos.end(), tmpFilms.begin(), tmpFilms.end());
	this->videos.insert(this->videos.end(), tmpSeries.begin(), tmpSeries.end());
}

//--------------------------------------------------
/*!
* \brief Destructeur
*/
Bibliotheque::~Bibliotheque() {
}

//--------------------------------------------------
/*!
* \brief Méthode qui renvoie le nom de l'utilisateur associé à la bibliothèque
* \return Le nom de l'utilisateur associé à la bibliothèque
*/
string Bibliotheque::getUser() {
	return this->user;
}

//--------------------------------------------------
/*!
* \brief Méthode qui définit le nom de l'utilisateur associé à la bibliothèque
* \param user Le nom de l'utilisateur à associer à la bibliothèque
*/
void Bibliotheque::setUser(string user) {
	this->user = user;
}

//--------------------------------------------------
/*!
* \brief Méthode qui
*/
vector<shared_ptr<Video>> Bibliotheque::getVideos() {
	return this->videos;
}

//--------------------------------------------------
/*!
* \brief Méthode qui ajoute une nouvelle vidéo (film ou episode) à la bibliothèque
* \param nom_video Titre de la vidéo à ajouter
* \param is_episode Le type de la vidéo
*/
void Bibliotheque::addVideo(string nom_video, string type_video) {
	//en fonction du type de la vidéo
	if(type_video == "Film") {
		//on récupère le film depuis IMDB
		shared_ptr<Film> film = this->factoryOMDB->makeVideo(this->factoryOMDB->queryTitle(nom_video));
		
		//on l'ajoute à la collection	
		this->videos.push_back(film);
		
		//on l'ajoute ensuite en base
		this->responsable->traiter(film,false,false);
		
	} else if(type_video == "Serie") {
		//on récupère la série depuis IMDB
		shared_ptr<Serie> serie = this->factoryOMDB->makeSerie(this->factoryOMDB->querySerie(nom_video));
		
		//on l'ajoute à la collection
		this->videos.push_back(serie);
		
		//on l'ajoute ensuite en base
		this->responsable->traiter(serie,false,false);
		
	} else {
		cout << "Erreur : type de vidéo inconnu" << endl;
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui sélectionne une vidéo (Film ou Série) de la bibliothèque
* \param titre Titre de la vidéo à sélectionner
*/
void Bibliotheque::selectVideo(string titre) {
	//on parcours la liste des vidéos
	for(const auto &video: this->videos) {
		//si le titre de la vidéo courante correspond au titre passé en paramètre
		if(video->getTitre() == titre) {
			this->currentVideo = video; //on mémorise la sélection
		}
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui sélectionne un épisode del la série actuellement sélectionnée
* \brief PRE : La vidéo actuellement sélectionnée doit être une série
* \param titre Titre de l'épisode à sélectionner
*/
void Bibliotheque::selectEpisode(string titre) {
	//on vérifie que le type de la vidéo actuellement sélectionée est bien Serie
	shared_ptr<Serie> currentSerie(dynamic_pointer_cast<Serie>(this->currentVideo));
	
	if(currentSerie) { //si c'est bien le cas
		
		//on récupère la liste des épisodes de la série
		vector<shared_ptr<Episode> > episodes = currentSerie->getEpisodes();
		
		//on recherche & sélectionne l'épisode en question
		for(const auto &episode: episodes) {
			//si le titre de l'épisode courant correspond au titre passé en paramètre
			if(episode->getTitre() == titre) {
				this->currentVideo = episode; //on mémorise la sélection
			}
		}
	}
}

//--------------------------------------------------
/*!
* \brief Méthode qui met à jour le statut de la vidéo sélectionnée
* \param vu Si la vidéo est vu ou non
* \param aVoir Si la vidéo est a voir ou non
*/
void Bibliotheque::setStatutCurrentVideo(bool vu, bool aVoir) {

	//mise à jour de la vidéo courante
	if(vu) {
		this->currentVideo->marquerVu();
	}
	if(aVoir) {
		this->currentVideo->marquerVoir();
	}

	//on transmet l'objet à la chaîne de responsabilité pour le mettre à jour en base
	this->responsable->traiter(this->currentVideo,false,false);
	
	cout << this->currentVideo->getStatut() << endl;
}
