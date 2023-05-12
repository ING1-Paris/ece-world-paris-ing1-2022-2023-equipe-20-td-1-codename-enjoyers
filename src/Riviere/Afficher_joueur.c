//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Afficher_joueur(BITMAP *bmp, t_joueur_riv *joueur_a_afficher[NOMBRE_JOUEURS])
{

    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        masked_blit(joueur_a_afficher[i]->skin_perso[joueur_a_afficher[i]->skin_utilise],bmp,0,0,joueur_a_afficher[i]->x,joueur_a_afficher[i]->y,joueur_a_afficher[i]->tx,joueur_a_afficher[i]->ty);

    }

}
