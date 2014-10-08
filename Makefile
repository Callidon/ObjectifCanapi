#---------------------------------------------------------
# Makefile pour le projet ObjectifCanapi
# Auteurs : Camille Le LUET & Thomas MINIER
#---------------------------------------------------------
CC = gcc
CXX = g++
SQLITEFLAGS = -lpthread -ldl

#---------------------------------------------------------
# Compilation complète du projet
#---------------------------------------------------------
all: objets
	echo "nothing yet"
	
objets:
	echo "nothing yet"

#---------------------------------------------------------
# Création du dossier de build
#---------------------------------------------------------
prepare:
	@if [ ! -d ./build ] ; then mkdir ./build ; fi;

#---------------------------------------------------------
# Bibliothèques (sqlite3)
#---------------------------------------------------------
sqlite:
	$(CC) -o build/$@.o libs/sqlite/$@.c $(SQLITEFLAGS) -c
	
#---------------------------------------------------------
# Compilations individuelles des différentes classes du projet
#---------------------------------------------------------
BDConnector:
	$(CXX) -o build/$@.o src/$@.cpp $(SQLITEFLAGS) -c

Bibliotheque:
	$(CXX) -o build/$@.o src/$@.cpp -c
	
Episode:
	$(CXX) -o build/$@.o src/$@.cpp -c
	
FactorySQL:
	$(CXX) -o build/$@.o src/$@.cpp -c
	
Film:
	$(CXX) -o build/$@.o src/$@.cpp -c
	
FilmObservateur:
	$(CXX) -o build/$@.o src/$@.cpp -c
	
Personne:
	$(CXX) -o build/$@.o src/$@.cpp -c
	
Serie:
	$(CXX) -o build/$@.o src/$@.cpp -c

Video:
	$(CXX) -o build/$@.o src/$@.cpp -c

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
