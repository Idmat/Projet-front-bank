#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Définir le mot de passe administrateur
#define ADMIN_PASSWORD "1234"
// Définir les limites maximales pour les comptes et les transactions
#define MAX_COMPTES 100
#define MAX_TRANSACTIONS 100
#define LONGUEUR_NUMERO_COMPTE 14

// Structure pour les informations du client
typedef struct {
    char nom[50];
    char postnom[50];
    char prenom[50];
    char dateNaissance[20];
    char lieuNaissance[50];
    char adresse[100];
    char telephone[20];
} InfosClient;

// Structure pour le compte client
typedef struct {
    char numeroCompte[LONGUEUR_NUMERO_COMPTE + 1];
    char dateCreation[20];
    double solde;
    int nombreTransactions;
    InfosClient infos;
    struct {
        char date[20];
        char emetteur[LONGUEUR_NUMERO_COMPTE + 1];
        char receveur[LONGUEUR_NUMERO_COMPTE + 1];
        double montant;
    } transactions[MAX_TRANSACTIONS];
} Compte;

Compte comptes[MAX_COMPTES];
int nombreComptes = 0;

// Fonction pour générer un numéro de compte de 14 chiffres
void genererNumeroCompte(char *numeroCompte) {
    for (int i = 0; i < LONGUEUR_NUMERO_COMPTE; i++) {
        int random = rand() % 10;
        numeroCompte[i] = random + '0';
    }
    numeroCompte[LONGUEUR_NUMERO_COMPTE] = '\0';
}

// Fonction pour obtenir la date et l'heure actuelle
void obtenirDateActuelle(char *dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%02d-%02d-%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// Fonction pour sauvegarder les comptes dans un fichier
void sauvegarderComptes() {
    FILE *file = fopen("comptes.dat", "wb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fwrite(&nombreComptes, sizeof(int), 1, file);
    fwrite(comptes, sizeof(Compte), nombreComptes, file);
    fclose(file);
}

// Fonction pour charger les comptes depuis un fichier
void chargerComptes() {
    FILE *file = fopen("comptes.dat", "rb");
    if (file == NULL) {
        printf("Aucun fichier de sauvegarde trouvé.\n");
        return;
    }
    fread(&nombreComptes, sizeof(int), 1, file);
    fread(comptes, sizeof(Compte), nombreComptes, file);
    fclose(file);
}

// Fonction pour créer un nouveau compte client
void creerCompte() {
    if (nombreComptes >= MAX_COMPTES) {
        printf("Nombre maximum de comptes atteint.\n");
        return;
    }

    Compte nouveauCompte;
    genererNumeroCompte(nouveauCompte.numeroCompte);
    obtenirDateActuelle(nouveauCompte.dateCreation);

    printf("Entrez le nom : ");
    scanf("%s", nouveauCompte.infos.nom);
    printf("Entrez le postnom : ");
    scanf("%s", nouveauCompte.infos.postnom);
    printf("Entrez le prénom : ");
    scanf("%s", nouveauCompte.infos.prenom);
    printf("Entrez la date de naissance (JJ-MM-AAAA) : ");
    scanf("%s", nouveauCompte.infos.dateNaissance);
    printf("Entrez le lieu de naissance (pays) : ");
    scanf("%s", nouveauCompte.infos.lieuNaissance);
    printf("Entrez l'adresse actuelle (pays, ville, commune, avenue, numéro de la parcelle) : ");
    scanf(" %[^\n]s", nouveauCompte.infos.adresse);
    printf("Entrez le numéro de téléphone : ");
    scanf("%s", nouveauCompte.infos.telephone);

    printf("Entrez le montant du dépôt initial : ");
    scanf("%lf", &nouveauCompte.solde);
    nouveauCompte.nombreTransactions = 0;

    comptes[nombreComptes++] = nouveauCompte;

    sauvegarderComptes();  // Sauvegarder les comptes après la création

    printf("Compte créé avec succès !\n");
    printf("Numéro de compte : %s\n", nouveauCompte.numeroCompte);
    printf("Date de création : %s\n", nouveauCompte.dateCreation);
    printf("Solde : %.2f\n", nouveauCompte.solde);
}

// Fonction pour lister tous les comptes
void listerComptes() {
    char motDePasseAdmin[20];
    printf("Entrez le mot de passe admin pour lister les comptes : ");
    scanf("%s", motDePasseAdmin);

    if (strcmp(motDePasseAdmin, ADMIN_PASSWORD) != 0) {
        printf("Mot de passe invalide.\n");
        return;
    }

    // Trier les comptes par date de création
    for (int i = 0; i < nombreComptes - 1; i++) {
        for (int j = i + 1; j < nombreComptes; j++) {
            if (strcmp(comptes[i].dateCreation, comptes[j].dateCreation) > 0) {
                Compte temp = comptes[i];
                comptes[i] = comptes[j];
                comptes[j] = temp;
            }
        }
    }

    for (int i = 0; i < nombreComptes; i++) {
        printf("Numéro de compte : %s\n", comptes[i].numeroCompte);
        printf("Date de création : %s\n", comptes[i].dateCreation);
        printf("Solde : %.2f\n", comptes[i].solde);
        printf("Nom : %s\n", comptes[i].infos.nom);
        printf("Postnom : %s\n", comptes[i].infos.postnom);
        printf("Prénom : %s\n", comptes[i].infos.prenom);
        printf("Date de naissance : %s\n", comptes[i].infos.dateNaissance);
        printf("Lieu de naissance : %s\n", comptes[i].infos.lieuNaissance);
        printf("Adresse : %s\n", comptes[i].infos.adresse);
        printf("Numéro de téléphone : %s\n", comptes[i].infos.telephone);
        printf("\n");
    }
}

// Fonction pour enregistrer une transaction
void enregistrerTransaction(char *emetteur, char *receveur, double montant) {
    Compte *compteEmetteur = NULL;
    Compte *compteReceveur = NULL;

    for (int i = 0; i < nombreComptes; i++) {
        if (strcmp(comptes[i].numeroCompte, emetteur) == 0) {
            compteEmetteur = &comptes[i];
        }
        if (strcmp(comptes[i].numeroCompte, receveur) == 0) {
            compteReceveur = &comptes[i];
        }
    }

    if (compteEmetteur == NULL || compteReceveur == NULL) {
        printf("Numéro de compte invalide.\n");
        return;
    }

    if (compteEmetteur->solde < montant) {
        printf("Fonds insuffisants.\n");
        return;
    }

    compteEmetteur->solde -= montant;
    compteReceveur->solde += montant;

    char date[20];
    obtenirDateActuelle(date);

    strcpy(compteEmetteur->transactions[compteEmetteur->nombreTransactions].date, date);
    strcpy(compteEmetteur->transactions[compteEmetteur->nombreTransactions].emetteur, emetteur);
    strcpy(compteEmetteur->transactions[compteEmetteur->nombreTransactions].receveur, receveur);
    compteEmetteur->transactions[compteEmetteur->nombreTransactions].montant = montant;
    compteEmetteur->nombreTransactions++;

    strcpy(compteReceveur->transactions[compteReceveur->nombreTransactions].date, date);
    strcpy(compteReceveur->transactions[compteReceveur->nombreTransactions].emetteur, emetteur);
    strcpy(compteReceveur->transactions[compteReceveur->nombreTransactions].receveur, receveur);
    compteReceveur->transactions[compteReceveur->nombreTransactions].montant = montant;
    compteReceveur->nombreTransactions++;

    sauvegarderComptes();  // Sauvegarder les comptes après une transaction

    printf("Transaction réussie ! Vous avez transmis une somme de %.2f à %s %s\n", montant, compteReceveur->infos.nom, compteReceveur->infos.postnom);
}

// Fonction pour voir les transactions d'un compte spécifique
void voirTransactionsCompte(char *numeroCompte) {
    Compte *compte = NULL;

    for (int i = 0; i < nombreComptes; i++) {
        if (strcmp(comptes[i].numeroCompte, numeroCompte) == 0) {
            compte = &comptes[i];
            break;
        }
    }

    if (compte == NULL) {
        printf("Numéro de compte invalide.\n");
        return;
    }

    printf("Transactions pour le compte %s :\n", compte->numeroCompte);
    for (int i = 0; i < compte->nombreTransactions; i++) {
        printf("Date : %s, Émetteur : %s, Receveur : %s, Montant : %.2f\n",
               compte->transactions[i].date,
               compte->transactions[i].emetteur,
               compte->transactions[i].receveur,
               compte->transactions[i].montant);
    }
}

// Fonction pour supprimer un compte
void supprimerCompte() {
    char motDePasseAdmin[20];
    printf("Entrez le mot de passe admin pour supprimer un compte : ");
    scanf("%s", motDePasseAdmin);

    if (strcmp(motDePasseAdmin, ADMIN_PASSWORD) != 0) {
        printf("Mot de passe invalide.\n");
        return;
    }

    char numeroCompte[LONGUEUR_NUMERO_COMPTE + 1];
    printf("Entrez le numéro de compte à supprimer : ");
    scanf("%s", numeroCompte);

    int index = -1;
    for (int i = 0; i < nombreComptes; i++) {
        if (strcmp(comptes[i].numeroCompte, numeroCompte) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Numéro de compte introuvable.\n");
        return;
    }

    printf("Compte trouvé : %s %s %s\n", comptes[index].infos.nom, comptes[index].infos.postnom, comptes[index].infos.prenom);
    printf("Votre compte a été supprimé.\n");

    // Déplacer le dernier compte à l'index de celui à supprimer
    comptes[index] = comptes[nombreComptes - 1];
    nombreComptes--;

    sauvegarderComptes();  // Sauvegarder les comptes après la suppression
}

// Fonction pour effectuer des opérations sur le compte
void operationsCompte() {
    char numeroCompte[LONGUEUR_NUMERO_COMPTE + 1];
    printf("Entrez votre numéro de compte : ");
    scanf("%s", numeroCompte);

    Compte *compte = NULL;
    for (int i = 0; i < nombreComptes; i++) {
        if (strcmp(comptes[i].numeroCompte, numeroCompte) == 0) {
            compte = &comptes[i];
            break;
        }
    }

    if (compte == NULL) {
        printf("Numéro de compte invalide.\n");
        return;
    }

    int option;
    printf("1. Transférer des fonds\n2. Dépôt\n3. Retrait\n4. Voir vos transactions\n");
    scanf("%d", &option);

    if (option == 1) {
        char compteReceveur[LONGUEUR_NUMERO_COMPTE + 1];
        double montant;

        printf("Entrez le numéro de compte du receveur : ");
        scanf("%s", compteReceveur);
        printf("Entrez le montant à transférer : ");
        scanf("%lf", &montant);

        enregistrerTransaction(numeroCompte, compteReceveur, montant);

    } else if (option == 2) {
        double montant;
        printf("Entrez le montant à déposer : ");
        scanf("%lf", &montant);

        compte->solde += montant;
        sauvegarderComptes();  // Sauvegarder les comptes après un dépôt
        printf("Dépôt réussi ! Nouveau solde : %.2f\n", compte->solde);

    } else if (option == 3) {
        double montant;
        printf("Entrez le montant à retirer : ");
        scanf("%lf", &montant);

        if (montant > compte->solde) {
            printf("Fonds insuffisants.\n");
        } else {
            compte->solde -= montant;
            sauvegarderComptes();  // Sauvegarder les comptes après un retrait
            printf("Retrait réussi ! Nouveau solde : %.2f\n", compte->solde);
        }

    } else if (option == 4) {
        voirTransactionsCompte(numeroCompte);

    } else {
        printf("Option invalide.\n");
    }
}

// Fonction principale
int main() {
    srand(time(NULL));
    chargerComptes(); // Charger les comptes depuis le fichier au démarrage
    int choix;

    while (1) {
        printf("\nSystème de Gestion Bancaire\n");
        printf("1. Créer un compte\n");
        printf("2. Lister les comptes\n");
        printf("3. Opérations sur le compte\n");
        printf("4. Supprimer un compte\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creerCompte();
                break;
            case 2:
                listerComptes();
                break;
            case 3:
                operationsCompte();
                break;
            case 4:
                supprimerCompte();
                break;
            case 5:
                sauvegarderComptes();  // Sauvegarder les comptes avant de quitter
                exit(0);
            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
