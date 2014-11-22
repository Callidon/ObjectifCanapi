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
#include "../ComportementBD/ComportementBD.hpp"

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
		std::shared_ptr<ComportementBD> comportement; //!< Comportement à utiliser pour traiter les objets
		
		//Méthode protected
		void passerAuSuivant(std::shared_ptr<Video> video, bool vu, bool aVoir);
		
	public:
		//Constructeur & destructeur
		Responsable(std::shared_ptr<BDConnector> db, std::shared_ptr<Responsable> suiv);
		~Responsable();
		//Méthodes publiques
		void setComportement(std::shared_ptr<ComportementBD> comp);
		std::shared_ptr<ComportementBD> getComportement();
		virtual void traiter(std::shared_ptr<Video> video, bool vu, bool aVoir) = 0;

};
//--------------------------------------------------
#endif

