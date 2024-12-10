#ifndef AFFICHAGE_H
  #define AFFICHAGE_H
    // Library public
    #include <windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

    // Library privé
    #include "store.h"

    // Prototypes des fonctions
    int afficherMenuPrincipal();
    void afficherMenuAjouter(char*, char*, char*, char*, int*, float*);
    void afficherMenuSupprimer(char*, char*);
    int afficherMenuAffichage();
    void afficherMenuRechercher(char[], char[]);
    char confirmer();
    void traitement();
    void clearScreen();
#endif
