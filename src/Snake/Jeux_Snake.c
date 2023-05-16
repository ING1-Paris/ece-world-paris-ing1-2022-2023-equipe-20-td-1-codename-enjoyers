//
// Created by Leroy on 27/04/2023.
//
#include "../../header.h"

void Snake(t_joueur * Joueur, int tab_temps[NOMBRE_JOUEURS]) {

    /// Initialisation \\\


    // Variable double buffer
    BITMAP* page ;
    BITMAP* decor;

    // Variable Gestion des Skins
    t_joueur hitbox;
    BITMAP* SNAKE1[12];
    char nomfichier[256];
    int Animation = 0;
    int attente = 0;
    BITMAP * Nom_du_jeu = load_bitmap("../assets/Item/Snake/Nom_du_Snake.bmp",NULL);

    // Variable Serpent
    t_corp_de_snake* head[NOMBRE_JOUEURS] = {NULL,NULL};
    t_corp_de_snake* head_tmp[NOMBRE_JOUEURS] = {NULL,NULL};
    int Longueur[NOMBRE_JOUEURS] = {0,0};
    int Serpent_en_vie[NOMBRE_JOUEURS] = {1,1};

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
    int alive_temps[NOMBRE_JOUEURS]={1,1};
    time_t Mort_du_seprent[NOMBRE_JOUEURS];

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
    tab_hitboxes[0].x2 = 75;
    tab_hitboxes[0].y2 = SCREEN_H;

    tab_hitboxes[1].x1 = 75;
    tab_hitboxes[1].y1 = 0;
    tab_hitboxes[1].x2 = 888;
    tab_hitboxes[1].y2 = 75;

    tab_hitboxes[2].x1 = 75;
    tab_hitboxes[2].y1 = 640;
    tab_hitboxes[2].x2 = 888;
    tab_hitboxes[2].y2 = SCREEN_H;

    tab_hitboxes[3].x1 = 888;
    tab_hitboxes[3].y1 = 0;
    tab_hitboxes[3].x2 = SCREEN_W;
    tab_hitboxes[3].y2 = SCREEN_H;

    //Creation des Pommes
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
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
        Longueur[i] = 1;
        for (int j = 0; j < 4; ++j) {
            Ajout_de_Longueur(head[i],SNAKE1,&Longueur[i]);
        }

        head_tmp[i] = head[i];

        for (int j = 0; j < TAILLE_TAB-1; ++j) {
            head_tmp[i]->x=400-(j*30)+(i*200);
            head_tmp[i] = head_tmp[i]->next_corp;
        }
    }

    blit(decor,page,0,0,0,0,SCREEN_W, SCREEN_H);

    //menu avant le jeu
    while (!key[KEY_SPACE]){

        masked_blit(Nom_du_jeu,page,0,0,SCREEN_W/2-200,50,400,178);
        rectfill(page,340,200,640,220,makecol(255,255,255));
        rect(page,340,200,640,220,makecol(0,0,0));
        textprintf_ex(page,font,350,210, makecol(0,0,0),-1,"Appuyer sur 'Space' Pour commencer !");

        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            head[i]->skin_used=2;
            Invertion(head[i],page,Animation);

        }
        blit(page,screen,0,0,0,0,SCREEN_W, SCREEN_H);
    }
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        head[i]->skin_used=6;
    }


    /// Debut du Jeu \\\

    //Debut du chronometre
    time_t begin = time(NULL);

    //Boucle de Jeu
    while (Fin_de_partie(Serpent_en_vie) != 1){

        blit(decor,page,0,0,0,0,SCREEN_W, SCREEN_H);
        //Coordonée de la map jouable= 60;76 892;689

        for (int j = 0; j < NOMBRE_JOUEURS; ++j) {

            // Deplacement joueur
            if (j == 0 && Serpent_en_vie[0]==1)
                Deplacement_Snake_1(head[0]);
            else if (j==1 && Serpent_en_vie[1]==1)
                Deplacement_Snake_2(head[1]);


            //Actualisation des positions du Snake et des Pommes
            Actualisation_Snake(head[j]);
            for (int k = 0; k < NOMBRE_JOUEURS; ++k) {
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
            hitbox.x = head[j]->x;
            hitbox.y = head[j]->y;
            hitbox.tx = hitbox.ty = 48;

            for (int k = 0; k < 4; ++k) {

                if (collision_joueur_hitbox(&tab_hitboxes[k],&hitbox)){
                    Serpent_en_vie[j] = 0;
                    Mort_de_serpent(head[j]);
                }
            }

            //Collision avec le corp des serpents
            head_tmp[j]=head[j];
            for (int k = 0; k < NOMBRE_JOUEURS; ++k) {


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
            Joueur[i].score=Longueur[i]-5;
        }

        //Gestion de L'interface in game

        //J1
        rectfill(page,10,10,250,70,makecol(255,255,255));
        rect(page,10,10,250,70,makecol(0,0,0));
        stretch_blit(Joueur[0].sprites[12],page,0,0,225,225,15,15,50,50);

        textprintf_ex(page,font,70, 30, makecol(0,0,0),-1,"%s",Joueur[0].nom);
        textprintf_ex(page,font,70, 50, makecol(0,0,0),-1,"Score: %d",Joueur[0].score);

        //J2
        rectfill(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(255,255,255));
        rect(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(0,0,0));
        stretch_blit(Joueur[1].sprites[12],page,0,0,225,225,SCREEN_W-250+5,15,50,50);

        textprintf_ex(page,font,SCREEN_W-250+5+55, 30, makecol(0,0,0),-1,"%s",Joueur[1].nom);
        textprintf_ex(page,font,SCREEN_W-250+5+55, 50, makecol(0,0,0),-1,"Score: %d",Joueur[1].score);

        //gestion du temps
        for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
            if (Serpent_en_vie[i]==0 && alive_temps[i]==1){
                Mort_du_seprent[i] = time(NULL);
                alive_temps[i]=0;
            }
        }


        //Double buffer
        blit(page,screen,0,0,0,0,SCREEN_W, SCREEN_H);
        rest(20);
    }

    /// Fin DU JEU \\\

    //gestion du temps en fin de partie
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        tab_temps[i] = (int) difftime(Mort_du_seprent[i], begin);
        printf("Le joueur %d est reste en vie pendant %d\n", i+1, tab_temps[i]);
    }


    //Information de fin de jeu
    masked_blit(Nom_du_jeu,page,0,0,SCREEN_W/2-200,50,400,178);
    rectfill(page,340,200,640,220,makecol(255,255,255));
    rect(page,340,200,640,220,makecol(0,0,0));

    if (Joueur[0].score > Joueur[1].score){
        textprintf_ex(page,font,350,210, makecol(0,0,0),-1,"Le Joueur %s gagne !",Joueur[0].nom);
        Joueur[0].tickets = Joueur[0].tickets + 1;
    }
    else {
        textprintf_ex(page,font,350,210, makecol(0,0,0),-1,"Le Joueur %s gagne !",Joueur[1].nom);
        Joueur[1].tickets = Joueur[1].tickets + 1;
    }

    blit(page,screen,0,0,0,0,SCREEN_W, SCREEN_H);

    alert("Fin du jeu !", NULL, NULL, "Retour au menu", NULL, 0, 0);

    //destruction des bitmaps du snake et liberation de la liste chainée
    destroy_bitmap(page);
    destroy_bitmap(decor);
    destroy_bitmap(Nom_du_jeu);
    for (int i = 0; i < 2; ++i) {
        destroy_bitmap(Pomme[i].Skin);
    }

    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        while (head[i] != NULL) {

            head_tmp[0] = head[i]->next_corp;
            free(head[i]);
            head[i] = head_tmp[0];
        }
    }
    for (int i = 0; i < 12; ++i) {
        destroy_bitmap(SNAKE1[i]);
    }
}
