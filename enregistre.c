ypedef struct {
    char nom[NOM_TAILLE];
    char postnom[NOM_TAILLE];
    char prenom[NOM_TAILLE];
    char dateNaissance[DATE_TAILLE];
    char lieuNaissance[NOM_TAILLE];
    char adressePays[NOM_TAILLE];
    char adresseVille[NOM_TAILLE];
    char adresseCommune[NOM_TAILLE];
    char adresseAvenue[NOM_TAILLE];
    char adresseNumeroParcelle[NOM_TAILLE];
    char numeroTelephone[TELEPHONE_TAILLE];
} Client;

typedef struct {
    char numeroCompte[NUMERO_COMPTE_TAILLE];
    Client client;
    double solde;
    time_t dateCreation;
} Compte;

typedef struct {
    char numeroCompte[NUMERO_COMPTE_TAILLE];
    double montant;
    char type; // 'D' pour dépôt, 'R' pour retrait
    time_t date;
} Transaction;

// Fonction pour ouvrir un fichier avec gestion d'erreur
FILE* ouvrir_fichier(const char* nom_fichier, const char* mode) {
    FILE* fichier = fopen(nom_fichier, mode);
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    return fichier;
}

// Fonction pour fermer un fichier
void fermer_fichier(FILE* fichier) {
    if (fichier != NULL) {
        fclose(fichier);
    }
}

// Fonction pour générer un numéro de compte
void generer_numero_compte(char* numero_compte, int compteur) {
    sprintf(numero_compte, "%014d", compteur);
}

// Fonction pour ajouter un compte
void ajouter_compte(Compte* comptes, int* compteur_comptes) {
    if (*compteur_comptes >= MAX_CLIENTS) {
        printf("\033[1;31mLimite de création de comptes atteinte pour aujourd'hui.\033[0m\n");
        return;
    }

    Compte nouveau_compte;
    Client nouveau_client;

    // Saisie des informations du client
    printf("Nom : ");
    scanf("%s", nouveau_client.nom);
    printf("Post-nom : ");
    scanf("%s", nouveau_client.postnom);
    printf("Prénom : ");
    scanf("%s", nouveau_client.prenom);
    printf("Date de naissance (jj/mm/aaaa) : ");
    scanf("%s", nouveau_client.dateNaissance);
    printf("Lieu de naissance : ");
    scanf("%s", nouveau_client.lieuNaissance);
    printf("Adresse - Pays : ");
    scanf("%s", nouveau_client.adressePays);
    printf("Adresse - Ville : ");
    scanf("%s", nouveau_client.adresseVille);
    printf("Adresse - Commune : ");
    scanf("%s", nouveau_client.adresseCommune);
    printf("Adresse - Avenue : ");
    scanf("%s", nouveau_client.adresseAvenue);
    printf("Adresse - Numéro de parcelle : ");
    scanf("%s", nouveau_client.adresseNumeroParcelle);
    printf("Numéro de téléphone : ");
    scanf("%s", nouveau_client.numeroTelephone);
