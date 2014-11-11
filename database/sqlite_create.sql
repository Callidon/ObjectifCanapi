/* Fichier contenant les requêtes utlisées pour créer une base de donnée vierge */

CREATE TABLE Films (id_film TEXT primary key, titre TEXT, lien TEXT, annee INTEGER, synopsis TEXT, affiche TEXT, pays TEXT, vu INTEGER, aVoir INTEGER);
CREATE TABLE Series (id_serie TEXT primary key, titre TEXT, lien TEXT, annee INTEGER, synopsis TEXT, affiche TEXT, pays TEXT, vu INTEGER, aVoir INTEGER);
CREATE TABLE Episodes (id_episode TEXT primary key, titre TEXT, lien TEXT, annee INTEGER, affiche TEXT, synopsis TEXT, numero INTEGER, saison INTEGER, id_serie TEXT, pays TEXT, vu INTEGER, aVoir INTEGER);
CREATE TABLE Personnes (id_personne INTEGER primary key, nom TEXT);
CREATE TABLE Acteurs (id_acteur INTEGER primary key, id_video TEXT);
CREATE TABLE Realisateurs (id_real INTEGER primary key, id_video TEXT);
