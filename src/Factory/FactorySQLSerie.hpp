/*!
* \file FactorySQLSerie.hpp
* \brief Fichier contenant la définition de la classe FactorySQLSerie
* \author Camille Le Luët
* \author Thomas Minier
* \date 26.11.2014
*/
#ifndef FACTORYSQLSERIE_H
#define FACTORYSQLSERIE_H

#include "FactorySQL.hpp"
#include "../BDConnector/BDConnector.hpp"

//--------------------------------------------------
/*!
* \class FactorySQLSerie
* \brief Classe réalisant l'interface FactorySQL & instanciant des objets Serie à partir d'une base Sqlite
*/

class FactorySQLSerie: public FactorySQL {
	
	private:
		//Attribut
		std::shared_ptr<BDConnector> bd; //!< Connecteur vers la base de donnée où sont stocké les informations
		//Méthodes privées
		std::shared_ptr<Serie> genererSerie(std::string id, std::string titre, std::string lien, int annee, std::string affiche, std::string synopsis, std::string pays, bool vu, bool aVoir);
		std::shared_ptr<Episode> genererEpisode(std::string id,std::string titre, std::string lien, int annee, std::string affiche, int numero, int saison, std::string id_serie, std::string synopsis, std::string pays, bool vu, bool aVoir);
		
	public:
		//Constructeur & destructeur
		FactorySQLSerie(std::shared_ptr<BDConnector> base);
		~FactorySQLSerie();
		//Méthode publique
		std::vector<std::shared_ptr<Video> > recupererAll();

};

//--------------------------------------------------
#endif
