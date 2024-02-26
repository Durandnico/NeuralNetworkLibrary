# README
## Project : Neural Network Library
### Table des matières
1. [Pré-requis](#Pré-requis)
2. [Compiler](#compiler)
3. [Choisir une démo](#démo)
4. [Lancer l'exécutable](#exe)
5. [Supprimer les fichiers en .exe et .o](#suppr)
6. [Documentation Doxygen](#doxy)

#### Pré-requis
***
Install Eigen lib
```sh
wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
tar xzf eigen-3.4.0.tar.gz
```
#### Compiler
***
Pour compiler :
```sh
make
```
Cela créera aussi l'éxecutable.
#### Choisir une démo
***
Pour cela vous avez juste un déplacer un fichier du dossier démo dans src
/!\ Attention /!\ ne pas mettre plusieurs démo en même temps dans le fichier src ou la compilation échoura à cause de la présence de plusieurs functions maini

#### Lancer l'exécutable
***
Pour lancer l'exécutable :
```sh
./bin/output
```
### Supprimer les dossiers bin (executable), obj (fichiers .o) et doc (DoxyFile)
***
Pour supprimer les dossiers bin (executable), obj (fichiers .o) et doc (DoxyFile) :
```sh
make clean
```
#### Documentation Doxygen
***
En lançant cette commande :
```sh
make doc
```
La documentation Doxygen sera créée ou mise à jour si elle existe déjà.

Pour l'ouvrir dans Firefox faire :
```sh
make docHtml
```

### Crédits
***
Auteur : DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
