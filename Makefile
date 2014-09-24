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
	gcc libs/sqlite/sqlite3.c $(LIBSQLITE) -c
	
#Nettoyage du dossier de build
clean:
	@rm -rf ./build
