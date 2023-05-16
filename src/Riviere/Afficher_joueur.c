//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Afficher_joueur(BITMAP *bmp, t_joueur_riv *joueur_a_afficher)
{

    masked_blit(joueur_a_afficher->skin_perso[joueur_a_afficher->skin_utilise],bmp,0,0,joueur_a_afficher->x,joueur_a_afficher->y,joueur_a_afficher->tx,joueur_a_afficher->ty);


}
