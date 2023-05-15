//
// Created by thais on 15/05/2023.
//
#include "../../header.h"

// Allouer et initialiser un acteur
t_acteur * creerActeur(int x,int y,int type){
    t_acteur *nouv;

    // Allouer
    nouv=(t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialiser ...

    // ici ce qui est commun aux acteurs
    nouv->x=x;
    nouv->y=y;
    nouv->type=type;
    nouv->comportement=0;
    nouv->cptexplo=0; // pas encore explosé mais on initialise par sécurité
    nouv->vivant=1;

    // ici ce qui est spécifique aux types
    nouv->tx=5;
    nouv->ty=30;
    nouv->dx=0;
    nouv->dy=10;
    nouv->couleur=makecol(255,255,0);
    return nouv;
}

// Actualiser un acteur (bouger, sortie écran, fin explosion ...)
void actualiserActeur(t_acteur *acteur) {

    // deplacement
    acteur->x=acteur->x-acteur->dx;
    acteur->y=acteur->y-acteur->dy;

    // si dépasse le bord alors disparait
    if (acteur->x+acteur->tx<0 || acteur->x>SCREEN_W || acteur->y+acteur->ty<0 || acteur->y>SCREEN_H )
        acteur->vivant=0;

    // si en cours d'explosion incrémenter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (acteur->comportement==1)
    {
        acteur->cptexplo++;
        if (acteur->cptexplo > 7)
            acteur->vivant=0;
    }
}

// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur){
    // Si pas d'explosion
    if (acteur->comportement==0)
        rectfill(bmp,acteur->x,acteur->y,acteur->x-acteur->tx,acteur->y-acteur->ty,acteur->couleur);
        // sinon explosion d'un diamètre décroissant et d'une couleur rougissante
    else
        circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));
}

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs){
    t_listeActeurs *nouv;
    int i;

    nouv=(t_listeActeurs *)malloc(1*sizeof(t_listeActeurs));

    nouv->max=maxacteurs;
    nouv->n=0;
    nouv->tab=(t_acteur **)malloc(maxacteurs*sizeof(t_acteur*));

    for (i=0;i<maxacteurs;i++)
        nouv->tab[i]=NULL;

    return nouv;
}

// Retourne un booléen vrai s'il reste de la place dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la){
    return la->n < la->max;
}

// Allouer et ajouter un acteur à la liste et retourner l'adresse de ce nouvel acteur
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type){
    int i;
    t_acteur *acteur;

    // Liste pleine
    if (la->n >= la->max)
        return NULL; // retourne NULL en cas de problème

    // Allouer un acteur initialisé
    acteur=creerActeur(x,y,type);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // s'il y a de la place :
    if (i<la->max){
        // Accrocher l'acteur à l'emplacement trouvé
        la->tab[i]=acteur;
        la->n++;
    }

    else
        allegro_message("Anomalie gestion ajouterActeur : liste corrompue");

    return acteur;
}

// Enlever et libérer de la place
void enleverActeur(t_listeActeurs *la,int i){

    // On vérifie qu'il y a bien un acteur en indice i
    if (la->tab[i]!=NULL)
    {
        // libérer la mémoire du acteur
        free(la->tab[i]);

        // marquer l'emplacement comme libre
        la->tab[i]=NULL;
        la->n--;

    }
}

// Gérer l'évolution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la){
    int i;

    // actualiser chaque acteur
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL){
            actualiserActeur(la->tab[i]);
            if (!la->tab[i]->vivant){     // si un acteur n'est plus vivant, l'enlever de la liste
                enleverActeur(la,i);
            }
        }
}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la){
    int i;

    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL)
            dessinerActeur(bmp,la->tab[i]);

}

// Un acteur a touché un ballon, il faut modifier son état
void destinActeur(t_acteur *acteur){
    acteur->dx/=2;
    acteur->dy/=2;
    acteur->comportement=1; // il passe en comportement 1 => explosion
    acteur->cptexplo=0;
}