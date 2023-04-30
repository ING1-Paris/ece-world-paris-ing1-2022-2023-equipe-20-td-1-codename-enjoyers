#include "header.h"

int main() {

    srand(time(NULL));

    allegro_init();

    install_keyboard();
    install_mouse();

    set_window_title("SHREK MANIA WORLD");


    /// CREATION DU MODE GRAPHIQUE
    // -----------------------------
    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,960,720,0,0) != 0) {

        allegro_message("Probleme de mode graphique :/");

        allegro_exit();
        exit(EXIT_FAILURE);
    }
    /// -----------------------------


    /// INITIALISER LES VARIABLES ICI
    // -----------------------------

    // BITMAPS
    BITMAP * page; // BITMAP de la page (double buffer)
    BITMAP * menu;

    // JOUEURS
    t_joueur tableau_joueurs[NOMBRE_JOUEURS];


    // OUVERTURE DE LA BOITE DE DIALOGUE
    char chaine_temp[256] = "";

    DIALOG GUI_demarrage[] =
        {
                    // (dialog proc)     (x)   (y)   (w)   (h) (fg)(bg) (key) (flags)     (d1) (d2)    (dp)                   (dp2) (dp3)
            { d_box_proc,           0, 0, 500, 200, 0, 0, 0,        0,          0,  0,       NULL,               NULL, NULL},
            { d_text_proc,         2,  10,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Saisir le pseudo du joueur:",  NULL, NULL  },
            { d_text_proc,         4,  25,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)">>",  NULL, NULL  },
            { d_edit_proc,       28,  25,  160,    8,   0,  0,    0, D_EXIT,      64,   0,    (void*)chaine_temp,      NULL, NULL  },
            { d_text_proc,         2,  65,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Choisir le personnage:",  NULL, NULL  },

            { d_icon_proc,       4,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL,                   NULL, NULL  },
            { d_icon_proc,       64,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL,                   NULL, NULL  },
            { d_icon_proc,       124,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL,                   NULL, NULL  },
            { d_icon_proc,       184,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL,                   NULL, NULL  },
            { d_icon_proc,       244,  80,   50,   50,   0,  0,    0,      0,       6,   0,    NULL,                   NULL, NULL  },


            { d_button_proc,     160,   190,  160,   16,   0,  0,    0, D_EXIT,       0,   0,    (void*)"OK",            NULL, NULL  },
            { d_yield_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
            { NULL,                0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
        };

    gui_fg_color = makecol(0, 0, 0);
    gui_mg_color = -1;
    gui_bg_color = makecol(255, 255, 255);
    set_dialog_color (GUI_demarrage, gui_fg_color, gui_bg_color);
    centre_dialog(GUI_demarrage);

    /// -----------------------------





    /// CHARGEMENT DES VARIABLES
    // -----------------------------

    menu = load_bitmap("../assets/maps/menu.bmp", NULL);

    /// -----------------------------





    /// DEBUT DU JEU
    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    GUI_demarrage[5].dp = load_bitmap("../assets/personnages/farquaad/farquaad.bmp", NULL);
    GUI_demarrage[6].dp = load_bitmap("../assets/personnages/shrek/shrek_photo.bmp", NULL);
    GUI_demarrage[7].dp = load_bitmap("../assets/personnages/Chat/chat_potte.bmp", NULL);
    GUI_demarrage[8].dp = load_bitmap("../assets/personnages/fiona/fiona.bmp", NULL);
    GUI_demarrage[9].dp = load_bitmap("../assets/personnages/thomas/thomas.bmp", NULL);



    alert("Bienvenue sur SHREK MANIA WORLD !", NULL, NULL, "Suivant", NULL, 0, 0);

    for (int i=0; i<NOMBRE_JOUEURS; i++) {

        strcpy(chaine_temp, "");

        for (int j=5; j<10; j++) {

            if (GUI_demarrage[j].flags != D_HIDDEN) {

                GUI_demarrage[j].flags = 0;
            }
        }

        blit(menu, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (i == 0) {

            alert("Remplissez les informations du joueur 1 !", NULL, NULL, "Suivant", NULL, 0, 0);

        }

        do {

            do_dialog(GUI_demarrage, 3);

        } while (strlen(chaine_temp) < 1);


        strcpy(tableau_joueurs[i].nom, chaine_temp);
        tableau_joueurs[i].score = 0;
        tableau_joueurs[i].dx = 10;
        tableau_joueurs[i].dy = 10;

        // Remplir le tableau de sprites de chaque joueur en fonction du perso qu'il a choisi
        if (GUI_demarrage[5].flags == D_SELECTED) { // Farquaad

            GUI_demarrage[5].flags = D_HIDDEN;

            tableau_joueurs[i].sprites[0] = load_bitmap("../assets/personnages/farquaad/farquaad_immobile_avant_0.bmp", NULL);
            tableau_joueurs[i].sprites[1] = load_bitmap("../assets/personnages/farquaad/farquaad_immobile_derriere_0", NULL);
            tableau_joueurs[i].sprites[2] = load_bitmap("../assets/personnages/farquaad/farquaad_immobile_droite_0.bmp", NULL);
            tableau_joueurs[i].sprites[3] = load_bitmap("../assets/personnages/farquaad/farquaad_immobile_gauche_0.bmp", NULL);
            tableau_joueurs[i].sprites[4] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_avant_0.bmp", NULL);
            tableau_joueurs[i].sprites[5] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_avant_1.bmp", NULL);
            tableau_joueurs[i].sprites[6] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_derriere_0.bmp", NULL);
            tableau_joueurs[i].sprites[7] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_derriere_1.bmp", NULL);
            tableau_joueurs[i].sprites[8] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_droite_0.bmp", NULL);
            tableau_joueurs[i].sprites[9] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_droite_1.bmp", NULL);
            tableau_joueurs[i].sprites[10] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_gauche_0.bmp", NULL);
            tableau_joueurs[i].sprites[11] = load_bitmap("../assets/personnages/farquaad/farquaad_marche_gauche_1.bmp", NULL);


        } else if (GUI_demarrage[6].flags == D_SELECTED) { //Shrek

            GUI_demarrage[6].flags = D_HIDDEN;


        } else if (GUI_demarrage[7].flags == D_SELECTED) { // Le chat potté

            GUI_demarrage[7].flags = D_HIDDEN;



        } else if (GUI_demarrage[8].flags == D_SELECTED) { // Fiona

            GUI_demarrage[8].flags = D_HIDDEN;

        } else if (GUI_demarrage[9].flags == D_SELECTED) { // Thomas

            GUI_demarrage[9].flags = D_HIDDEN;
        }

        tableau_joueurs[i].x = 300 + (20 * i); // Valeurs à changer
        tableau_joueurs[i].y = 300 + (20 * i); // Valeurs à changer
        tableau_joueurs[i].tx = tableau_joueurs[i].sprites[0]->w;
        tableau_joueurs[i].ty = tableau_joueurs[i].sprites[0]->h;


        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (i == 0) {

            alert("Remplissez a present les informations du joueur 2 !", NULL, NULL, "Suivant", NULL, 0, 0);
        }


    }

    while (!readkey()) {

        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }



    destroy_bitmap(page);
    destroy_bitmap(menu);

    allegro_exit();

    return 0;

} END_OF_MAIN()