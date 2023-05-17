//
// Created by Leroy on 17/05/2023.
//
#include "../../header.h"




void statistique() {

    /* for the d_text_box_proc object */
    char affichage_scores[] =
            "Selectionnez un jeu ou une categorie pour en voir les meilleurs scores !";



    MENU Map[] =
            {       //(text)                   (fonction)             (Child)(flags) (NULL)
                    { "Map :"                ,                  NULL,   NULL,    0,  NULL  },
                    { ""                     ,                  NULL,   NULL,    0,  NULL  },
                    { "Cupid"                ,  (void*)menu_callback,   NULL,    0,  NULL  },
                    { "Megalovania"          ,  (void*)menu_callback,   NULL,    0,  NULL  },
                    { "Pirates des Caraibes" ,  (void*)menu_callback,   NULL,    0,  NULL  },
                    { NULL                   ,                  NULL,   NULL,    0,  NULL  }
            };


    MENU the_menu[] =
            {      //(text)                     (fonction)             (Child)(flags)(NULL)
                    {"Snake d'epices"         , (void*) menu_callback,  NULL   , 0, NULL},
                    {"Guitare Hero "          , NULL                 ,  Map    , 0, NULL},
                    {"Explose Ballons"        , (void*)menu_callback ,  NULL   , 0, NULL},
                    {"Course de Lapin"        , (void*)menu_callback ,  NULL   , 0, NULL},
                    {"Deratisation"           , (void*)menu_callback ,  NULL   , 0, NULL},
                    {"La traversee de la mort", (void*)menu_callback ,  NULL   , 0, NULL},
                    {NULL                     , NULL                 ,  NULL   , 0, NULL}
            };


    DIALOG Menu_score[] = {
    //                    (dialog proc)     (x)  (y)  (w)  (h) (fg)(bg)(key)  (flags)    (d1)(d2)(dp)                        (dp2) (dp3)
                           {d_box_proc,     48, 292, 853, 263,   0, 0,   0,          0,    0, 0, NULL,                       NULL, NULL},
                           {d_box_proc,    410, 288, 130,  12,   0, 0,   0,          0,    0, 0, NULL,                       NULL, NULL},
                           {d_text_proc,   420, 290,   0,   0,   0, 0,   0,          0,    0, 0, (void *) "Statistiques :",  NULL, NULL},
                           {d_text_proc,    60, 320,   0,   0,   0, 0,   0,          0,    0, 0, (void *) "Jeux :",          NULL, NULL},
                           {d_menu_proc,    55, 330, 842,  10,   0, 0,   0,          0,    0, 0, the_menu,                   NULL, NULL},
                           {d_yield_proc,    0,   0,   0,   0,   0, 0,   0,          0,    0, 0, NULL,                       NULL, NULL},
                           {d_textbox_proc, 55, 350, 842, 200,   0, 0,   0,          0,    0, 0, (void*) affichage_scores ,  NULL, NULL},
                           {d_button_proc, 410, 550, 130, 12 ,   0, 0,   0,          D_EXIT,    0, 0, (void* ) "Retour" ,         NULL, NULL},
                           {NULL,            0,   0,   0,   0,   0, 0,   0,          0,    0, 0, NULL,                       NULL, NULL}
    };

    set_dialog_color(Menu_score, gui_fg_color, gui_bg_color);
    centre_dialog(Menu_score);

    position_dialog(Menu_score, 2, 2);

    int alive = 1;

    BITMAP * test = create_bitmap(SCREEN_W, SCREEN_H);

    clear_to_color(test, makecol(255, 0, 0));

    while (alive) {

        do_dialog(Menu_score, 3);

        if (alert("Quitter", NULL, NULL, "Au revoir !", NULL, 0, 0)) {

            allegro_exit();
            exit(0);
        }

    }








}