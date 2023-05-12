//
// Created by lucie on 11/05/2023.
//

#include "../../header.h"

void Afficher_rondin(BITMAP *bmp, t_rondin *rondin_a_afficher)
{

    masked_blit(rondin_a_afficher->img,bmp,0,0,rondin_a_afficher->posx,rondin_a_afficher->posy,rondin_a_afficher->tx,rondin_a_afficher->ty);

}
