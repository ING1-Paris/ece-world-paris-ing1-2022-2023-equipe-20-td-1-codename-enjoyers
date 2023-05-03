//
// Created by guych on 03/05/2023.
//

#include "../../header.h"

int collision_cercles(t_cercle_fixe *a1, t_note *a2)
{
    int retour;
    int m[4],imin,i;



    // Calcul des marges d'intersection (a2 par rapport à a1)
    m[0]=a2->x_centre + a2->radius - a1->x_centre; // 0: à droite
    m[1]=a1->x_centre + a1->radius - a2->x_centre; // 1: à gauche
    m[2]=a2->y_centre + a2->radius - a1->y_centre; // 2: en bas
    m[3]=a1->y_centre + a1->radius - a2->y_centre; // 3: en haut

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