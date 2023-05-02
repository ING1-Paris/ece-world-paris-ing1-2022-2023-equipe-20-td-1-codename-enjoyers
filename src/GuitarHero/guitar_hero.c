//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

void guitar_hero() {

    char chansons[10][256] = {

            "la marseillaise",
            "running in the 90",
            "helicopter helicopter"
    };





    DIALOG GUI_guitar_hero[] =
            {
                    // (dialog proc)     (x)   (y)   (w)   (h) (fg)(bg) (key) (flags)     (d1) (d2)    (dp)                   (dp2) (dp3)
                    { d_box_proc,           0, 0, 500, 200, 0, 0, 0,        0,          0,  0,       NULL,               NULL, NULL},
                    { d_text_proc,         2,  10,    0,    0,   0,  0,    0,      0,       0,   0,    (void*)"Selectionner la musique a jouer:",  NULL, NULL  },

                    { d_list_proc, 64, 80, 50, 50, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},


                    { d_button_proc,     160,   190,  160,   16,   0,  0,    0, D_EXIT,       0,   0,    (void*)"OK",            NULL, NULL  },
                    { d_yield_proc,        0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
                    { NULL,                0,   0,    0,    0,   0,  0,    0,      0,       0,   0,    NULL,                   NULL, NULL  },
            };

    gui_fg_color = makecol(0, 0, 0);
    gui_mg_color = -1;
    gui_bg_color = makecol(255, 255, 255);
    set_dialog_color (GUI_guitar_hero, gui_fg_color, gui_bg_color);
    centre_dialog(GUI_guitar_hero);

    GUI_guitar_hero[2].dp = chansons;

    do_dialog(GUI_guitar_hero, 3);
}