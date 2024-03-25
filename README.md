# Projet Cornelis - Interpréteur de langage inspiré de Piet

Ce projet est un interpréteur pour un langage de programmation appelé Cornelis, qui est fortement inspiré du langage Piet. Cornelis tire son nom du célèbre artiste Pieter Mondriaan, plus connu sous le nom de Piet Mondrian, dont le travail est souvent associé à l'art abstrait.

Dans Cornelis, les programmes sont représentés sous la forme d'images en deux dimensions, où chaque pixel de l'image correspond à une instruction ou à une action spécifique. Ces images, qui ressemblent à des tableaux d'art abstrait, sont parcourues par l'interpréteur, ce qui déclenche l'exécution des actions correspondantes.

Dans un premier temps, j'ai dû implémenter un algorithme de parcours de l'image. Cet algorithme suit des règles précises. Il faut voir l'image comme des paquets de pixels connexes de même couleur. Le parcours de l'image va dépendre du nombre de pixels dans les paquets ainsi que de leur couleur. En plus des différentes couleurs, il y a les notions de pixels bloquants, pixels passants et pixels codants, qui changent le parcours de l'image.

En plus du parcours de l'image, il a fallu implémenter une pile d'entiers dynamique avec son lot de fonctions pour la modifier et la traiter. Ces fonctions sont ensuite appelées en fonction du parcours de l'image (En d'autres termes, en fonction des pixels rencontrés, de leur nombre et de leur couleur). Puis ces fonctions agissent sur la pile d'entiers, on peut ajouter des entiers à la pile, sommer les deux premiers entiers en haut de la pile, afficher le caractère ASCII correspondant à l'entier en haut de la pile et faire bien d'autres actions...

En résumé, ce projet fait appel à plusieurs compétences en C, en algorithmique et en traitement d'images. Ce projet m'a permis de concevoir et implémenter une solution logicielle pour un problème complexe.

**Enoncé du problème par Guillaume Burel :** [Enonce.html](Enonce.html)

**Mon rapport :** [Rapport_Alexis_Comsis.pdf](Rapport_Alexis_Comsis.pdf)

## Compilation et exécution :

pour compiler le programme il suffit d'exécuter la commande : 
make

pour exécuter le programme la commande est la suivante :
./prog nom_du_fichier.ppm

pour exécuter en mode DEBUG :
./prog nom_du_fichier.ppm -debug (Il faut ensuite appuyer sur entrée pour itérer le programme)


## Comportement attendu des programmes :

- 99bottles.ppm : affiche les paroles de la chanson "99bottles of beer on the wall"

- adder.ppm : prend en entrée deux entiers et affiche leur somme

- alpha.ppm : affiche les lettres de a à z

- cowsay.ppm : prend en entrée une ligne de texte et affiche une vache qui répète cette ligne

- euclide.ppm : prend en entrée deux entiers et affiche leur PGCD

- fact.ppm : prend en entrée un entier et affiche sa factorielle

- hw2.ppm : affiche "Hello, world!"

- hw3.ppm : affiche "Hello, world!"

- hw4.ppm : affiche "Hello, world!"

- mondrian.ppm : affiche "Hello, world!"

- Piet_hello.ppm : affiche "Hello, world!" (sans retour à la ligne)

- pietquest.ppm : propose un petit jeu

- pi.ppm : calcul une valeur approximative de pi

- power.ppm : prend en entrée deux entiers et affiche le premier à la puissance le second

- tetris.ppm : affiche "Tetris" sans retour à la ligne. (À noter : les blocs ont tous une forme de pièce en Tetris.)
