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

    Nouveau_maillon->x = maillon_precedent->last_x[5];
    Nouveau_maillon->y = maillon_precedent->last_y[5];

    for (int i = 0; i < TAILLE_TAB; ++i) {
        Nouveau_maillon->last_x[i] = Nouveau_maillon->x;
        Nouveau_maillon->last_y[i] = Nouveau_maillon->y;
    }

    Nouveau_maillon->tx = 48;
    Nouveau_maillon->ty = 48;

    Nouveau_maillon->dx = 0;
    Nouveau_maillon->dy = 0;

    Nouveau_maillon->next_corp = NULL;

    return Nouveau_maillon;
}

void Actualisation_Snake(t_corp_de_snake* head){

    int temp[2][TAILLE_TAB];


    //Deplacement de la tete

    head->x = head->x + head->dx;
    head->y = head->y + head->dy;

    // Correction de l'image

    if (head->x < head->last_x[0]){
        head->last_x[TAILLE_TAB-2] = head->last_x[TAILLE_TAB-2]+15;
        head->last_y[TAILLE_TAB-2] = head->last_y[TAILLE_TAB-2]+2;
    }
    if (head->x > head->last_x[0]){
        head->last_y[TAILLE_TAB-2] = head->last_y[TAILLE_TAB-2]+2;
    }

    if(head->y != head->last_y[0]){
        head->last_x[TAILLE_TAB-2] = head->last_x[TAILLE_TAB-2]+8;
    }

    //Deplacement du corp

    while (head->next_corp != NULL){

        for (int i = 0; i < TAILLE_TAB; ++i) {
            temp[0][i]= head->last_x[i];
            temp[1][i]= head->last_y[i];
        }

        for (int i = 0; i < TAILLE_TAB; ++i) {
            head->last_x[i+1] = temp[0][i] ;
            head->last_y[i+1] = temp[1][i] ;
        }

        head->last_x[0] = head->x ;
        head->last_y[0] = head->y ;

        //Direction de l'image
        /*if (head->next_corp->last_x[0] > head->next_corp->x){
            //direction a gauche
            head->next_corp->skin_used = 3;
        }

        if (head->next_corp->last_x[0] < head->next_corp->x){
            //direction a droite
            head->next_corp->skin_used = 6;
        }

        if (head->next_corp->last_y[0] > head->next_corp->y){
            //direction en haut
            head->next_corp->skin_used = 9;
        }

        if (head->next_corp->last_y[0] < head->next_corp->y){
            //direction en bas
            head->next_corp->skin_used = 0;
        }*/

        head->next_corp->x=head->last_x[TAILLE_TAB-1] ;
        head->next_corp->y=head->last_y[TAILLE_TAB-1] ;

        head = head->next_corp;
    }
}

void Invertion(t_corp_de_snake* Liste_init,BITMAP* page,int Animation){
    if (Liste_init != NULL){
        Invertion(Liste_init->next_corp,page,Animation);
        masked_blit(Liste_init->Skin[Liste_init->skin_used+Animation],page,0,0,Liste_init->x,Liste_init->y,Liste_init->tx,Liste_init->ty);

    }
}


