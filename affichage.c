#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affichage.h"

// -----------------
// Affichage du menu
// -----------------
int afficherMenu() {
    int input;
    do {
        printf("\nFaites un choix\n");
        printf("1. Ajouter un produit\n");
        printf("2. Supprimer un produit\n");
        printf("3. Afficher les magasins et produits\n");
        printf("   ------\n");
        printf("10. Fermer le programme\n");
        printf("> ");
        scanf("%d", &input);
        if (input < 1 || (input > 3 && input != 10)) {
            printf("Erreur - Veuillez s%clectionner une option valide.\n", 130);
        }
    } while (input < 1 || (input > 3 && input != 10));
    return input;
}
