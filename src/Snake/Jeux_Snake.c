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

    BITMAP* test;

    // Variable Serpent
    t_corp_de_snake* head = NULL;
    t_corp_de_snake* head_tmp = NULL;
    int Longueur = 0;

    // Variable joueur
    Joueur[1].tx = 29;
    Joueur[1].ty = 29;

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

        head->dx=0;
        head->dy=0;
        head->tx = Joueur[i].tx;
        head->ty = Joueur[i].ty;
        head->x = 400;
        head->y = 400;
        for (int j = 0; j < TAILLE_TAB*30; j=j+30) {
            head->last_x[i] = 400-j;
            head->last_y[i] = 400-j;
        }

        head->next_corp = NULL;
        head->skin_used = 0;

        /*for (int j = 0; j < 12; ++j) {
            head->Skin[j]=Joueur[i].Skin[j];
        }*/

        // Temporaire
        test = load_bitmap("../assets/personnages/Farquaad/Farquaad_0.bmp",NULL);

        if (!test){
            allegro_message("Impossible de charger le personnage");
            exit(EXIT_FAILURE);
        }
        head->Skin[0]=test;

        head->next_corp= Creer_maillon(head,SNAKE1);


        head->next_corp->next_corp= Creer_maillon(head->next_corp,SNAKE1);
        Longueur = 3;

        head->next_corp->x=370;
        head->next_corp->next_corp->x=340;

        head_tmp = head;
        /// Debut du Jeu \\\

        while (!key[KEY_ESC]){
            blit(decor,page,0,0,0,0,SCREEN_W, SCREEN_H);

            // Deplacement joueur

            if(key[KEY_RIGHT]){
                if(head->dx != -5){
                    head->dx = 5;
                    head->dy = 0;
                }
            }
            if(key[KEY_LEFT]){
                if(head->dx != 5){
                    head->dx = -5;
                    head->dy = 0;
                }
            }
            if(key[KEY_DOWN]){
                if(head->dy != -5) {
                    head->dy = 5;
                    head->dx = 0;
                }
            }
            if(key[KEY_UP]){
                if(head->dy != 5) {
                    head->dy = -5;
                    head->dx = 0;
                }
            }

            //Actualisation des positions du Snake
            Actualisation_Snake(head);

            // Affichage du Snake
            if (head->dy == 5){
                Invertion(head,page);
            }
            else {
                for (int j = 0; j < Longueur; ++j) {
                    masked_blit(head_tmp->Skin[head_tmp->skin_used],page,0,0,head_tmp->x,head_tmp->y,head_tmp->tx,head_tmp->ty);
                    head_tmp=head_tmp->next_corp;
                }
                head_tmp=head;
            }

            blit(page,screen,0,0,0,0,SCREEN_W, SCREEN_H);
            rest(20);
        }
    }

}