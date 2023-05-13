//
// Created by lucie on 06/05/2023.
//

#include "../../header.h"

void jeu_taupe(t_joueur joueur_taupe[NOMBRE_JOUEURS]) {

    t_taupe mesTaupes[NOMBRE_TAUPE];
    //t_taupe *mesTaupes;
    t_joueur_taupe monJoueur[NOMBRE_JOUEURS];
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;
    BITMAP *fond;


    page = create_bitmap(SCREEN_W, SCREEN_H);


    decor=load_bitmap("../assets/maps/MAP_TAUPE.bmp",NULL);

    if (!decor)
    {
        allegro_message("decor introuvable");
        exit(EXIT_FAILURE);
    }



    fond = load_bitmap("../assets/Item/Taupe/barbecue.bmp", NULL);

    if (!fond)
    {
        allegro_message("decor introuvable");
        exit(EXIT_FAILURE);
    }




    for (int j = 0; j < NOMBRE_TAUPE; j++) {

        mesTaupes[j].tx = 79;
        mesTaupes[j].ty = 100;

        while ((mesTaupes[j].y == mesTaupes[j + 1].y) || (mesTaupes[j].x == mesTaupes[j + 1].x)) {
            mesTaupes[j].y = rand() % ((634 - 135 + 135) + 135);
            mesTaupes[j].x = rand() % ((852 - 90 + 90) + 90);
        }


        mesTaupes[j].skin = load_bitmap("../assets/Item/Taupe/rat.bmp", NULL);

        if (!mesTaupes[j].skin)
        {
            allegro_message("decor introuvable");
            exit(EXIT_FAILURE);
        }

        mesTaupes[j].affichage = 1;


        for (int i = 0; i < 79; ++i) {
            for (int k = 0; k < 100; ++k) {
                mesTaupes[j].taille[i][k][0] = mesTaupes[j].x + i;
                mesTaupes[j].taille[i][k][1] = mesTaupes[j].y + k;
            }

        }

    }


    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        monJoueur[i].temps = 0;
        monJoueur[i].score = 0;

    }


    blit(fond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Bienvenue sur le JEU TAUPE-LA !", NULL, NULL, "go !", NULL, 0, 0);



    for (int k = 0; k < NOMBRE_JOUEURS; ++k) {

        time_t debut = time(NULL);

        while (monJoueur[k].temps != 5) {

            monJoueur[k].temps = 0;
            monJoueur[k].temps = debut;



            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


            for (int i = 0; i < NOMBRE_TAUPE; i++) {
                if (mouse_b && verfication(mesTaupes[i]) == 1) {
                    printf("TAP !\n");
                    mesTaupes[i].affichage = 0;
                    rest(200);
                    monJoueur[k].score = monJoueur[k].score + 1;

                }

            }


            for (int i = 0; i < NOMBRE_TAUPE; i++) {

                if (mesTaupes[i].affichage == 1) {

                    masked_blit(mesTaupes[i].skin, page, 0, 0, mesTaupes[i].x, mesTaupes[i].y, mesTaupes[i].tx,
                                mesTaupes[i].ty);
                } else {
                    //la taupe ne s'affiche plus
                }
            }


            time_t end = time(NULL);
            monJoueur[k].temps = (unsigned long) difftime(end, debut);


            textprintf_ex(decor, font, 60, 280, makecol(0, 0, 0), makecol(255, 255, 255), "%lu", monJoueur[k].temps);

            textprintf_ex(decor, font, 60, 300, makecol(0, 0, 0), makecol(255, 255, 255), "%4d %4d", mouse_x, mouse_y);



            //J1
            rectfill(page, 10, 10, 250, 70, makecol(255, 255, 255));
            rect(page, 10, 10, 250, 70, makecol(0, 0, 0));
            stretch_blit(joueur_taupe[0].sprites[12], page, 0, 0, 225, 225, 15, 15, 50, 50);

            textprintf_ex(page, font, 70, 30, makecol(0, 0, 0), -1, "%s", joueur_taupe[0].nom);
            textprintf_ex(page, font, 70, 50, makecol(0, 0, 0), -1, "score: %d", monJoueur[0].score);

            //J2
            rectfill(page, SCREEN_W - 250, 10, SCREEN_W - 10, 70, makecol(255, 255, 255));
            rect(page, SCREEN_W - 250, 10, SCREEN_W - 10, 70, makecol(0, 0, 0));
            stretch_blit(joueur_taupe[1].sprites[12], page, 0, 0, 225, 225, SCREEN_W - 250 + 5, 15, 50, 50);


            textprintf_ex(page, font, SCREEN_W - 250 + 5 + 55, 30, makecol(0, 0, 0), -1, "%s", joueur_taupe[1].nom);
            textprintf_ex(page, font, SCREEN_W - 250 + 5 + 55, 50, makecol(0, 0, 0), -1, "score: %d", monJoueur[1].score);


            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        }

    }


    if (joueur_taupe[0].score > joueur_taupe[1].score) {

        alert("Joueur 1, vous avez gagné un ticket ! ", NULL, NULL, "go!", NULL, 0, 0);
        joueur_taupe[0].tickets = joueur_taupe[0].tickets + 1;
    } else {

        alert("Joueur 2, vous avez gagné un ticket ! ", NULL, NULL, "go !", NULL, 0, 0);
        joueur_taupe[0].tickets = joueur_taupe[0].tickets + 1;

    }

}
