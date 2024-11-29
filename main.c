#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Structure pour représenter une catégorie
typedef struct {
    int id;
    char nom[50];
} Categorie;

// Structure pour représenter un produit
typedef struct {
    int id;
    char nom[50];
    float prix;
    int quantite;
    Categorie categorie;
} Produit;

// Fonction pour vérifier si une catégorie existe déjà par son ID
int categorieExiste(Categorie categories[], int nbCategories, int id) {
    for (int i = 0; i < nbCategories; i++) {
        if (categories[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour vérifier si un produit existe déjà par son ID
int produitExiste(Produit produits[], int nbProduits, int id) {
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour ajouter une catégorie
void ajouterCategorie(Categorie categories[], int *nbCategories, int id, char *nom) {
    if (categorieExiste(categories, *nbCategories, id)) {
        printf("Erreur : Une catégorie avec cet ID existe déjà.\n");
        return;
    }
    categories[*nbCategories].id = id;
    strcpy(categories[*nbCategories].nom, nom);
    (*nbCategories)++;
    printf("Catégorie ajoutée avec succès.\n");
}

// Fonction pour ajouter un produit
void ajouterProduit(Produit produits[], int *nbProduits, int id, char *nom, float prix, int quantite, Categorie categorie) {
    if (produitExiste(produits, *nbProduits, id)) {
        printf("Erreur : Un produit avec cet ID existe déjà.\n");
        return;
    }
    produits[*nbProduits].id = id;
    strcpy(produits[*nbProduits].nom, nom);
    produits[*nbProduits].prix = prix;
    produits[*nbProduits].quantite = quantite;
    produits[*nbProduits].categorie = categorie;
    (*nbProduits)++;
    printf("Produit ajouté avec succès.\n");
}

// Fonction pour afficher toutes les catégories
void afficherCategories(Categorie categories[], int nbCategories) {
    printf("\nListe des catégories :\n");
    for (int i = 0; i < nbCategories; i++) {
        printf("ID: %d | Nom: %s\n", categories[i].id, categories[i].nom);
    }
    if (nbCategories == 0) {
        printf("Aucune catégorie trouvée.\n");
    }
}

// Fonction pour afficher tous les produits
void afficherProduits(Produit produits[], int nbProduits) {
    printf("\nListe des produits :\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("ID: %d | Nom: %s | Prix: %.2f | Quantité: %d | Catégorie: %s\n",
               produits[i].id, produits[i].nom, produits[i].prix, produits[i].quantite, produits[i].categorie.nom);
    }
    if (nbProduits == 0) {
        printf("Aucun produit trouvé.\n");
    }
}

// Fonction pour supprimer une catégorie
void supprimerCategorie(Categorie categories[], int *nbCategories, int id) {
    int trouve = 0;
    for (int i = 0; i < *nbCategories; i++) {
        if (categories[i].id == id) {
            trouve = 1;
            for (int j = i; j < *nbCategories - 1; j++) {
                categories[j] = categories[j + 1];
            }
            (*nbCategories)--;
            printf("Catégorie supprimée avec succès.\n");
            break;
        }
    }
    if (!trouve) {
        printf("Erreur : Catégorie introuvable.\n");
    }
}

// Fonction pour supprimer un produit
void supprimerProduit(Produit produits[], int *nbProduits, int id) {
    int trouve = 0;
    for (int i = 0; i < *nbProduits; i++) {
        if (produits[i].id == id) {
            trouve = 1;
            for (int j = i; j < *nbProduits - 1; j++) {
                produits[j] = produits[j + 1];
            }
            (*nbProduits)--;
            printf("Produit supprimé avec succès.\n");
            break;
        }
    }
    if (!trouve) {
        printf("Erreur : Produit introuvable.\n");
    }
}

// Fonction pour modifier une catégorie
void modifierCategorie(Categorie categories[], int nbCategories, int id) {
    for (int i = 0; i < nbCategories; i++) {
        if (categories[i].id == id) {
            printf("Nouveau nom de la catégorie : ");
            char nom[50];
            scanf(" %49[^\n]", nom);
            strcpy(categories[i].nom, nom);
            printf("Catégorie modifiée avec succès.\n");
            return;
        }
    }
    printf("Erreur : Catégorie introuvable.\n");
}

// Fonction pour modifier un produit
void modifierProduit(Produit produits[], int nbProduits, Categorie categories[], int nbCategories, int id) {
    for (int i = 0; i < nbProduits; i++) {
        if (produits[i].id == id) {
            printf("Nouveau nom du produit : ");
            char nom[50];
            scanf(" %49[^\n]", nom);
            strcpy(produits[i].nom, nom);

            printf("Nouveau prix : ");
            scanf("%f", &produits[i].prix);

            printf("Nouvelle quantité : ");
            scanf("%d", &produits[i].quantite);

            afficherCategories(categories, nbCategories);
            printf("ID de la nouvelle catégorie : ");
            int idCategorie;
            scanf("%d", &idCategorie);

            for (int j = 0; j < nbCategories; j++) {
                if (categories[j].id == idCategorie) {
                    produits[i].categorie = categories[j];
                    printf("Produit modifié avec succès.\n");
                    return;
                }
            }

            printf("Erreur : Catégorie introuvable.\n");
            return;
        }
    }
    printf("Erreur : Produit introuvable.\n");
}

// Fonction pour afficher le menu principal
void afficherMenu() {
    printf("\n=== Menu ===\n");
    printf("1. Ajouter une catégorie\n");
    printf("2. Ajouter un produit\n");
    printf("3. Afficher les catégories\n");
    printf("4. Afficher les produits\n");
    printf("5. Supprimer une catégorie\n");
    printf("6. Supprimer un produit\n");
    printf("7. Modifier une catégorie\n");
    printf("8. Modifier un produit\n");
    printf("9. Quitter\n");
    printf("Choix : ");
}

// Fonction principale
int main() {
    setlocale(LC_ALL, ""); // Configurer l'encodage pour UTF-8

    Produit produits[100];
    Categorie categories[50];
    int nbProduits = 0, nbCategories = 0;

    while (1) {
        afficherMenu();
        int choix;
        scanf("%d", &choix);

        if (choix == 9) break;

        int id;
        char nom[50];
        float prix;
        int quantite, idCategorie;
        switch (choix) {
            case 1:
                printf("ID de la catégorie : ");
                scanf("%d", &id);
                printf("Nom de la catégorie : ");
                scanf(" %49[^\n]", nom);
                ajouterCategorie(categories, &nbCategories, id, nom);
                break;
            case 2:
                printf("ID du produit : ");
                scanf("%d", &id);
                printf("Nom du produit : ");
                scanf(" %49[^\n]", nom);
                printf("Prix : ");
                scanf("%f", &prix);
                printf("Quantité : ");
                scanf("%d", &quantite);
                afficherCategories(categories, nbCategories);
                printf("ID de la catégorie : ");
                scanf("%d", &idCategorie);

                Categorie cat;
                for (int i = 0; i < nbCategories; i++) {
                    if (categories[i].id == idCategorie) {
                        cat = categories[i];
                        break;
                    }
                }
                ajouterProduit(produits, &nbProduits, id, nom, prix, quantite, cat);
                break;
            case 3:
                afficherCategories(categories, nbCategories);
                break;
            case 4:
                afficherProduits(produits, nbProduits);
                break;
            case 5:
                printf("ID de la catégorie à supprimer : ");
                scanf("%d", &id);
                supprimerCategorie(categories, &nbCategories, id);
                break;
            case 6:
                printf("ID du produit à supprimer : ");
                scanf("%d", &id);
                supprimerProduit(produits, &nbProduits, id);
                break;
            case 7:
                printf("ID de la catégorie à modifier : ");
                scanf("%d", &id);
                modifierCategorie(categories, nbCategories, id);
                break;
            case 8:
                printf("ID du produit à modifier : ");
                scanf("%d", &id);
                modifierProduit(produits, nbProduits, categories, nbCategories, id);
                break;
            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
