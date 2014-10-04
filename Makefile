#---------------------------------------------------------
# Makefile pour le projet ObjectifCanapi
# Auteurs : Camille Le LUET & Thomas MINIER
#---------------------------------------------------------

LIBSQLITE = -lpthread -ldl

all: BDConnector
	g++ src/test.cpp build/sqlite3.o build/BDConnector.o -o test.exe $(LIBSQLITE)

#---------------------------------------------------------
# Création du dossier de build
#---------------------------------------------------------
prepare:
	@if [ ! -d ./build ] ; then mkdir ./build ; fi;

#---------------------------------------------------------
# Bibliothèque sqlite3
#---------------------------------------------------------
sqlite:
	gcc -o build/sqlite3.o libs/sqlite/sqlite3.c $(LIBSQLITE) -c
	
#---------------------------------------------------------
# Diverses classes du projet
#---------------------------------------------------------
BDConnector:
	g++ -o build/BDConnector.o src/BDConnector.cpp $(LIBSQLITE) -c
	
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
