
#include "../../header.h"



/******************************************/
/*          PROGRAMME PRINCIPAL           */
/******************************************/

void jeu_riviere(t_joueur joueur_riv[NOMBRE_JOUEURS], unsigned long* Temps) {

    t_rondin *mesRondins[NRONDIN];
    t_joueuur *joueur[NOMBRE_JOUEURS];
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;

    int inactivite[NOMBRE_JOUEURS] = {1,1};
    int animation_perso_riv[NOMBRE_JOUEURS] = {1,1};

    page = create_bitmap(SCREEN_W, SCREEN_H);

    remplirTabRondin(mesRondins);

    decor = load_bitmap_check("../assets/maps/MAP_RIVIERE.bmp");



    for (int j = 0; j < NOMBRE_JOUEURS; j++) {

        //Debut du chronometre
        time_t temps_precedent = time(NULL);

        //joueur[j] = creationJoueur(perso);

        joueur[j] = (t_joueuur *) malloc(sizeof(t_joueur));

        joueur[j]->skin_utilise = 6;
        joueur[j]->vit = 5;
        joueur[j]->tx = 48;
        joueur[j]->ty = 48;
        joueur[j]->y = 0;
        joueur[j]->x = 500;
        joueur[j]->temps = 0;

        for (int i = 0; i < 12; ++i) {
            joueur[j]->skin_perso[i] = joueur_riv[j].sprites[i];
        }

    }


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
        joueur[i]->skin_utilise=6;
    }


    blit(decor, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Bienvenue sur le JEU DE LA RIVIERE !", NULL, NULL, "go !", NULL, 0, 0);



    time_t begin = time(NULL);


    for (int j = 0; j < NOMBRE_JOUEURS; ++j) {

        /*do {
            joueur[j]->y = joueur[j]->y + joueur[j]->vit;

        }while(joueur[j]->y<280);*/

        joueur[j]->temps = begin;

        while (joueur[j]->y <= 580) {


            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            AfficherTabRondin(page, mesRondins);
            actualiserTabRondin(mesRondins);

            //AfficherJoueur(joueur[j], page, animation_perso_riv[j]);


            textprintf_centre_ex(decor, font, 400, 570, makecol(255, 255, 255), 0, "%d", joueur[j]->y);

            for (int i = 0; i < NOMBRE_JOUEURS; ++i) {
                inactivite[i]=1;
            }

            deplacement_joueurs_riv(page, &joueur[j], &inactivite[j],&mesRondins[j]);


                for (int i=0; i<NOMBRE_JOUEURS; i++) {

                    //On verifie si le personnage est innactif ou non
                    if (inactivite[i] == 1){

                        joueur[i]->skin_utilise = joueur[i]->skin_utilise +2;
                        animation_perso_riv[i] = 0;

                    }
                    else{

                        if (animation_perso_riv[i] == 0)
                            animation_perso_riv[i] = 1;
                        else {
                            animation_perso_riv[i] = 0;
                        }
                    }

                    //Affichage du joueur
                    //masked_blit(joueur_a_afficher->skin_perso[joueur_a_afficher->skin_utilise + animation],bmp,0,0,joueur_a_afficher->x,joueur_a_afficher->y,joueur_a_afficher->tx,joueur_a_afficher->ty);
                    //ActualiserJoueur(decor, joueur[i], mesRondins, animation_perso_riv[i]);

                    masked_blit(joueur[i]->skin_perso[joueur[i]->skin_utilise+animation_perso_riv[i]],page,0,0,joueur[i]->x,joueur[i]->y,joueur[i]->tx,joueur[i]->ty);


                    //On enleve le sprite d'inactivite
                    if (inactivite[i] == 1)
                        joueur[i]->skin_utilise = joueur[i]->skin_utilise - 2;

                }


            time_t temps_actuel = time(NULL);

            joueur[j]->temps = (unsigned long) difftime(temps_actuel, begin);



            //J1
            rectfill(page,10,10,250,70,makecol(255,255,255));
            rect(page,10,10,250,70,makecol(0,0,0));
            stretch_blit(joueur_riv[0].sprites[12],page,0,0,225,225,15,15,50,50);

            textprintf_ex(page,font,70, 30, makecol(0,0,0),-1,"%s",joueur_riv[0].nom);
            textprintf_ex(page,font,70, 50, makecol(0,0,0),-1,"temps: %lu",joueur[0]->temps);

            //J2
            rectfill(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(255,255,255));
            rect(page,SCREEN_W-250,10,SCREEN_W-10,70,makecol(0,0,0));
            stretch_blit(joueur_riv[1].sprites[12],page,0,0,225,225,SCREEN_W-250+5,15,50,50);


            textprintf_ex(page,font,SCREEN_W-250+5+55, 30, makecol(0,0,0),-1,"%s",joueur_riv[1].nom);
            textprintf_ex(page,font,SCREEN_W-250+5+55, 50, makecol(0,0,0),-1,"temps: %lu",joueur[1]->temps);

            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


            rest(15);



        }


    }

    if(joueur[0]->temps < joueur[1]->temps)

        //alert("%s, vous avez gagné un ticket ! "joueur_riv[0].nom, NULL, NULL, "go!", NULL, 0, 0);

        allegro_message("%s, vous avez gagné un ticket !",joueur_riv[0].nom);

    else
        //alert("%d, vous avez gagné un ticket ! ",joueur_riv[1].nom, NULL, NULL, "go !", NULL, 0, 0);


        allegro_message("%s, vous avez gagné un ticket !",joueur_riv[1].nom);

   // allegro_message("Joueur 2, vous avez gagné un ticket !");


    time_t end = time(NULL);
    *Temps = (unsigned long) difftime(end,begin);


}

