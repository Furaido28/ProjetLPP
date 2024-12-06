#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "affichage.h"

// -----------------
// Affichage du menu
// -----------------
int afficherMenuPrincipal() {
    int input;
    do {
        printf("\033[1;33mFaites un choix :\033[0m\n");
        printf("  \033[1;32m1.\033[0m Ajouter un produit\n");
        printf("  \033[1;32m2.\033[0m Supprimer un produit\n");
        printf("  \033[1;32m3.\033[0m Rechercher un produit\n");
        printf("  \033[1;32m4.\033[0m Afficher la liste des produits\n");
        printf("  \033[1;32m5.\033[0m Archiver la liste des produits\n");
        printf("  \033[1;32m6.\033[0m Importer une liste de produits\n");
        printf("  \033[1;34m------\033[0m\n");
        printf("  \033[1;31m0.\033[0m Fermer le programme\n");
        printf("\n");

        printf("> ");
        scanf("%d", &input);
        if (input != 0 && (input < 1 || input > 6)) {
            printf("Erreur - Veuillez s%clectionner une option valide.\n\n", 130);
            printf("Appuyez sur Entr%ce pour continuer...", 130);
            getchar(); getchar();
            clearScreen();
        }
    } while (input != 0 && (input < 1 || input > 6));
    clearScreen();
    return input;
}

void afficherMenuAjouter(char *nomProduit, char *nomCategorie, char *nomMarque, char *nomRayon, int *quantiteProduit, float *prixProduit) {
    printf("\033[1;32mNom du produit\033[0m > ");
    scanf("%s", nomProduit);

    printf("\033[1;32mNom de la cat%cgorie\033[0m > ", 130);
    scanf("%s", nomCategorie);

    printf("\033[1;32mNom de la marque\033[0m > ");
    scanf("%s", nomMarque);

    printf("\033[1;32mNom du rayon\033[0m > ");
    scanf("%s", nomRayon);

    printf("\033[1;32mQuantit%c\033[0m > ", 130);
    scanf("%d", quantiteProduit);

    printf("\033[1;32mPrix\033[0m > ");
    scanf("%f", prixProduit);

    printf("Appuyez sur Entr%ce pour revenir au menu principal...", 130);
    getchar(); getchar();
    clearScreen();
}

void afficherMenuSupprimer(char *nomProduit, char *nomMarque) {

    printf("============================================\n");
    printf("        \033[1;31m*** Supprimer un Produit ***\033[0m\n");
    printf("============================================\n\n");

    printf("\033[1;33mVeuillez entrer les informations suivantes pour supprimer un produit :\033[0m\n\n");

    printf("\033[1;32mNom du produit\033[0m > ");
    scanf("%s", nomProduit);

    printf("\033[1;32mNom de la marque\033[0m > ");
    scanf("%s", nomMarque);

    printf("Appuyez sur Entr%ce pour confirmer et revenir au menu principal...", 130);
    getchar(); getchar();
    clearScreen();
}

void afficherMenuRechercher(char nom_produit[], char nom_marque[]) {
    printf("=============================================\n");
    printf("        \033[1;31m*** Rechercher un Produit ***\033[0m\n");
    printf("=============================================\n\n");

    printf("\033[1;32mNom du produit\033[0m > ");
    scanf("%s", nom_produit);
    printf("\033[1;32mNom de la marque\033[0m > ");
    scanf("%s", nom_marque);
    clearScreen();
}
// -------------------------------
// Fonction pour effacer le terminal
// -------------------------------
char confirmer() {
    char input = 'Y';
    do {
        printf("\033[1;32mVeuillez confirmer votre choix (Y/N) \033[0m > ");
        scanf(" %c", &input);

        if (input >= 'y' || input <= 'n') {
            input = toupper(input);
        }
    } while (input != 'Y' && input != 'N');
    clearScreen();
    return input;
}

// -------------------------------
// Fonction pour effacer le terminal
// -------------------------------
void clearScreen() {
    Sleep(550);
    system("cls");
}