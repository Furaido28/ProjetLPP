//  **********************************
//  Nom     :   Flipo       Makhloufi
//  Prénom  :   Ethan       Olivia
//  Classe  :   2BIA1
//  **********************************

//  Library public
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Library privé
#include "store.h"
#include "affichage.h"

// -------------
// Fonction main
// -------------

int main() {
    store *listeMagasins = NULL;
    char nomMagasin[100], nomProduit[80], nomCategorie[80], nomMarque[80], nomRayon[80];
    int quantiteProduit, input;
    float prixProduit;

    do {
        input = afficherMenu();

        switch (input) {
            case 1: {
                printf("\nNom du magasin > ");
                scanf("%s", nomMagasin);

                // Rechercher ou cr�er le magasin
                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);
                if (magasin == NULL) {
                    magasin = creerMagasin(nomMagasin);
                    magasin->suivant = listeMagasins;
                    listeMagasins = magasin;
                }

                // Saisir les d�tails du produit
                printf("Nom du produit > ");
                scanf("%s", nomProduit);
                printf("Nom de la cat%cgorie > ", 130);
                scanf("%s", nomCategorie);
                printf("Nom de la marque > ");
                scanf("%s", nomMarque);
                printf("Nom du rayon > ");
                scanf("%s", nomRayon);
                printf("Quantit%c > ", 130);
                scanf("%d", &quantiteProduit);
                printf("Prix > ");
                scanf("%f", &prixProduit);

                // Ajouter le produit au magasin
                ajouterProduit(magasin, nomProduit, nomCategorie, nomMarque, nomRayon, quantiteProduit, prixProduit);
                break;
            }
            case 2: {
                printf("\nNom du magasin > ");
                scanf("%s", nomMagasin);

                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);
                if (magasin == NULL) {
                    printf("\nMagasin introuvable.\n");
                    break;
                }

                printf("Nom du produit > ");
                scanf("%s", nomProduit);
                printf("Nom de la marque > ");
                scanf("%s", nomMarque);

                supprimerProduit(magasin, nomProduit, nomMarque);
                break;
            }
            case 3:
                afficherMagasinsEtProduits(listeMagasins);
                break;
            case 10:
                printf("\nFermeture du programme...\n");
                break;
            default:
                printf("Erreur - Veuillez s%clectionner une option valide.\n", 130);
        }
    } while (input != 10);

    return 0;
}
