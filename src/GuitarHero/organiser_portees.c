//
// Created by guych on 05/05/2023.
//

#include "../../header.h"

t_note * organiser_portees(t_note * tab_notes, int taille_tab_notes, int * taille_portee, int portee) {

    int compteur_de_notes = 0;
    int index_remplissage = 0;
    int validation_de_decoupe = 0;

    int i;

    //Comptage des differentes notes dans la portée 1
    while (validation_de_decoupe != 1 && compteur_de_notes < taille_tab_notes) {

        if (tab_notes[compteur_de_notes].portee == 2) {

            validation_de_decoupe = 1;

        } else {

            compteur_de_notes = compteur_de_notes + 1;
        }
    }



    //Remplissage des nouveaux tableaux pour chaque partition
    if (portee == 1) {

        t_note * tab1 = malloc( (compteur_de_notes) * sizeof (t_note));

        for (i=0; i<compteur_de_notes; i++) {

            tab1[i] = tab_notes[i];
        }

        *taille_portee = compteur_de_notes;

        return tab1;

    } else if (portee == 2) {

        t_note * tab2 = malloc( (taille_tab_notes - compteur_de_notes) * sizeof (t_note));


        for (i=compteur_de_notes; i<taille_tab_notes; i++) {

            tab2[index_remplissage] = tab_notes[i];

            index_remplissage = index_remplissage + 1;
        }

        *taille_portee = index_remplissage;

        return tab2;

    }


}