#ifndef AFFICHAGE_H
  #define AFFICHAGE_H
    // Library public
    #include <windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

    // Prototypes des fonctions
    void afficherMenuAjouter(char*, char*, char*, char*, int*, float*);
    void afficherMenuSupprimer(char*, char*);
    int afficherMenuPrincipal();
    void afficherMenuRechercher(char[], char[]);
    char confirmer();
    void traitement();
    void clearScreen();
#endif
