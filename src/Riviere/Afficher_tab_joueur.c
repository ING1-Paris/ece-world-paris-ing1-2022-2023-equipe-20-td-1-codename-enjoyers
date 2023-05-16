//
// Created by lucie on 15/05/2023.
//

#include "../../header.h"

void Afficher_tab_joueur(BITMAP *bmp, t_joueur_riv *tab_joueur[NOMBRE_JOUEURS]){

    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        Afficher_joueur(bmp,tab_joueur[i]);

    }

}