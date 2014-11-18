#---------------------------------------------------------
# Makefile pour le projet ObjectifCanapi
# Auteurs : Camille Le LUET & Thomas MINIER
#---------------------------------------------------------
CC = gcc
CXX = g++
FLAGS = -std=c++11
SQLITEFLAGS = -lpthread -ldl

#---------------------------------------------------------
# Compilation complète du projet
#---------------------------------------------------------
all: objets
	@echo "nothing yet"
	
objets:
	@echo "nothing yet"

#---------------------------------------------------------
# Création du dossier de build
#---------------------------------------------------------
prepare:
	@if [ ! -d ./build ] ; then mkdir ./build ; fi;

#---------------------------------------------------------
# Bibliothèques (sqlite3)
#---------------------------------------------------------
sqlite3:
	$(CC) -o build/$@.o libs/sqlite/$@.c $(SQLITEFLAGS) -c
	
#---------------------------------------------------------
# Compilations individuelles des différentes classes du projet
#---------------------------------------------------------
BDConnector: sqlite3
	$(CXX) $(FLAGS) -o build/$@.o src/BDConnector/$@.cpp $(SQLITEFLAGS) -c

Bibliotheque: FactorySQL FactoryOMDB
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
Episode: Video
	$(CXX) $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
	
FactoryOMDB:
	$(CXX) $(FLAGS) -o build/$@.o src/Factory/$@.cpp -c
	
FactorySQL:
	$(CXX) $(FLAGS) -o build/$@.o src/Factory/$@.cpp -c
	
Film: Video
	$(CXX) $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
#DEPRECATED 
FilmObservateur:
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
Personne:
	$(CXX) $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
	
Serie: Video Episode
	$(CXX) -g $(FLAGS) -o build/$@.o src/Video/$@.cpp -c
	
Test: Video Film Episode Bibliotheque
	$(CXX) $(FLAGS) src/$@.cpp build/Video.o build/Personne.o build/Film.o build/Episode.o build/Bibliotheque.o build/BDConnector.o build/sqlite3.o $(SQLITEFLAGS) -o test
	./test
	
TestFactory: Video Film Serie Episode BDConnector FactorySQL
	$(CXX) $(FLAGS) -g src/Factory/$@.cpp build/FactorySQL.o build/Video.o build/Serie.o build/Film.o build/Episode.o build/BDConnector.o build/sqlite3.o $(SQLITEFLAGS) -o testFactory
	./testFactory

TestFactoryOMDB: Video Film Serie Episode FactoryOMDB
	$(CXX) $(FLAGS) src/Factory/$@.cpp build/FactoryOMDB.o build/Video.o build/Film.o build/Serie.o build/Episode.o build/BDConnector.o build/sqlite3.o $(SQLITEFLAGS) -o testFactoryOMDB
	#gdb testFactoryOMDB
	./testFactoryOMDB

TestBibliotheque: Video Film Episode Serie Bibliotheque 
	$(CXX) $(FLAGS) src/$@.cpp build/Bibliotheque.o build/FactoryOMDB.o build/FactorySQL.o build/Video.o build/Film.o build/Serie.o build/Episode.o build/BDConnector.o build/sqlite3.o $(SQLITEFLAGS) -o testBibliotheque
	./testBibliotheque
	
Video:
	$(CXX) $(FLAGS) -o build/$@.o src/Video/$@.cpp -c

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
