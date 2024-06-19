Ce projet implémente un système de gestion bancaire en langage C, permettant la création, la gestion, et la suppression de comptes bancaires ainsi que la réalisation de transactions entre ces comptes.
Fonctionnalités

    Créer un compte client : Permet de créer un nouveau compte en saisissant les informations personnelles du client.
    Lister les comptes : Affiche la liste de tous les comptes existants, triés par date de création. Cette fonctionnalité nécessite une authentification administrateur.
    Effectuer des opérations sur le compte :
        Transférer des fonds : Permet de transférer de l'argent d'un compte à un autre.
        Dépôt : Permet d'ajouter de l'argent à un compte.
        Retrait : Permet de retirer de l'argent d'un compte.
        Voir les transactions : Affiche l'historique des transactions d'un compte spécifique.
    Supprimer un compte : Permet de supprimer un compte après authentification administrateur.
    Sauvegarde et Chargement : Sauvegarde automatique des comptes dans un fichier binaire et chargement des comptes au démarrage.


Menu Principal

Après avoir lancé le programme, le menu principal propose les options suivantes :

    Créer un compte
    Lister les comptes
    Opérations sur le compte
    Supprimer un compte
    Quitter

Création d'un compte

Lors de la création d'un compte, le programme demande les informations suivantes :

    Nom
    Postnom
    Prénom
    Date de naissance
    Lieu de naissance
    Adresse actuelle
    Numéro de téléphone
    Montant du dépôt initial

Liste des comptes

Pour lister les comptes, il est nécessaire d'entrer le mot de passe administrateur. Par défaut, le mot de passe est 1234.
Opérations sur le compte

Lors de l'exécution des opérations sur le compte, les options suivantes sont proposées :

    Transférer des fonds : Nécessite le numéro de compte du receveur et le montant à transférer.
    Dépôt : Nécessite le montant à déposer.
    Retrait : Nécessite le montant à retirer.
    Voir vos transactions : Affiche l'historique des transactions du compte.

Suppression d'un compte

Pour supprimer un compte, il est nécessaire d'entrer le mot de passe administrateur.


Ce projet a été réalisé par :

    MBAYA-KOLELA Patrick
    MBOMBO-KALALA Henock
    MBIYA-BANZA Josue
    MATANDA-MATANDA Idriss
