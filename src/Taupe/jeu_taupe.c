//
// Created by lucie on 06/05/2023.
//

#include "../../header.h"

void jeu_taupe(t_joueur joueur_taupe[NOMBRE_JOUEURS]) {

    t_taupe mesTaupes[NOMBRE_TAUPE];
    t_joueur_taupe monJoueur[NOMBRE_JOUEURS];
    BITMAP *page;        // BITMAP buffer d'affichage
    BITMAP *decor;
    BITMAP *fond;


    page = create_bitmap(SCREEN_W, SCREEN_H);

    decor = load_bitmap("../assets/maps/MAP_TAUPE.bmp",NULL);

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




    //Initialisation des joueurs
    for (int i = 0; i < NOMBRE_JOUEURS; ++i) {

        monJoueur[i].temps = 0;
        monJoueur[i].score = 0;

    }


    blit(fond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    alert("Bienvenue sur le JEU TAUPE-LA !", NULL, NULL, "go !", NULL, 0, 0);



    for (int k = 0; k < NOMBRE_JOUEURS; ++k) {


        //Initialisation des taupes
        for (int j = 0; j < NOMBRE_TAUPE; ++j) {

            mesTaupes[j].skin = load_bitmap("../assets/Item/Taupe/rat.bmp", NULL);

            if (!mesTaupes[j].skin)
            {
                allegro_message("decor introuvable");
                allegro_exit();
                exit(EXIT_FAILURE);
            }

            mesTaupes[j].tx = mesTaupes[j].skin->w;
            mesTaupes[j].ty = mesTaupes[j].skin->h;


            //mesTaupes[j].y = rand() % (((500 - mesTaupes[j].ty) - 200 + 1) + 200);
            //mesTaupes[j].x = rand() % (((800 - mesTaupes[j].tx) - 200 + 1) + 200);


            mesTaupes[j].y = 200 + 8*j;
            mesTaupes[j].x = 300 + 8*j;

            mesTaupes[j].affichage = 1;

            for (int i = 0; i < 79; ++i) {
                for (int m = 0; m < 100; ++m) {
                    mesTaupes[j].taille[i][m][0] = mesTaupes[j].x + i;
                    mesTaupes[j].taille[i][m][1] = mesTaupes[j].y + m;
                }

            }
        }


        alert("Tenez-vous prêt...", NULL, "Vous avez 5 secondes pour éliminer le plus de rat,", "C'est parti !", NULL, 0, 0);


        time_t debut = time(NULL);


        // début du jeu
        while (monJoueur[k].temps != 5) {

            monJoueur[k].temps = 0;
            monJoueur[k].temps = debut;



            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);


            //Condition d'affichage des taupes
            for (int i = 0; i < NOMBRE_TAUPE; i++) {
                if (mouse_b && verfication(mesTaupes[i]) == 1) {
                    printf("TAP !\n");
                    mesTaupes[i].affichage = 0;
                    rest(200);
                    joueur_taupe[k].score = joueur_taupe[k].score + 1;

                }

            }

            for (int i = 0; i < NOMBRE_TAUPE; i++) {

                if (mesTaupes[i].affichage == 1) {

                    masked_blit(mesTaupes[i].skin, page, 0, 0, mesTaupes[i].x, mesTaupes[i].y, mesTaupes[i].tx,mesTaupes[i].ty);
                } else {
                    //la taupe ne s'affiche plus
                }
            }


            //Gestion chrono
            time_t end = time(NULL);
            monJoueur[k].temps = (unsigned long) difftime(end, debut);


            //Affichage score et temps des joueurs
            rectfill(page, 10, 10, 250, 90, makecol(255, 255, 255));
            rect(page, 10, 10, 250, 90, makecol(0, 0, 0));
            stretch_blit(joueur_taupe[k].sprites[12], page, 0, 0, 225, 225, 15, 15, 70, 70);

            textprintf_ex(page, font, 90, 20, makecol(0, 0, 0), -1, "%s", joueur_taupe[k].nom);
            textprintf_ex(page, font, 90, 50, makecol(0, 0, 0), -1, "score: %d", joueur_taupe[k].score);
            textprintf_ex(page, font, 90, 70, makecol(0, 0, 0), -1, "temps écoulé: %lu", monJoueur[k].temps);


            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        }

    }


    //Gestion des tickets
    if (monJoueur[0].score > monJoueur[1].score) {

        alert("Joueur 1, vous avez gagné un ticket ! ", NULL, NULL, "go!", NULL, 0, 0);
        joueur_taupe[0].tickets = joueur_taupe[0].tickets + 1;

    } else if (monJoueur[0].score < monJoueur[1].score) {

        alert("Joueur 2, vous avez gagné un ticket ! ", NULL, NULL, "go !", NULL, 0, 0);
        joueur_taupe[1].tickets = joueur_taupe[1].tickets + 1;

    } else {

        alert("Egalité ! ", NULL, NULL, "go !", NULL, 0, 0);
    }

}
