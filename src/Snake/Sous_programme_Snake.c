//
// Created by Leroy on 30/04/2023.
//
#include "../../header.h"

t_corp_de_snake* Creer_maillon(t_corp_de_snake* maillon_precedent,BITMAP* tab_de_Skin[12]){
    t_corp_de_snake* Nouveau_maillon;

    Nouveau_maillon = (t_corp_de_snake*)malloc(sizeof(t_corp_de_snake));

    for (int i = 0; i < 12; ++i) {
        Nouveau_maillon->Skin[i] = tab_de_Skin[i];
    }
    Nouveau_maillon->skin_used = 0;

    Nouveau_maillon->x = maillon_precedent->last_x;
    Nouveau_maillon->y = maillon_precedent->last_y;

    Nouveau_maillon->last_x = Nouveau_maillon->x;
    Nouveau_maillon->last_y = Nouveau_maillon->y;

    Nouveau_maillon->tx = maillon_precedent->tx;
    Nouveau_maillon->ty = maillon_precedent->ty;

    Nouveau_maillon->dx = 0;
    Nouveau_maillon->dy = 0;

    Nouveau_maillon->next_corp = NULL;

    return Nouveau_maillon;
}
