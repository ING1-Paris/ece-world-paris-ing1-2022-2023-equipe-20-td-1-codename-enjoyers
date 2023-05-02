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

    Nouveau_maillon->x = -100;
    Nouveau_maillon->y = -100;


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

void Ajout_de_Longueur(t_corp_de_snake* Head,BITMAP* Tab_de_sprites[12],int * Longueur){
    *Longueur = *Longueur + 1;
    while (Head->next_corp != NULL){
        Head = Head->next_corp;
    }
    Head->next_corp = Creer_maillon(Head,Tab_de_sprites);
}

int Collision_Acteur(t_corp_de_snake* head,t_corp_de_snake* corp){
    int retour;
    int m[4], imin, i;

    m[0] = head->x + 30 - corp->x; // 0: à droite
    m[1] = corp->x + 30 - head->x; // 1: à gauche
    m[2] = head->y + 20 - corp->y; // 2: en bas
    m[3] = corp->y + 20 - head->y; // 3: en haut


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

void generation_Pomme(t_Pomme* Pomme){

    Pomme->x = rand()%(700-100+1)+100;
    Pomme->y = rand()%(600-100+1)+100;
}

int actualistation_Pomme(t_corp_de_snake* head,t_Pomme* Pomme){
    int retour;
    int m[4], imin, i;

    m[0] = head->x + 30 - Pomme->x; // 0: à droite
    m[1] = Pomme->x + 30 - head->x; // 1: à gauche
    m[2] = head->y  + 29 - Pomme->y; // 2: en bas
    m[3] = Pomme->y + 10 - head->y; // 3: en haut


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

void Interaction_Pomme(t_corp_de_snake* head,t_Pomme* Pomme,int *Longeur,BITMAP* tab_de_Skin[12]){
    if (actualistation_Pomme(head,Pomme)== 1){
        Ajout_de_Longueur(head,tab_de_Skin,Longeur);
        generation_Pomme(Pomme);
    }
}