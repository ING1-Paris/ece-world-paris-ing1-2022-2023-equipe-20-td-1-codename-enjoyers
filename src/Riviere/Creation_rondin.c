//
// Created by lucie on 12/05/2023.
//


#include "../../header.h"

t_rondin * Creation_rondin(int nb) {

    t_rondin * mon_rondin;

    mon_rondin = (t_rondin *) malloc(sizeof(t_rondin));

    mon_rondin->img = load_bitmap("../assets/Item/Riviere/bois5.bmp", NULL);

    if (!mon_rondin->img) {
        allegro_message("rondin introuvable");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    mon_rondin->tx = mon_rondin->img->w;
    mon_rondin->ty = mon_rondin->img->h;

    mon_rondin->indice_ligne = nb;

    mon_rondin->posx = rand() % (SCREEN_W - mon_rondin->tx);

    if (nb == 0) {

        mon_rondin->posy = 200;

    } else if (nb == 1) {

        mon_rondin->posy = 230;

    } else if (nb == 2) {

        mon_rondin->posy = 260;

    } else if (nb == 3) {

        mon_rondin->posy = 290;

    } else if (nb == 4) {

        mon_rondin->posy = 320;

    } else if (nb == 5) {

        mon_rondin->posy = 350;

    } else if (nb == 6) {

        mon_rondin->posy = 380;

    } else if (nb == 7) {

        mon_rondin->posy = 410;

    } else if (nb == 8) {

        mon_rondin->posy = 440;

    } else if (nb == 9) {

        mon_rondin->posy = 470;

    }else if (nb == 10) {

        mon_rondin->posy = 500;

    }else if (nb == 11) {

        mon_rondin->posy = 530;

    }else if (nb == 12) {

        mon_rondin->posy = 560;

    }else if (nb == 13) {

        mon_rondin->posy = 590;

    }else if (nb == 14) {

        mon_rondin->posy = 620;

    }



    //mon_rondin->depx = ((-1) ^ (rand() % (2-1+1) + 1)) * (rand() % (5-1+1) + 1);
    mon_rondin->depx = pow(-1, rand()%(2-1+1)+1)* (rand() % (5-1+1) + 1);

    mon_rondin->affichage = 1;

    /*for (int i = 0; i < 109; ++i) {
        for (int k = 0; k < 50; ++k) {
            mon_rondin->taille[i][k][0]=mon_rondin->posx+i;
            mon_rondin->taille[i][k][1]=mon_rondin->posy+k;
        }

    }*/

    return mon_rondin;

}



