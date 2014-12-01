ObjectifCanapi
==============

Catalogue de films & séries réalisé pour le projet de **Design & Développement d'application**, matière enseignée dans le cadre de la Licence 3 Informatique à l'Université de Nantes.      
Cette application gère une bibliothèque de films et de séries, interargit avec [IMDB](http://www.imdb.com/) (Internet Movie Database) gère les multiples utlisateurs et sauvegarde les informations dans une base de données.

Compilation
----------
Pour compiler tout le programme, lancer la commande suivante
```
make
```

Pour exécuter l'application, lancer la commande suivante 
```
make exec
```

Utilisation
----------
Une fois le prgramme lancé, il vous sera demandé votre pseudo. Une fois ce dernier siais, vous arriverez dans un menu. Sélectionner l'option correspondant à votre choix.  

###Menu principal
Il s'agit du menu principal qui gère toute l'application.    
* L'option n°1, **Mes vidéos marquées**, vous affiche les vidéos présentes dans votre bibliothèque. Il vous sera demandée si vous voulez sélectionner une vidéo ou non. La saisie de *y*, pour oui, vous demande la saisie du numéro de la vidéo que vous souhaitez sélectionner, puis vous ouvre le sous-menu **Gestion d'une vidéo**. La saisie de *n*, pour non, vous renvoie au menu principal.
* L'option n°2, **Recherche**, vous permet de rechercher et d'ajouter une vidéo à votre bibliothèque. Il vous sera demandé si vous souhaitez ajouter un film ou une série. Saisissez *1* pour la première option et *2* pour la seconde. Si vous recherchez une série, il vous faudra attendre quelques secondes. La vidéo sera ensuite ajoutée à votre bibliothèque puis le sous-menu **Gestion d'une vidéo** s'ouvrira pour vous permettre de gérer cette nouvelle vidéo.
* L'option n°3, **Déconnexion**, vous déconnecte et vous renvoie à l'écran de saisie d'un pseudo.
* L'option n°4, **Quitter**, ferme l'application.

###Menu : Gestion d'une vidéo
Il s'agit du sous menu qui permet de gérer une vidéo (soit un film, une série ou un épisode).    
* L'option n°1, **Marquer la vidéo "à voir"**, vous permet de marquer la vidéo sélectionnée comme étant à voir.
* L'option n°2, **Marquer la vidéo "vu"**, vous permet de marquer la vidéo sélectionnée comme étant vue.
* L'option n°3, **Voir statut**, vous permet de savoir quel est le marquage de la vidéo (vu, à voir ou non marquée).
* L'option n°4, **Afficher les informations**, vous permet d'afficher les informatiosn relatives à la vidéo.
* L'option n°5, **Voir l'affiche**, ferme l'application et ouvre un aperçu de l'affiche de la vidéo dans Firefox.
* L'option n°6, **Rechercher la bande-annonce**, ferme l'application et ouvre une recherche Youtube de la bande annonce de la vidéo.
* L'option n°7, **Liste des épisodes**, qui n'est utlisable que si une série est sélectionnée, permet de sélectionner un épisode parmi la liste des épisodes de la série. Cela fonctionne de la même manière qu'avec la sélection d'une vidéo normale (voir l'option n°1 du menu principal).
* L'option n°8, **Retour**, permet de revenir au menu principal.

Diagramme UML
----------
![UML](http://i.imgur.com/9RTNkJ0.png)

Bibliothèques et APIs utilisées
----------
* [Sqlite](http://www.sqlite.org/), une solution efficace pour gérer une base de données en C++
* [OMDB](http://www.omdbapi.com/), API open source et non officielle de IMDB

*Copyright © 2014 Camille Le Luët & Thomas Minier*
