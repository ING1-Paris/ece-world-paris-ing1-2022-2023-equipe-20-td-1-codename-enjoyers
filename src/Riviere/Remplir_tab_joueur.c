//
// Created by lucie on 15/05/2023.
//


#include "../../header.h"

void Remplir_tab_joueur(t_joueur_riv *tab_joueur[NOMBRE_JOUEURS]) {

    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        tab_joueur[i] = Creation_joueur();
    }

}