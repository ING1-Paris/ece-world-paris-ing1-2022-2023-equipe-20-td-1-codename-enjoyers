//
// Created by guych on 06/05/2023.
//

#include "../../header.h"

void update_millis(t_note * note_a_update, int tempo) {

    int temp;
    unsigned long long res;

    temp = note_a_update->millis;

    res = (unsigned long long) temp * (unsigned long long) tempo;

    res = res / TEMPO_DE_BASE;

    note_a_update->millis = (int) res;

}