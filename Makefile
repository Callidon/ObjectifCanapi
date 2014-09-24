#------------------
#Makefile pour le projet ObjectifCanapi
#Auteurs : LE LUET Camille & MINIER Thomas
#------------------

LIBSQLITE = -lpthread -ldl

#Création du dossier de build
prepare:
	@if [ ! -d ./build ] ; then mkdir ./build ; fi;

#Bibliothèque sqlite3
sqlite:
	gcc -o build/sqlite3.o libs/sqlite/sqlite3.c $(LIBSQLITE) -c build/
	
#Génération de la documentation Doxygen
doc:
	@if [ ! -d ./doxygen-pages ] ; then mkdir ./doxygen-pages ; fi;
	@doxygen doxygen.config
	
#Nettoyage du dossier de build
clean:
	@rm -rf ./build
