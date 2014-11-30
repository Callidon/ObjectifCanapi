#---------------------------------------------------------
# Makefile pour le projet ObjectifCanapi
# Auteurs : Camille Le LUËT & Thomas MINIER
#---------------------------------------------------------

#---------------------------------------------------------
# Variables
#---------------------------------------------------------
# Flags utilisés
CC = @ gcc
CXX = @ g++
FLAGS = -std=c++0x
SQLITEFLAGS = -lpthread -ldl
# Liste de tous les objets du projet
OBJETS = BDConnector Bibliotheque ComportementSQL Episode FactorySQLFilm FactorySQLSerie FactoryOMDBFilm FactoryOMDBSerie Film Responsable ResponsableEpisode ResponsableFilm ResponsableSerie Serie sqlite3 Video
DEPENDANCES = $(foreach file, $(OBJETS), build/$(file).o)

#---------------------------------------------------------
# Compilation complète du projet & éxecution
#---------------------------------------------------------
all: $(OBJETS)
	$(CXX) $(FLAGS) main.cpp $(DEPENDANCES) $(SQLITEFLAGS) -o main

exec:
	@echo "nothing yet"
#---------------------------------------------------------
# Création du dossier de build
#---------------------------------------------------------
prepare:
	@if [ ! -d ./build ] ; then mkdir ./build ; fi;

#---------------------------------------------------------
# Bibliothèque annexe (sqlite3)
#---------------------------------------------------------
sqlite3:
	$(CC) -o build/$@.o libs/sqlite/$@.c $(SQLITEFLAGS) -c
	
#---------------------------------------------------------
# Compilations individuelles des différentes classes du projet
#---------------------------------------------------------
BDConnector:
	@echo "Patience....."
	$(CXX) $(FLAGS) -o build/$@.o src/BDConnector/$@.cpp $(SQLITEFLAGS) -c

Bibliotheque:
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
ComportementSQL:
	$(CXX) $(FLAGS) -o build/$@.o src/ComportementBD/$@.cpp -c
	
Episode:
	$(CXX) $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
	
FactoryOMDBFilm:
	$(CXX) $(FLAGS) -o build/$@.o src/Factory/$@.cpp -c

FactoryOMDBSerie:
	$(CXX) $(FLAGS) -o build/$@.o src/Factory/$@.cpp -c
	
FactorySQLSerie:
	$(CXX) $(FLAGS) -o build/$@.o src/Factory/$@.cpp -c

FactorySQLFilm:
	$(CXX) $(FLAGS) -o build/$@.o src/Factory/$@.cpp -c
	
Film:
	$(CXX) $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
	
Responsable:
	$(CXX) $(FLAGS) -o build/$@.o src/Responsable/$@.cpp -c
	
ResponsableFilm:
	$(CXX) $(FLAGS) -o build/$@.o src/Responsable/$@.cpp -c

ResponsableSerie:
	$(CXX) $(FLAGS) -o build/$@.o src/Responsable/$@.cpp -c
	
ResponsableEpisode:
	$(CXX) $(FLAGS) -o build/$@.o src/Responsable/$@.cpp -c
	
Serie:
	$(CXX) -g $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
	
Video:
	$(CXX) $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
	
Main: $(OBJETS) 
	$(CXX) -g $(FLAGS) src/$@.cpp $(foreach file, $^, build/$(file).o) $(SQLITEFLAGS) -o main
	@clear
	@ gdb main
#---------------------------------------------------------
# Compilaton des programmes utlisées pour tester les différents modules
#---------------------------------------------------------

Test: Video Film Episode Bibliotheque
	$(CXX) $(FLAGS) src/$@.cpp build/Video.o build/Personne.o build/Film.o build/Episode.o build/Bibliotheque.o build/BDConnector.o build/sqlite3.o $(SQLITEFLAGS) -o test
	./test
	
TestFactory: Video Film Serie Episode BDConnector FactorySQL
	$(CXX) $(FLAGS) -g src/Factory/$@.cpp build/FactorySQL.o build/Video.o build/Serie.o build/Film.o build/Episode.o build/BDConnector.o build/sqlite3.o $(SQLITEFLAGS) -o testFactory
	./testFactory
#include <iostream>
TestFactoryOMDB: Video Film Serie Episode FactoryOMDBFilm FactoryOMDBSerie
	$(CXX) -g $(FLAGS) src/Factory/$@.cpp build/FactoryOMDBFilm.o build/FactoryOMDBSerie.o  build/Video.o build/Film.o build/Serie.o build/Episode.o build/BDConnector.o build/sqlite3.o $(SQLITEFLAGS) -o testFactoryOMDB
	gdb testFactoryOMDB

TestBibliotheque: $(OBJETS) 
	$(CXX) $(FLAGS) src/$@.cpp $(foreach file, $^, build/$(file).o) $(SQLITEFLAGS) -o testBibliotheque
	./testBibliotheque
	
#---------------------------------------------------------
# Génération de la documentation Doxygen
#---------------------------------------------------------
doc:
	@if [ ! -d ./doxygen-pages ] ; then mkdir ./doxygen-pages ; fi;
	@doxygen doxygen.config

#---------------------------------------------------------
# Nettoyage du dossier de build
#---------------------------------------------------------
clean:
	@rm -rf ./build
