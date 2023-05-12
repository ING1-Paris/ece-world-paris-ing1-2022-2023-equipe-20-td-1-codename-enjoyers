//
// Created by lucie on 11/05/2023->
//

#include "../../header.h"

t_rondin * Creation_rondin(int nb) {

    t_rondin * mon_rondin;

    mon_rondin = (t_rondin *) malloc(sizeof(t_rondin));

    mon_rondin->img = load_bitmap("../assets/Item/Riviere/bois1.bmp", NULL);

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

        mon_rondin->posy = 180;

    } else if (nb == 1) {

        mon_rondin->posy = 210;

    } else if (nb == 2) {

        mon_rondin->posy = 240;

    } else if (nb == 3) {

        mon_rondin->posy = 270;

    } else if (nb == 4) {

        mon_rondin->posy = 300;

    } else if (nb == 5) {

        mon_rondin->posy = 330;

    } else if (nb == 6) {

        mon_rondin->posy = 360;

    } else if (nb == 7) {

        mon_rondin->posy = 390;

    } else if (nb == 8) {

        mon_rondin->posy = 420;

    } else if (nb == 9) {

        mon_rondin->posy = 450;

    }else if (nb == 10) {

        mon_rondin->posy = 480;

    }else if (nb == 11) {

        mon_rondin->posy = 510;

    }else if (nb == 12) {

        mon_rondin->posy = 540;

    }else if (nb == 13) {

        mon_rondin->posy = 570;

    }else if (nb == 14) {

        mon_rondin->posy = 600;

    }else if (nb == 15) {

        mon_rondin->posy = 630;

    }



    //mon_rondin->depx = ((-1) ^ (rand() % (2-1+1) + 1)) * (rand() % (5-1+1) + 1);
    mon_rondin->depx = pow(-1, rand()%(2-1+1)+1)* (rand() % (5-1+1) + 1);




    /*for (int i = 0; i < 109; ++i) {
        for (int k = 0; k < 50; ++k) {
            mon_rondin->taille[i][k][0]=mon_rondin->posx+i;
            mon_rondin->taille[i][k][1]=mon_rondin->posy+k;
        }

    }*/

    return mon_rondin;

}



