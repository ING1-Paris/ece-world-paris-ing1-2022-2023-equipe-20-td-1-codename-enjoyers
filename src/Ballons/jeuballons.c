#include "../../header.h"

/**********************/
/*     STRUCTURES     */
/**********************/


/*********************/
/*     PROTOTYPES    */
/*********************/

// Allouer et initialiser un acteur
// pour ce projet il faut x y de départ et type
//   ( à adapter selon besoins )
t_acteur * creerActeur(int x,int y,int type);

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs);

// Retourne un booléen vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la);

//compteur de ballons éclatés
int cpt_ballons ;

//temps performance joueur
double temps_ecouleeee, tmpJ1;

// Allouer et ajouter un acteur à la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de problème
// pour ce projet il faut x y de départ et type
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type);

// Enlever et libèrer un acteur qui était dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i);



// Actualiser un acteur (bouger ...)
void actualiserActeur(t_acteur *acteur);

// Gérer l'évolution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la);


// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur);

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la);


// Un acteur a été touché ou a touché un ballon : modifier son état
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divisé en norme (ralentissement)
void destinActeur(t_acteur *acteur);

// Gérer collision (éventuelle) entre un acteur (un tir) et un ballon_bleu
void collisionActeurBleu(t_ballon *ballon_bleu, t_acteur *acteur);
void collisionActeurRose(t_ballon *ballon_rose, t_acteur *acteur);
void collisionActeurVert(t_ballon *ballon_vert, t_acteur *acteur);
void collisionActeurViolet(t_ballon *ballon_violet, t_acteur *acteur);
void collisionActeurRouge(t_ballon *ballon_rouge, t_acteur *acteur);

// Gérer les collisions entre les acteurs (tous les tirs) et un ballon_bleu
void collisionListeActeursBleu(t_ballon *ballon_bleu,t_listeActeurs *la);
void collisionListeActeursRose(t_ballon *ballon_rose,t_listeActeurs *la);
void collisionListeActeursVert(t_ballon *ballon_vert,t_listeActeurs *la);
void collisionListeActeursViolet(t_ballon *ballon_violet,t_listeActeurs *la);
void collisionListeActeursRouge(t_ballon *ballon_rouge,t_listeActeurs *la);


// Spécifique à cet exemple : gérer le fusil et le ballon

// Allouer et initialiser joueur
t_joueur_ballons * creerJoueur(char *nomimage);

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueur_ballons *joueur,t_listeActeurs *la);

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueur_ballons *joueur);


// Allouer et initialiser ballon_bleu
t_ballon * creerBallon_bleu(char *nomimage);
t_ballon * creerBallon_rose(char *nomimage);
t_ballon * creerBallon_vert(char *nomimage);
t_ballon * creerBallon_violet(char *nomimage);
t_ballon * creerBallon_rouge(char *nomimage);


// Actualiser les ballons (bouger automatiquement au hasard...)
void actualiserBallon_bleu(t_ballon *ballon_bleu);
void actualiserBallon_rose(t_ballon *ballon_rose);
void actualiserBallon_vert(t_ballon *ballon_vert);
void actualiserBallon_violet(t_ballon *ballon_violet);
void actualiserBallon_rouge(t_ballon *ballon_rouge);

// Dessiner les ballons sur la bitmap bmp
void dessinerBallon_bleu(BITMAP *bmp,t_ballon *ballon_bleu);
void dessinerBallon_rose(BITMAP *bmp,t_ballon *ballon_rose);
void dessinerBallon_vert(BITMAP *bmp,t_ballon *ballon_vert);
void dessinerBallon_violet(BITMAP *bmp,t_ballon *ballon_violet);
void dessinerBallon_rouge(BITMAP *bmp,t_ballon *ballon_rouge);


/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle d'animation */
/******************************************/

void jeuballons()
{

    // Buffer
    BITMAP *page;

    // Image de fond
    BITMAP *decor;

    // La collection des acteurs (les tirs)
    t_listeActeurs *acteurs;

    // Le fusil manipulé par le joueur
    t_joueur_ballons *fusil;

    // Les ballons qui se déplacent automatiquement
    BITMAP *img[5];

    t_ballon *ballon1;
    t_ballon *ballon2;
    t_ballon *ballon3;
    t_ballon *ballon4;
    t_ballon *ballon5;

    // Il y aura du hasard
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,700,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // buffer
    page=create_bitmap(SCREEN_W,SCREEN_H);

    // charger image de fond
    decor=load_bitmap("shrek.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver shrek.bmp");
        exit(EXIT_FAILURE);
    }

    // créer le fusil et les ballons
    fusil=creerJoueur("fusil.bmp");
    ballon1=creerBallon_bleu("ballon_bleu.bmp");
    ballon2=creerBallon_rose("ballon_rose.bmp");
    ballon3=creerBallon_vert("ballon_vert.bmp");
    ballon4=creerBallon_violet("ballon_violet.bmp");
    ballon5=creerBallon_rouge("ballon_rouge.bmp");

    // préparer la liste des acteurs (100 maxi)
    // mais vide initialement
    acteurs=creerListeActeurs(100);

    // BOUCLE DE JEU
    for(int j=0; j<2; j++) {
        time_t temps_precedent = time(NULL);
        while (!key[KEY_ENTER]) {
            time_t temps_actuel = time(NULL);
            temps_ecouleeee = difftime(temps_actuel, temps_precedent);

            // effacer buffer en appliquant décor  (pas de clear_bitmap)
            blit(decor, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // bouger tout le monde
            actualiserJoueur(fusil, acteurs);
            actualiserBallon_bleu(ballon1);
            actualiserBallon_rose(ballon2);
            actualiserBallon_vert(ballon3);
            actualiserBallon_violet(ballon4);
            actualiserBallon_rouge(ballon5);

            actualiserListeActeurs(acteurs);

            // gérer les collisions
            collisionListeActeursBleu(ballon1, acteurs);
            collisionListeActeursRose(ballon2, acteurs);
            collisionListeActeursVert(ballon3, acteurs);
            collisionListeActeursViolet(ballon4, acteurs);
            collisionListeActeursRouge(ballon5, acteurs);

            // afficher tout le monde
            dessinerJoueur(page, fusil);
            dessinerBallon_bleu(page, ballon1);
            dessinerBallon_rose(page, ballon2);
            dessinerBallon_vert(page, ballon3);
            dessinerBallon_violet(page, ballon4);
            dessinerBallon_rouge(page, ballon5);

            dessinerListeActeurs(page, acteurs);

            // afficher tout ça à l'écran
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // petite temporisation
            rest(10);
        }
        allegro_message("vous avez éclaté les 5 ballons en %.1f secondes", temps_ecouleeee);
        if(j==0)
            tmpJ1 = temps_ecouleeee;
        else{
            if(tmpJ1 < temps_ecouleeee)
                allegro_message("Joueur 1, vous avez gagné un ticket !");
            else
                allegro_message("Joueur 2, vous avez gagné un ticket !");

        }
    }

}




/************************************************/
/*     DEFINITIONS DES SOUS-PROGRAMMES          */
/************************************************/


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
    switch (type)
    {
        // laser
        case 0:
            nouv->tx=5;
            nouv->ty=30;
            nouv->dx=0;
            nouv->dy=10;
            nouv->couleur=makecol(255,255,0);
            break;
    }
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
    if (acteur->comportement==0){
        switch(acteur->type)
        {
            case 0:
                rectfill(bmp,acteur->x,acteur->y,acteur->x-acteur->tx,acteur->y-acteur->ty,acteur->couleur);
                break;
        }
    }
        // sinon explosion d'un diamètre décroissant et d'une couleur rougissante
    else {
        switch(acteur->type)
        {
            case 0:
                circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));
                break;
        }
    }
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

// Allouer et ajouter un acteur à la liste et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de problème
// ( mais il vaut mieux d'abord vérifier qu'il
//   y a de la place disponible avant d'appeler )
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type){
    int i;
    t_acteur *acteur;

    // Liste pleine, on alloue rien et on retourne NULL...
    if (la->n >= la->max)
        return NULL;

    // Allouer un acteur initialisé
    acteur=creerActeur(x,y,type);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // Si on a trouvé ...
    // (normalement oui car on a vérifié n<max)
    if (i<la->max){
        // Accrocher le acteur à l'emplacement trouvé
        la->tab[i]=acteur;
        la->n++;
    }
        // Sinon c'est qu'il y a un problème de cohérence
    else
        allegro_message("Anomalie gestion ajouterActeur : liste corrompue");

    return acteur;
}

// Enlever et libèrer un acteur qui était dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i){

    // Vérifier qu'il y a bien un acteur accroché en indice i
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
    // si un acteur n'est plus vivant, l'enlever de la liste
    for (i=0;i<la->max;i++)
        if (la->tab[i]!=NULL){
            actualiserActeur(la->tab[i]);
            if (!la->tab[i]->vivant){
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


// Un acteur a été touché ou a touché une ballon : modifier son état
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divisé en norme (ralentissement)
void destinActeur(t_acteur *acteur){
    acteur->dx/=2;
    acteur->dy/=2;
    acteur->comportement=1;
    acteur->cptexplo=0;
}

// Gérer collision (éventuelle) entre un acteur (un tir) et un ballon_bleu
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
            cpt_ballons +=1;
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
            cpt_ballons += 1;
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
        if ( d2 < ballon_vert->tx * ballon_vert->tx / 4 )
            destinActeur(acteur);
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
        if ( d2 < ballon_violet->tx * ballon_violet->tx / 4 )
            destinActeur(acteur);
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
        if ( d2 < ballon_rouge->tx * ballon_rouge->tx / 4 )
            destinActeur(acteur);
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

// Allouer et initialiser un joueur
t_joueur_ballons * creerJoueur(char *nomimage){
    t_joueur_ballons *nouv;

    // Allouer
    nouv = (t_joueur_ballons *)malloc(1*sizeof(t_joueur_ballons));

    // Initialiser

    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/2-nouv->tx/2;
    nouv->y = SCREEN_H*7/8-nouv->ty/2;
    nouv->vit = 5;

    nouv->cpttir0 = 0;
    nouv->cpttir1 = 0;

    return nouv;
}

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserJoueur(t_joueur_ballons *joueur,t_listeActeurs *la){

    // Déplacements instantanés (pas d'inertie)
    // gestion d'un blocage dans une zone écran (moitié gauche)
    if (key[KEY_LEFT]){
        joueur->x -= joueur->vit;
        if (joueur->x<0)
            joueur->x=0;
    }

    if (key[KEY_RIGHT]){
        joueur->x += joueur->vit;
        if (joueur->x+joueur->tx > SCREEN_W/2)
            joueur->x=SCREEN_W/2-joueur->tx;
    }

    // Gestion du tir...

    // incrémenter la tempo des tirs
    joueur->cpttir0++;
    joueur->cpttir1++;

    // si le joueur appui sur la gachette et arme ok...
    // espace = laser
    if (key[KEY_SPACE] && joueur->cpttir0>=5){
        ajouterActeur(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,0);
        joueur->cpttir0 = 0;
    }

}

// Dessiner joueur sur la bitmap bmp
void dessinerJoueur(BITMAP *bmp,t_joueur_ballons *joueur){
    draw_sprite(bmp,joueur->img,joueur->x,joueur->y);
}


// Allouer et initialiser ballon_bleu
t_ballon * creerBallon_bleu(char *nomimage){
    t_ballon *nouv;

    // Allouer
    nouv = (t_ballon *)malloc(1*sizeof(t_ballon));

    // Initialiser
    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/2-nouv->tx/2;
    nouv->y = SCREEN_H/3-nouv->ty/2;
    nouv->dx=0;

    return nouv ;
}


// Allouer et initialiser ballon_rose
t_ballon * creerBallon_rose(char *nomimage){
    t_ballon *nouv;

    // Allouer
    nouv = (t_ballon *)malloc(1*sizeof(t_ballon));

    // Initialiser
    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/4-nouv->tx/2;
    nouv->y = SCREEN_H/5-nouv->ty/2;
    nouv->dx=0;

    return nouv ;
}


// Allouer et initialiser ballon_vert
t_ballon * creerBallon_vert(char *nomimage){
    t_ballon *nouv;

    // Allouer
    nouv = (t_ballon *)malloc(1*sizeof(t_ballon));

    // Initialiser
    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/2-nouv->tx/2;
    nouv->y = SCREEN_H/3-nouv->ty/2;
    nouv->dx=0;

    return nouv ;
}


// Allouer et initialiser ballon_violet
t_ballon * creerBallon_violet(char *nomimage){
    t_ballon *nouv;

    // Allouer
    nouv = (t_ballon *)malloc(1*sizeof(t_ballon));

    // Initialiser
    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W*2/3-nouv->tx/2;
    nouv->y = SCREEN_H/2-nouv->ty/2;
    nouv->dx=0;

    return nouv ;
}

// Allouer et initialiser ballon_rouge
t_ballon * creerBallon_rouge(char *nomimage){
    t_ballon *nouv;

    // Allouer
    nouv = (t_ballon *)malloc(1*sizeof(t_ballon));

    // Initialiser
    nouv->img=load_bitmap(nomimage,NULL);
    if (!nouv->img)
    {
        allegro_message("pas pu trouver %s",nomimage);
        exit(EXIT_FAILURE);
    }

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/4-nouv->tx/2;
    nouv->y = SCREEN_H/7-nouv->ty/2;
    nouv->dx=0;

    return nouv ;
}


// Actualiser ballon_bleu
// (bouger automatiquement au hasard)
void actualiserBallon_bleu(t_ballon *ballon_bleu){

    // proba de changement de déplacement : une chance sur 50
    if ( rand()%50==0 ){
        // Nouveau vecteur déplacement
        ballon_bleu->dx = rand()%11-5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (( ballon_bleu->x < 0 && ballon_bleu->dx < 0 ) || ( ballon_bleu->x + ballon_bleu->tx > SCREEN_W && ballon_bleu->dx > 0))
        ballon_bleu->dx = -ballon_bleu->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_bleu->x = ballon_bleu->x + ballon_bleu->dx;

}


void actualiserBallon_rose(t_ballon *ballon_rose){

    // proba de changement de déplacement : une chance sur 50
    if ( rand()%50==0 ){
        // Nouveau vecteur déplacement
        ballon_rose->dx = rand()%11-5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (( ballon_rose->x < 0 && ballon_rose->dx < 0 ) || ( ballon_rose->x + ballon_rose->tx > SCREEN_W && ballon_rose->dx > 0))
        ballon_rose->dx = -ballon_rose->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_rose->x = ballon_rose->x + ballon_rose->dx;

}

void actualiserBallon_vert(t_ballon *ballon_vert){

    // proba de changement de déplacement : une chance sur 50
    if ( rand()%50==0 ){
        // Nouveau vecteur déplacement
        ballon_vert->dx = rand()%11-5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (( ballon_vert->x < 0 && ballon_vert->dx < 0 ) || ( ballon_vert->x + ballon_vert->tx > SCREEN_W && ballon_vert->dx > 0))
        ballon_vert->dx = -ballon_vert->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_vert->x = ballon_vert->x + ballon_vert->dx;

}


void actualiserBallon_violet(t_ballon *ballon_violet){

    // proba de changement de déplacement : une chance sur 50
    if ( rand()%50==0 ){
        // Nouveau vecteur déplacement
        ballon_violet->dx = rand()%11-5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (( ballon_violet->x < 0 && ballon_violet->dx < 0 ) || ( ballon_violet->x + ballon_violet->tx > SCREEN_W && ballon_violet->dx > 0))
        ballon_violet->dx = -ballon_violet->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_violet->x = ballon_violet->x + ballon_violet->dx;

}

void actualiserBallon_rouge(t_ballon *ballon_rouge){

    // proba de changement de déplacement : une chance sur 50
    if ( rand()%50==0 ){
        // Nouveau vecteur déplacement
        ballon_rouge->dx = rand()%11-5;
    }

    // contrôle des bords : ici on décide de rebondir sur les bords
    if  (( ballon_rouge->x < 0 && ballon_rouge->dx < 0 ) || ( ballon_rouge->x + ballon_rouge->tx > SCREEN_W && ballon_rouge->dx > 0))
        ballon_rouge->dx = -ballon_rouge->dx;

    // calculer nouvelle position
    // nouvelle position = position actuelle + deplacement
    ballon_rouge->x = ballon_rouge->x + ballon_rouge->dx;

}


// Dessiner les ballons sur la bitmap bmp
void dessinerBallon_bleu(BITMAP *bmp,t_ballon *ballon_bleu){
    draw_sprite(bmp,ballon_bleu->img,ballon_bleu->x,ballon_bleu->y);
}
void dessinerBallon_rose(BITMAP *bmp,t_ballon *ballon_rose){
    draw_sprite(bmp,ballon_rose->img,ballon_rose->x,ballon_rose->y);
}
void dessinerBallon_vert(BITMAP *bmp,t_ballon *ballon_vert){
    draw_sprite(bmp,ballon_vert->img,ballon_vert->x,ballon_vert->y);
}
void dessinerBallon_violet(BITMAP *bmp,t_ballon *ballon_violet){
    draw_sprite(bmp,ballon_violet->img,ballon_violet->x,ballon_violet->y);
}
void dessinerBallon_rouge(BITMAP *bmp,t_ballon *ballon_rouge){
    draw_sprite(bmp,ballon_rouge->img,ballon_rouge->x,ballon_rouge->y);
}