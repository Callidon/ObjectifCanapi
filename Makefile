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
BDConnector:
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp $(SQLITEFLAGS) -c

Bibliotheque: Video
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
Episode: Video
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
FactorySQL:
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
Film: Video
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
FilmObservateur:
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
Personne:
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
Serie:
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c
	
Test: Video Film Episode
	$(CXX) $(FLAGS) src/$@.cpp build/Video.o build/Personne.o build/Film.o -o test
	./test
	
Video: Personne
	$(CXX) $(FLAGS) -o build/$@.o src/$@.cpp -c

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
