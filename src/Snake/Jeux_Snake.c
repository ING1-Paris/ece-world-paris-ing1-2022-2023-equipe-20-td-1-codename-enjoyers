//
// Created by Leroy on 27/04/2023.
//
#include "../../header.h"

void Snake(t_joueur Joueur[NOMBRE_JOUEURS],unsigned long* Temps){

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
    int mode_de_jeu = 2;
    t_corp_de_snake* head[2] = {NULL,NULL};
    t_corp_de_snake* head_tmp[2] = {NULL,NULL};
    int Longueur[2] = {0,0};
    int Serpent_en_vie[2] = {1,1};

    // Variable hitbox
    t_hitbox tab_hitboxes[4];

    //Variable Pomme
    t_Pomme Pomme [2];
    for (int i = 0; i < 2; ++i) {
        Pomme[i].Skin=load_bitmap("../assets/Item/Snake/Snake_pomme.bmp",NULL);
    }

    //Variable Score
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        Joueur[i].score=0;
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

    //Creation des Murs
    tab_hitboxes[0].x1 = 0;
    tab_hitboxes[0].y1 = 0;
    tab_hitboxes[0].x2 = 60;
    tab_hitboxes[0].y2 = SCREEN_H;

    tab_hitboxes[1].x1 = 60;
    tab_hitboxes[1].y1 = 0;
    tab_hitboxes[1].x2 = 892;
    tab_hitboxes[1].y2 = 65;

    tab_hitboxes[2].x1 = 60;
    tab_hitboxes[2].y1 = 689;
    tab_hitboxes[2].x2 = 892;
    tab_hitboxes[2].y2 = SCREEN_H;

    tab_hitboxes[3].x1 = 900;
    tab_hitboxes[3].y1 = 0;
    tab_hitboxes[3].x2 = SCREEN_W;
    tab_hitboxes[3].y2 = SCREEN_H;

    //Creation des Pommes
    for (int i = 0; i < mode_de_jeu; ++i) {
        generation_Pomme(&Pomme[i]);
    }

    //Creation des Joueurs
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        // Création du Serpent Initial

        head[i] = (t_corp_de_snake*)malloc(sizeof(t_corp_de_snake));

        // Remplissage du premier maillon

        head[i]->dx = 5;
        head[i]->dy = 0;
        head[i]->skin_used = 6;
        head[i]->tx = 48;
        head[i]->ty = 48;
        head[i]->y = 400;

        for (int j = 0; j < TAILLE_TAB; j=j+1) {
            head[i]->last_x[j] = 400-(j*5)+(i*200);
            head[i]->last_y[j] = 400-(j*5);
        }

        head[i]->next_corp = NULL;

        for (int j = 0; j < 12; ++j) {
            head[i]->Skin[j]=Joueur[i].sprites[j];
        }

        //Mise en place des 2 premieres parties du corps
        Longueur[0] = 1;
        for (int j = 0; j < 4; ++j) {
            Ajout_de_Longueur(head[i],SNAKE1,&Longueur[0]);
        }

        head_tmp[i] = head[i];

        for (int j = 0; j < TAILLE_TAB-1; ++j) {
            head_tmp[i]->x=400-(j*30)+(i*200);
            head_tmp[i] = head_tmp[i]->next_corp;
        }
    }


    /// Debut du Jeu \\\

    //Debut du chronometre
    time_t begin = time(NULL);

    //Boucle de Jeu
    while (Fin_de_partie(Serpent_en_vie) != 1){

        blit(decor,page,0,0,0,0,SCREEN_W, SCREEN_H);
        //Coordonée de la map jouable= 60;76 892;689

        for (int j = 0; j < mode_de_jeu; ++j) {

            // Deplacement joueur
            if (j == 0 && Serpent_en_vie[0]==1)
                Deplacement_Snake_1(head[0]);
            else if (j==1 && Serpent_en_vie[1]==1)
                Deplacement_Snake_2(head[1]);


            //Actualisation des positions du Snake et des Pommes
            Actualisation_Snake(head[j]);
            for (int k = 0; k < mode_de_jeu; ++k) {
                Interaction_Pomme(head[j],&Pomme[k],&Longueur[j],SNAKE1);
            }

            //Affichage Pomme
            masked_blit(Pomme[j].Skin,page,0,0,Pomme[j].x,Pomme[j].y,29,29);


            // Affichage du Snake
            if (head[j]->dy == 5){
                Invertion(head[j],page,Animation);
            }

            else {

                while (head_tmp[j] != NULL){

                    masked_blit(head_tmp[j]->Skin[(head_tmp[j]->skin_used)+Animation],page,0,0,head_tmp[j]->x,head_tmp[j]->y,head_tmp[j]->tx,head_tmp[j]->ty);
                    head_tmp[j]=head_tmp[j]->next_corp;

                }
            }

            //Collision avec les murs
            Joueur[0].x = head[j]->x;
            Joueur[0].y = head[j]->y;

            for (int k = 0; k < 4; ++k) {

                if (collision_joueur_hitbox(&tab_hitboxes[k],&Joueur[0])){
                    Serpent_en_vie[j] = 0;
                    Mort_de_serpent(head[j]);
                }
            }

            //Collision avec le corp des serpents
            head_tmp[j]=head[j];
            for (int k = 0; k < mode_de_jeu; ++k) {


                if (head[j] == head_tmp[k])
                    head_tmp[k] = head[k]->next_corp->next_corp->next_corp->next_corp;
                else
                    head_tmp[k] = head[k]->next_corp;

                while (head_tmp[k] != NULL){
                    if (Collision_Acteur(head[j],head_tmp[k])){
                        Serpent_en_vie[j] = 0;
                        Mort_de_serpent(head[j]);

                    }
                    head_tmp[k] = head_tmp[k]->next_corp;

                }
                head_tmp[k] = head[k];
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

        //gestion du Score
        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            Joueur[i].score=Longueur[i]-4;
        }


        //Double buffer
        blit(page,screen,0,0,0,0,SCREEN_W, SCREEN_H);
        rest(20);
    }
    //gestion du temps
    time_t end = time(NULL);
    *Temps = (unsigned long) difftime(end,begin);
}