# Première reflexion 
Sur la modélisation de nos bin et nos items on à pensé à 

## Matrice 
Pas besoin de plus d'explication 

## Coordonées 
Pour alléger les calculs on peut faire un systéme de coordonées (on stocke haut gauche et bas droit en 2D) à partir de quoi on peut faire tout les calculs dont on a besoin

**Rotater** c'est inverser hauteur largeur, la coordonée haut gauche définit la position de l'item dans la bin.

Les **items sont assignés à une bin via un attribut** (un pointeur vers la bin).

# La modélisation 
On a une classe rectangle qui sert de base et qui contient largeur et hauteur

Les deux classes `bin` et `item` héritent de `rectangle`. 

**Rotater** c'est inverser hauteur largeur, la coordonée haut gauche définit la position de l'item dans la bin.

Les **items sont assignés à une bin via un attribut** (un pointeur vers la bin).
