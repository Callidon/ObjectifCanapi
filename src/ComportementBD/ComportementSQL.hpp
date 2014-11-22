/*!
* \file ComportementSQL.hpp
* \brief Fichier contenant les entêtes de la classe ComportementSQL
* \author Camille Le Luët
* \author Thomas Minier
* \date 22.11.2014
*/

#ifndef COMPORTEMENTSQL_H
#define COMPORTEMENTSQL_H
#include <string>
#include <vector>
#include <memory>
#include "ComportementBD.hpp"
#include "../BDConnector/BDConnector.hpp"

//--------------------------------------------------
/*!
* \class ComportementSQL
* \brief Interface représentant un comportement vis à vis d'une base de données SQL
*/
class ComportementSQL : public ComportementBD {
		
	protected:
		//Attribut
		std::shared_ptr<BDConnector> database; //!< Pointeur vers la base de données
		//Méthodes protected (héritées de ComportementBD)
		void addActeur(std::string nom, std::string id_video);
		void addRealisateur(std::string nom, std::string id_video); 
		
	public:
		//Constructeur & destructeur
		ComportementSQL(std::shared_ptr<BDConnector> db);
		~ComportementSQL();
		//Méthodes publiques (héritées de ComportementBD)
		void traiterFilm(std::shared_ptr<Film> film, bool vu, bool aVoir);
		void traiterSerie(std::shared_ptr<Serie> serie, bool vu, bool aVoir);
		void traiterEpisode(std::shared_ptr<Episode> episode, bool vu, bool aVoir);

};
//--------------------------------------------------
#endif
