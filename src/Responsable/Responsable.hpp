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
		std::shared_ptr<Responsable> suivant; //!< Pointeur vers le responsable suivant
		std::shared_ptr<BDConnector> database; //!< Base de données avec laquelle interargir
	
	protected:
		//Méthodes protected
		void passerAuSuivant(std::shared_ptr<Video> video);
		void addActeur(std::string nom, std::string id_video);
		void addRealisateur(std::string nom, std::string id_video);
		
	public:
		//Constructeur & destructeur
		Responsable(std::shared_ptr<BDConnector> db, std::shared_ptr<Video> suiv);
		~Responsable();
		//Méthode publique
		virtual void traiter(std::shared_ptr<Video> video) = 0;

};
//--------------------------------------------------
#endif

