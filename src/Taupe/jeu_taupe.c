//
// Created by lucie on 06/05/2023.
//

#include "../../header.h"

void jeu_taupe(t_joueur joueur_taupe[NOMBRE_JOUEURS], unsigned long* Temps) {

    //t_taupe *mesTaupes[NRONDIN];
    t_taupe *mesTaupes[NOMBRE_TAUPE];
    t_joueur_taupe *monJoueur[NOMBRE_JOUEURS];
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;
    int score[NOMBRE_JOUEURS] = {0,0};

    unsigned long temps[NOMBRE_JOUEURS];
    int fin  = 0;


    page = create_bitmap(SCREEN_W, SCREEN_H);

    decor = load_bitmap_check("../assets/maps/MAP_RIVIERE.bmp");


    for (int j = 0; j < NOMBRE_TAUPE; j++) {


        mesTaupes[j] = (t_taupe *) malloc(sizeof(t_taupe));

        //mesTaupes[j]->skin_utilise = 6;
       // mesTaupes[j]->vit = 5;
        mesTaupes[j]->tx = 48;
        mesTaupes[j]->ty = 48;
        mesTaupes[j]->y = 0;
        mesTaupes[j]->x = 500;
        mesTaupes[j]->skin = load_bitmap_check("../assets/Item/Riviere/bois1.bmp");

    }


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        monJoueur[i]->temps = 0;
        //monJoueur[i]->score = 0;
    }

    blit(decor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Bienvenue sur TAUPE-LA !", NULL, NULL, "go !", NULL, 0, 0);


    rectfill(decor,0,0,40,20,makecol(0,128,0 ));
    textprintf_ex(decor,font,4,6,makecol(255,0,0),makecol(0,255,0),"EXIT");


    //time_t debut = time(NULL);

    for (int j = 0; j < NOMBRE_JOUEURS; ++j) {

        //monJoueur[j]->temps = debut;


        while(!fin){


            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


            for (int i = 0; i < NOMBRE_TAUPE; ++i) {
                masked_blit(mesTaupes[i]->skin,page,0,0,mesTaupes[i]->x,mesTaupes[i]->y,mesTaupes[i]->tx,mesTaupes[i]->ty);
            }


            for (int i = 0; i < NOMBRE_TAUPE; ++i) {
                // les clics
                if (mouse_b){ // gauche : dessiner en rouge
                    rectfill(decor, mouse_x, mouse_y, mouse_x+20, mouse_y+20, makecol(255,0,0));
                    //clear(mesTaupes[i]->skin);
                    //clear_bitmap(mesTaupes[i]->skin);

                    /*score[j]= score[j]+1;
                    monJoueur[j]->score = score[j];*/
                }

            }


            // clip sur EXIT :
            if ( mouse_b&1 && mouse_x<=40 && mouse_y<=20)
                fin=1;


            //time_t end = time(NULL);
            //monJoueur[j]->temps = (unsigned long) difftime(end, debut);


            textprintf_ex(decor,font,60,280,makecol(0,0,0), makecol(255,255,255),"%lu",monJoueur[j]->temps);
            textprintf_ex(decor,font,60,300,makecol(0,0,0),-1,"%4d %4d",mouse_x,mouse_y);



            //J1
            rectfill(page,10,10,250,70,makecol(255,255,255));
            rect(page,10,10,250,70,makecol(0,0,0));
            stretch_blit(joueur_taupe[0].sprites[12],page,0,0,225,225,15,15,50,50);

            textprintf_ex(page,font,70, 30, makecol(0,0,0),-1,"%s",joueur_taupe[0].nom);
            textprintf_ex(page,font,70, 50, makecol(0,0,0),-1,"score: %d",monJoueur[0]->score);

            //J2
            rectfill(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(255,255,255));
            rect(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(0,0,0));
            stretch_blit(joueur_taupe[1].sprites[12],page,0,0,225,225,SCREEN_W-250+5,15,50,50);


            textprintf_ex(page,font,SCREEN_W-250+5+55, 30, makecol(0,0,0),-1,"%s",joueur_taupe[1].nom);
            textprintf_ex(page,font,SCREEN_W-250+5+55, 50, makecol(0,0,0),-1,"score: %d",monJoueur[1]->score);

            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


        }

    }

    if(monJoueur[0]->score < monJoueur[1]->score)

        //alert("%s, vous avez gagné un ticket ! "joueur_riv[0].nom, NULL, NULL, "go!", NULL, 0, 0);

        allegro_message("%s, vous avez gagné un ticket !",joueur_taupe[0].nom);

    else
        //alert("%d, vous avez gagné un ticket ! ",joueur_riv[1].nom, NULL, NULL, "go !", NULL, 0, 0);


        allegro_message("%s, vous avez gagné un ticket !",joueur_taupe[1].nom);

    // allegro_message("Joueur 2, vous avez gagné un ticket !");


}