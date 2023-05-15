//
// Created by thais on 15/05/2023.
//
#include "../../header.h"

/// Gérer les collisions (éventuelles) entre un acteur (un tir du joueur) et un ballon

void collisionActeurBleu(t_ballon *ballon_bleu,t_acteur *acteur){
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // s'il est dans le ballon alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre ballon
        vx = acteur->x+acteur->tx/2 - (ballon_bleu->x+ballon_bleu->tx/2);
        vy = acteur->y+acteur->ty/2 - (ballon_bleu->y+ballon_bleu->ty/2);


        // calcul distance au carré au centre du ballon (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ballon_bleu->tx * ballon_bleu->tx / 4 ){
            destinActeur(acteur);
            ballon_bleu->dy = ballon_bleu->dy - 15 ;
        }
    }
}

void collisionActeurRose(t_ballon *ballon_rose,t_acteur *acteur){
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // s'il est dans le ballon alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre ballon
        vx = acteur->x+acteur->tx/2 - (ballon_rose->x+ballon_rose->tx/2);
        vy = acteur->y+acteur->ty/2 - (ballon_rose->y+ballon_rose->ty/2);


        // calcul distance au carré au centre de la ballon (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ballon_rose->tx * ballon_rose->tx / 4 ) {
            destinActeur(acteur);
            ballon_rose->dy = ballon_rose->dy - 15 ;
        }
    }
}

void collisionActeurVert(t_ballon *ballon_vert,t_acteur *acteur){
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // s'il est dans le ballon alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre ballon
        vx = acteur->x+acteur->tx/2 - (ballon_vert->x+ballon_vert->tx/2);
        vy = acteur->y+acteur->ty/2 - (ballon_vert->y+ballon_vert->ty/2);


        // calcul distance au carré au centre de la ballon (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ballon_vert->tx * ballon_vert->tx / 4 ) {
            destinActeur(acteur);
            ballon_vert->dy = ballon_vert->dy - 15;
        }
    }
}

void collisionActeurViolet(t_ballon *ballon_violet,t_acteur *acteur){
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // s'il est dans le ballon alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre ballon
        vx = acteur->x+acteur->tx/2 - (ballon_violet->x+ballon_violet->tx/2);
        vy = acteur->y+acteur->ty/2 - (ballon_violet->y+ballon_violet->ty/2);


        // calcul distance au carré au centre de la ballon (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ballon_violet->tx * ballon_violet->tx / 4 ) {
            destinActeur(acteur);
            ballon_violet->dy = ballon_violet->dy - 15;
        }
    }
}

void collisionActeurRouge(t_ballon *ballon_rouge,t_acteur *acteur){
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // s'il est dans le ballon alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre ballon
        vx = acteur->x+acteur->tx/2 - (ballon_rouge->x+ballon_rouge->tx/2);
        vy = acteur->y+acteur->ty/2 - (ballon_rouge->y+ballon_rouge->ty/2);


        // calcul distance au carré au centre de la ballon (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ballon_rouge->tx * ballon_rouge->tx / 4 ) {
            destinActeur(acteur);
            ballon_rouge->dy = ballon_rouge->dy - 15;
        }
    }
}


// Gérer les collisions entre les acteurs (tous les tirs) et un ballon_bleu
void collisionListeActeursBleu(t_ballon *ballon_bleu,t_listeActeurs *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeurBleu(ballon_bleu,la->tab[i]);

}

void collisionListeActeursRose(t_ballon *ballon_rose,t_listeActeurs *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeurRose(ballon_rose,la->tab[i]);

}

void collisionListeActeursVert(t_ballon *ballon_vert,t_listeActeurs *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeurVert(ballon_vert,la->tab[i]);

}

void collisionListeActeursViolet(t_ballon *ballon_violet,t_listeActeurs *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeurViolet(ballon_violet,la->tab[i]);

}

void collisionListeActeursRouge(t_ballon *ballon_rouge,t_listeActeurs *la){

    int i;

    // regarder pour chaque acteur...
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            collisionActeurRouge(ballon_rouge,la->tab[i]);

}