//
// Created by Leroy on 27/04/2023.
//
#include "../../header.h"

void Snake(t_joueur Joueur[NOMBRE_JOUEURS]){

    /// Initialisation \\\

    // Variable double buffer
    BITMAP* page ;
    BITMAP* decor;

    // Variable Gestion des Skins
    BITMAP* SNAKE1[12];
    char nomfichier[256];
    int Animation = 0;
    int attente = 0;

    // Variable Serpent
    int Nombre_de_player = 1;
    t_corp_de_snake* head = NULL;
    t_corp_de_snake* head_tmp = NULL;
    int Longueur[2] = {0,0};

    // Variable joueur
    Joueur[1].tx = 29;
    Joueur[1].ty = 29;

    // Variable hitbox
    t_hitbox tab_hitboxes[4];

    //Variable Pomme
    t_Pomme Pomme [2];

    for (int i = 0; i < 2; ++i) {
        Pomme[i].Skin=load_bitmap("../assets/Item/Snake/Snake_pomme.bmp",NULL);
    }

    // Initialisation de la page
    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear(page);

    decor = load_bitmap("../assets/maps/Map_Snake.bmp",NULL);
    if (!decor){
        allegro_message("Impossible de charger le decor de Snake");
        exit(EXIT_FAILURE);
    }

    // charger les images de la séquence d'animation pour le corp du Snake

    for (int i=0;i<12;i++) {

        // sprintf permet de faire un printf dans une chaine
        sprintf(nomfichier, "../assets/personnages/Ti_Biscuit/Ti_Biscuit_%d.bmp",i);

        SNAKE1[i] = load_bitmap(nomfichier, NULL);
        if (!SNAKE1[i]) {
            allegro_message("pas pu trouver %s", nomfichier);
            exit(EXIT_FAILURE);
        }
    }


    for (int i = 0; i < 2; ++i) {

        // Création du Serpent Initial

        head = (t_corp_de_snake*)malloc(sizeof(t_corp_de_snake));

        // Remplissage du premier maillon

        head->dx = 5;
        head->dy = 0;
        head->skin_used = 6;
        head->tx = 48;
        head->ty = 48;
        head->y = 400;

        for (int j = 0; j < TAILLE_TAB; j=j+1) {
            head->last_x[j] = 400-(j*5);
            head->last_y[j] = 400-(j*5);
        }

        head->next_corp = NULL;

        for (int j = 0; j < 12; ++j) {
            head->Skin[j]=Joueur[i].sprites[j];
        }

        //Mise en place des 2 premieres parties du corps
        Longueur[0] = 1;
        for (int j = 0; j < 4; ++j) {
            Ajout_de_Longueur(head,SNAKE1,&Longueur[0]);
        }

        head_tmp = head;

        for (int j = 0; j < 5; ++j) {
            head_tmp->x=400-j*30;
            head_tmp = head_tmp->next_corp;
        }


        //Creation des Murs
        tab_hitboxes[0].x1 = 0;
        tab_hitboxes[0].y1 = 0;
        tab_hitboxes[0].x2 = 60;
        tab_hitboxes[0].y2 = SCREEN_H;

        tab_hitboxes[1].x1 = 60;
        tab_hitboxes[1].y1 = 0;
        tab_hitboxes[1].x2 = 892;
        tab_hitboxes[1].y2 = 76;

        tab_hitboxes[2].x1 = 60;
        tab_hitboxes[2].y1 = 689;
        tab_hitboxes[2].x2 = 892;
        tab_hitboxes[2].y2 = SCREEN_H;

        tab_hitboxes[3].x1 = 892;
        tab_hitboxes[3].y1 = 0;
        tab_hitboxes[3].x2 = SCREEN_W;
        tab_hitboxes[3].y2 = SCREEN_H;

        //Creation de la Pomme
        generation_Pomme(&Pomme[0]);


        /// Debut du Jeu \\\

        while (!key[KEY_ESC]){
            blit(decor,page,0,0,0,0,SCREEN_W, SCREEN_H);
            //Coordonée de la map = 60;76 892;689

            // Deplacement joueur

            if(key[KEY_RIGHT]){
                if(head->dx != -5){
                    head->dx = 5;
                    head->dy = 0;
                    head->skin_used = 6;
                }
            }
            if(key[KEY_LEFT]){
                if(head->dx != 5){
                    head->dx = -5;
                    head->dy = 0;
                    head->skin_used = 3;
                }
            }
            if(key[KEY_DOWN]){
                if(head->dy != -5) {
                    head->dy = 5;
                    head->dx = 0;
                    head->skin_used = 0;
                }
            }
            if(key[KEY_UP]){
                if(head->dy != 5) {
                    head->dy = -5;
                    head->dx = 0;
                    head->skin_used = 9;
                }
            }

            //Actualisation des positions du Snake et des Pommes
            Actualisation_Snake(head);
            for (int j = 0; j < Nombre_de_player; ++j) {
                Interaction_Pomme(head,&Pomme[j],&Longueur[0],SNAKE1);
            }

            //Affichage Pomme
            masked_blit(Pomme[0].Skin,page,0,0,Pomme[0].x,Pomme[0].y,29,29);

            // Affichage du Snake
            if (head->dy == 5){
                Invertion(head,page,Animation);
            }

            else {
                while (head_tmp != NULL){
                    masked_blit(head_tmp->Skin[(head_tmp->skin_used)+Animation],page,0,0,head_tmp->x,head_tmp->y,head_tmp->tx,head_tmp->ty);
                    head_tmp=head_tmp->next_corp;

                }
            }

            //Gestion de l'animation
            if (attente == 4){
                if (Animation == 1){
                    Animation = 0;
                } else{
                    Animation = 1 ;
                }
                attente = 0;
            }
            attente++;

            //Collision\\

            //Collision avec les murs
            Joueur[0].x = head->x;
            Joueur[0].y = head->y;
            for (int j = 0; j < 4; ++j) {
                if (collision_joueur_hitbox(&tab_hitboxes[j],&Joueur[0])){
                    printf("C'est perdu !\n");
                }
            }

            //Collision avec le corp du serpent
            head_tmp = head->next_corp->next_corp->next_corp->next_corp;

            while (head_tmp != NULL){
                if (Collision_Acteur(head,head_tmp)){
                    printf("C'est perdu !\n");

                }
                head_tmp = head_tmp->next_corp;

            }
            head_tmp = head;





            //Double buffer
            blit(page,screen,0,0,0,0,SCREEN_W, SCREEN_H);
            rest(20);
        }
    }

}