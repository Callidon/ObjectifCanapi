/*!
* \file Responsable.hpp
* \brief Fichier contenant les entêtes de la classe Responsable
* \author Camille Le Luët
* \author Thomas Minier
* \date ?
*/
#ifndef RESPONSABLE_H
#define RESPONSABLE_H
#include <string>
#include <vector>
#include <memory>
#include "../Video/Video.hpp"

//--------------------------------------------------
/*!
* \class Responsable
* \brief Classe représentant un responsable abstrait chargé de gérer des objets Video
*/
class Responsable {
	private:
		//Attributs
		std::shared_ptr<Responsable> suivant;
		std::shared_ptr<BDConnector> database;
	
	protected:
		void passerAuSuivant(std::shared_ptr<Video> video);
		
	public:
		//Constructeur & destructeur
		Responsable(std::shared_ptr<BDConnector> db, std::shared_ptr<Video> suiv);
		~Responsable();
		//Méthodes publiques
		virtual void traiter(std::shared_ptr<Video> video) = 0;

};
//--------------------------------------------------
#endif

