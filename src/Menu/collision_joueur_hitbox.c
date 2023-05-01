//
// Created by guych on 01/05/2023.
//

#include "../../header.h"

int collision_joueur_hitbox(t_hitbox * hitbox, t_joueur * joueur_actuel) {

    int retour;
    int m[4], imin, i;

    // Calcul des marges d'intersection (a2 par rapport à a1)
    m[0]=joueur_actuel->x + joueur_actuel->tx - hitbox->x1; // 0: à droite
    m[1]=hitbox->x2 - joueur_actuel->x; // 1: à gauche
    m[2]=joueur_actuel->y + joueur_actuel->ty - hitbox->y1; // 2: en bas
    m[3]=hitbox->y2 - joueur_actuel->y; // 3: en haut

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