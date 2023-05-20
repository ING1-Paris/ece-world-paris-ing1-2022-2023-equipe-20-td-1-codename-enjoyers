//
// Created by thais on 15/05/2023.
//
#include "../../header.h"

/// Gérer les collisions (éventuelles) entre un acteur (un tir du joueur) et un ballon

void collisionActeur(t_ballon * ballon ,t_acteur * acteur) {

    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // s'il est dans le ballon alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre ballon
        vx = acteur->x+acteur->tx/2 - (ballon->x+ballon->tx/2);
        vy = acteur->y+acteur->ty/2 - (ballon->y+ballon->ty/2);


        // calcul distance au carré au centre du ballon (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ballon->tx * ballon->tx / 4 ){
            destinActeur(acteur);
            ballon->dy = ballon->dy - 15 ;
        }
    }
}





// Gérer les collisions entre les acteurs (tous les tirs) et un ballon_bleu
void collisionListeActeurs(t_ballon *ballon,t_listeActeurs *la) {

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeur(ballon,la->tab[i]);

}


