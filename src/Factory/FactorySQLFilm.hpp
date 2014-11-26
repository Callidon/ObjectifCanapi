/*!
* \file FactorySQLFilm.hpp
* \brief Fichier contenant la définition de la classe FactorySQLFilm
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef FACTORYSQLFILM_H
#define FACTORYSQLFILM_H

#include "FactorySQL.hpp"
#include "../BDConnector/BDConnector.hpp"

//--------------------------------------------------
/*!
* \class FactorySQLFilm
* \brief Classe réalisant l'interface FactoryBD & instanciant des objets Film à partir d'une base Sqlite
*/

class FactorySQLFilm: public FactorySQL {
	
	private:
		//Attribut
		std::shared_ptr<BDConnector> bd; //!< Connecteur vers la base de donnée où sont stocké les informations
		//Méthode privée
		std::shared_ptr<Film> genererFilm(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir);
		
	public:
		//Constructeur & destructeur
		FactorySQLFilm(std::shared_ptr<BDConnector> base);
		~FactorySQLFilm();
		//Méthode publique
		std::vector<std::shared_ptr<Video> > recupererAll();
		
};

//--------------------------------------------------
#endif
