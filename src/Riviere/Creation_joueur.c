//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

t_joueur_riv Creation_joueur(t_joueur joueur[NOMBRE_JOUEURS]){

    t_joueur_riv mon_joueur;

    //mon_joueur = (t_joueur_riv*)malloc(sizeof(t_joueur_riv));

    mon_joueur.x = 500;
    mon_joueur.y = 145;

    mon_joueur.tx = 48;
    mon_joueur.ty= 48;

    mon_joueur.dx = 10;
    mon_joueur.dy = 10;

    mon_joueur.skin_utilise = 1;

    mon_joueur.temps = 0;

    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        mon_joueur.skin_perso[i] = joueur[i].sprites[i];
    }

    return mon_joueur;

}