//
// Created by Leroy on 13/05/2023.
//
#include "../../header.h"

void generation_Pomme(t_Pomme* Pomme){

    Pomme->x = rand()%(700-100+1)+100;
    Pomme->y = rand()%(570-100+1)+100;
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
