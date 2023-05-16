//
// Created by lucie on 12/05/2023.
//

#include "../../header.h"

int Collision_joueur_rondin(t_rondin * rondin, t_joueur_riv * joueur){

    int retour;
    int m[4], imin, i;


    m[0] = rondin->posx + rondin->tx - joueur->x; // 0: à droite
    m[1] = rondin->posx + rondin->tx - joueur->x; // 1: à gauche
    m[2] = joueur->y + joueur->ty - rondin->posy; // 2: en bas
    m[3] = rondin->posy + rondin->ty - (joueur->y+joueur->ty); // 3: en haut

    // Chercher l'indice de la plus petite marge
    imin=0;
    for (i=1;i<4;i++)
        if (m[i]<m[imin])
            imin=i;

    // A priori pas de collision
    retour=0;

    // Si la plus petite marge n'est pas strictement négative
    // alors c'est qu'on a une collision et cette collision est de ce coté
    if (m[imin]>=0)
        retour=1;  // on retourne l'indice du coté + 1 (car 0 signifie "pas de collision")

    return retour;
}