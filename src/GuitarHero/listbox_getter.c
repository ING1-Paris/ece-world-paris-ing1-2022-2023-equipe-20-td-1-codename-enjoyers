//
// Created by guych on 02/05/2023.
//

#include "../../header.h"

char *listbox_getter(int index, int *list_size) {

    static char *strings[] =
            {
                    "Pirates des Caraibes (intermediaire)",  "Megalovania (difficile)", "Cupid (facile)"
            };

    if (index < 0) {
        *list_size = TAILLE_TAB_CHANSONS;
        return NULL;
    }
    else {
        return strings[index];
    }
}