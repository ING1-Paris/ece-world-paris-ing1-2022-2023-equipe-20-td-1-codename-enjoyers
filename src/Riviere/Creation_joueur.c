//
// Created by lucie on 11/05/2023.
//


#include "../../header.h"

t_joueur_riv * Creation_joueur() {

    t_joueur_riv * mon_joueur;

    mon_joueur = (t_joueur_riv*) malloc(sizeof(t_joueur_riv));

    mon_joueur->x = 500;
    mon_joueur->y = 100;

    mon_joueur->tx = 48;
    mon_joueur->ty= 48;

    mon_joueur->dx = 7;
    mon_joueur->dy = 7;

    mon_joueur->skin_utilise = 0;

    mon_joueur->temps = 0;


    return mon_joueur;

}