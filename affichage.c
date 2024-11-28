#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affichage.h"

// -----------------
// Affichage du menu
// -----------------
int afficherMenuPrincipal() {
    int input;
    do {
        printf("\nFaites un choix\n");
        printf("1. Ajouter un produit\n");
        printf("2. Supprimer un produit\n");
        printf("3. Rechercher un produit\n");
        printf("4. Afficher la liste des produits\n");
        printf("5. Archiver la liste des produits\n");
        printf("6. Importer une liste d%cj%c existante\n", 130, 133);
        printf("   ------\n");
        printf("10. Fermer le programme\n");
        printf("> ");
        scanf("%d", &input);
        if (input < 1 || (input > 6 && input != 10)) {
            printf("Erreur - Veuillez s%clectionner une option valide.\n", 130);
        }
    } while (input < 1 || (input > 6 && input != 10));
    return input;
}

void afficherMenuAjouter(char *nomProduit, char *nomCategorie, char *nomMarque, char *nomRayon, int *quantiteProduit, float *prixProduit) {
    // Saisir les détails du produit
    printf("Nom du produit > ");
    scanf("%s", nomProduit);
    printf("Nom de la cat%cgorie > ", 130);
    scanf("%s", nomCategorie);
    printf("Nom de la marque > ");
    scanf("%s", nomMarque);
    printf("Nom du rayon > ");
    scanf("%s", nomRayon);
    printf("Quantit%c > ", 130);
    scanf("%d", quantiteProduit);
    printf("Prix > ");
    scanf("%f", prixProduit);
}

void afficherMenuSupprimer(char *nomProduit, char *nomMarque) {
    printf("Nom du produit > ");
    scanf("%s", nomProduit);
    printf("Nom de la marque > ");
    scanf("%s", nomMarque);
}