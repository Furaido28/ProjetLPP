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
        input = afficherMenuPrincipal();

        switch (input) {
            case 1: {
                printf("\n\033[1;33mNom du magasin\033[0m > ");
                scanf("%99s", nomMagasin);

                // Rechercher ou créer le magasin
                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);

                if (magasin == NULL) {
                    magasin = creerMagasin(nomMagasin);
                    magasin->suivant = listeMagasins;
                    listeMagasins = magasin;
                    printf("\033[1;32mMagasin '%s' cr%c%c avec succ%cs.\033[0m\n", nomMagasin, 130, 130, 138);
                } else {
                    printf("\033[1;36mMagasin '%s' trouv%c.\033[0m\n", nomMagasin, 130);
                }

                // Affichage du menu ajouter
                afficherMenuAjouter(nomProduit, nomCategorie, nomMarque, nomRayon, &quantiteProduit, &prixProduit);

                // Ajouter le produit au magasin
                ajouterProduit(magasin, nomProduit, nomCategorie, nomMarque, nomRayon, quantiteProduit, prixProduit);
                printf("\033[1;32mProduit '%s' ajout%c avec succ%cs au magasin '%s'.\033[0m\n", nomProduit, 130, 138, nomMagasin);
                break;
            }
            case 2: {
                printf("\n\033[1;33mNom du magasin\033[0m > ");
                scanf("%99s", nomMagasin);

                store *magasin = rechercherMagasin(listeMagasins, nomMagasin);
                if (magasin == NULL) {
                    printf("\033[1;31mMagasin introuvable.\033[0m\n");
                    break;
                }

                // Affichage du menu supprimer
                afficherMenuSupprimer(nomProduit, nomMarque);

                supprimerProduit(magasin, nomProduit, nomMarque);
                break;
            }
            case 3:
                break;
            case 4:
                printf("\n\033[1;36mListe des magasins et produits :\033[0m\n");
                afficherMagasinsEtProduits(listeMagasins);
                break;
            case 5:
                archiverListe(listeMagasins);
                break;
            case 6:
                importerListe(&listeMagasins);
                break;
            case 7:
                //supprimerArchive();
                break;
            case 10:
                printf("\n\033[1;35mFermeture du programme...\033[0m\n");
                break;
        }
    } while (input != 10);

    return 0;
}
