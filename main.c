#include "header.h"

int main() {

    srand(time(NULL));

    allegro_init();

    install_keyboard();
    install_mouse();

    set_window_title("SHREK MANIA WORLD");


    // CREATION DU MODE GRAPHIQUE
    // -----------------------------
    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,960,720,0,0) != 0) {

        allegro_message("Probleme de mode graphique :/");

        allegro_exit();
        exit(EXIT_FAILURE);
    }
    // -----------------------------


    // INITIALISER LES VARIABLES ICI
    // -----------------------------

    // BITMAPS
    BITMAP * page; // BITMAP de la page (double buffer)
    BITMAP * menu;

    // JOUEURS
    t_joueur tableau_joueurs[NOMBRE_JOUEURS];


    // OUVERTURE DE LA BOITE DE DIALOGUE
    char chaine_temp[64] = "";

    DIALOG GUI_demarrage[] =
        {
                    // (dialog proc)     (x)   (y)   (w)   (h) (fg)(bg) (key) (flags)     (d1) (d2)    (dp)                   (dp2) (dp3)
            { d_box_proc,           0, 0, 500, 200, 0, 0, 0,        0,          0,  0,       NULL,               NULL, NULL},
            { d_text_proc,         2,  10,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Saisir le pseudo du joueur:",  NULL, NULL  },
            { d_text_proc,         4,  20,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)">>",  NULL, NULL  },
            { d_edit_proc,       28,  20,  160,    8,   0,  0,    0, D_EXIT,      64,   0,    (void*)chaine_temp,      NULL, NULL  },
            { d_icon_proc, }
            { d_button_proc,     160,   190,  160,   16,   0,  0,    0, D_EXIT,       0,   0,    (void*)"OK",            NULL, NULL  },
            { d_yield_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
            { NULL,                0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
        };

    gui_fg_color = makecol(0, 0, 0);
    gui_mg_color = -1;
    gui_bg_color = makecol(255, 255, 255);
    set_dialog_color (GUI_demarrage, gui_fg_color, gui_bg_color);
    centre_dialog(GUI_demarrage);

    // -----------------------------





    // CHARGEMENT DES VARIABLES
    // -----------------------------

    menu = load_bitmap("../assets/maps/menu.bmp", NULL);

    // -----------------------------





    // DEBUT DU JEU
    page = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(page);

    alert("Bienvenue sur SHREK MANIA WORLD !", NULL, NULL, "Suivant", NULL, 0, 0);

    for (int i=0; i<NOMBRE_JOUEURS; i++) {

        strcpy(chaine_temp, "");

        blit(menu, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (i == 0) {

            alert("Remplissez les informations du joueur 1 !", NULL, NULL, "Suivant", NULL, 0, 0);

        }

        do_dialog(GUI_demarrage, 3);

        strcpy(tableau_joueurs[i].nom, chaine_temp);
        tableau_joueurs[i].score = 0;


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
