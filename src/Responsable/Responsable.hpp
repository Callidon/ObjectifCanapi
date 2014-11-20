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
#include "../BDConnector/BDConnector.hpp"

//--------------------------------------------------
/*!
* \class Responsable
* \brief Classe représentant un responsable abstrait chargé de gérer des objets Video
*/
class Responsable {
	
	protected:
		//Attributs
		std::shared_ptr<Responsable> suivant; //!< Pointeur vers le responsable suivant
		std::shared_ptr<BDConnector> database; //!< Base de données avec laquelle interargir
		//Méthodes protected
		void passerAuSuivant(std::shared_ptr<Video> video, bool vu, bool aVoir);
		void addActeur(std::string nom, std::string id_video);
		void addRealisateur(std::string nom, std::string id_video);
		
	public:
		//Constructeur & destructeur
		Responsable(std::shared_ptr<BDConnector> db, std::shared_ptr<Responsable> suiv);
		~Responsable();
		//Méthode publique
		virtual void traiter(std::shared_ptr<Video> video, bool vu, bool aVoir) = 0;

};
//--------------------------------------------------
#endif

