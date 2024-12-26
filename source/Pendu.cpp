/*####################################################################################
Créateur : Th3Ph3nix3
Date de dernière mise à jour : 17/11/2024

Description : Ce programme est le jeu du pendu qui sera executé lors du menu si il
              est selectionné par le joueur. Le jeu sélectionne un mot dans un fichier
              texte, le cache et le fait deviner au joueur avec un nombre d'erreur 
              possible spécifique.
              
Mode d'emploi : Le jeu du pendu est compilé avec le menu donc quand vous executé le
                jeu.exe vous n'avez qu'a le selctionné dans le menu pour y jouer

                                Amusez vous bien !
####################################################################################*/

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <cctype> // pour tolower()

#include "../include/pendu.hpp"
#include "../include/menu.hpp"

using namespace std;

//Sous-programme comptes nombre mot possible a faire deviner
int nombreMot() {
    ifstream liste_mot("../txt/mot_a_deviner.txt");  // Ouvre le fichier "mot_a_deviner.txt"
    
    // Vérifie si le fichier est ouvert correctement
    if (liste_mot.is_open()) {
        string ligne;
        int nombre_mot = 0;
        
        // Parcourt le fichier ligne par ligne + compte le nombre de mots
        while (getline(liste_mot, ligne)) {
            nombre_mot += 1;
        }
        liste_mot.close();  // Ferme le fichier après la lecture
        //cout << "Nombre de mots : " << nombre_mot << endl;              //Test a enlever
        return nombre_mot;  // Retourne le nombre de mots
    } else {
        // Si le fichier ne s'ouvre pas, affiche un message d'erreur
        cout << "Jeu HS, requiert l'attention d'un administrateur, code 1" << endl;
        return -1;  // Retourne une erreur
    }
}

//Sous-programme pour tirer un nombre au hasard
int ligneAleatoire(int max){

    // Déclaration du moteur et de la distribution
    default_random_engine moteur(random_device{}());
    uniform_int_distribution<int> distribution(1, max);

    // Génération d'un nombre aléatoire
    int nombre_aleatoire = distribution(moteur);
    //cout << "Nombre aleatoire : " << nombre_aleatoire << endl;         //Test a enlever

    return nombre_aleatoire;
}

//Sous-programme pour renvoyer la ligne choisie aléatoirement
string obtenirLigne(int nombre_aleatoire){
    ifstream liste_mot("../txt/mot_a_deviner.txt");

    //Vérifie si le fichier a bien été ouvert
    if (liste_mot.is_open()){
        string ligne;

        //Parcours les ligne jusqu'à celle tirer aléatoirement
        for (int i = 0; i < nombre_aleatoire; ++i){

            //Si la ligne n'existe pas on renvoie une erreur
            if (!getline(liste_mot, ligne)){
                cout << "Erreur, ligne inexistante, code 2" << endl;
                return "ERREUR";
            }
        }
        liste_mot.close();                         //Ferme le fichier après lecture
        //cout << "Mot choisi aleatoirement : " << ligne << endl ;                             //Test a enlever
        return ligne;                              // Retourne la ligne sélectionnée
    } 
    else{
        cout << "Jeu HS, requiert attention administrateur, code 0.1" << endl;  //Si le fichier ne veut pas s'ouvrir on renvoie une erreur
        return "ERREUR";
    }
}

//Sous programme qui va cacher le mot
string cache_mot(string mot_choisi){
    //Compte le nombre de lettre dans le mot
    int nb_caractere = mot_choisi.size();
    string mot_cacher = "";

    //Pour chaque lettre on remplace dans le mot cacher par un _
    for (int i = 0; i < nb_caractere; ++i){
        mot_cacher += "_";
    }
    //cout << "C'est bien cache ? -> " << mot_cacher << endl;     //Test a enlever
    return mot_cacher;
}

//Sous programme qui cherche la lettre dans le mot et qui le met dans le mot cacher
string cherche_caractère(char caractere, string mot_choisi, string mot_cacher){
    //On cherche si le caractère est présent dans le mot
    for (int i = 0; i < mot_choisi.size(); ++i){
        if (mot_choisi[i] == caractere){
            mot_cacher[i] = caractere;
        }
    }
    return mot_cacher;
}

// Sous-programme qui détecte si un caractère a déjà été saisi
bool estPresent(char tableau[], char valeur, int taille) {
    for (int i = 0; i < taille; i++) {
        if (tableau[i] == valeur) {
            return true;  // Si la valeur est trouvée, on retourne vrai
        }
    }
    return false;  // Si la valeur n'est pas trouvée, on retourne faux
}
void test(){clearConsole();cout << "Bravo vous avez trouve cet easter egg ! Felicitation ! On espere que nos jeux vous a plus ! Merci d'avoir joue !"<<endl;" by th3ph3nix/whoselevenn/funaki25";Sleep(5000);menu();}
//Sous programme affichant les règles
void regle(){
    clearConsole();
    char entrer = ' ';
    while (entrer != 'y' && entrer != 'n'){
        cout << "#########################################################" << std::endl;
        cout << "#                    " << "\033[4m" << "Regles du jeu :" << "\033[0m" << "                    #" << endl;
        cout << "#                                                       #" << std::endl;
        cout << "#  Le but du jeu du pendu est de trouver le mot cacher  #" << std::endl;
        cout << "#  en un certain nombre de coups, 10 plus precisement   #" << std::endl;
        cout << "#  sinon c'est perdu. Vous pouvez entrer seulement des  #" << std::endl;
        cout << "#  des caracteres sans accents et faisant partis de     #" << std::endl;
        cout << "#  l'alphabet.                                          #" << std::endl;
        cout << "#                     Bonne chance...                   #" << std::endl;
        cout << "#                                                       #" << std::endl;
        cout << "#########################################################" << std::endl;

        cout << "Tapez Y pour lancer le jeu sinon taper N pour retourner au menu principal (Y/N) : ";
        cin >> entrer;

        entrer = tolower(entrer);

        if (entrer == 'n'){
            menu();
        }
    }
    clearConsole();
}

//Sous programme gérant l'affichage du dessin
void dessin(int i){
    if (i == 0){
        cout << "#############" << endl;
        cout << "#           #" << endl;
        cout << "#           #" << endl;
        cout << "#           #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 1){
        cout << "#############" <<endl;
        cout << "#           #" << endl;
        cout << "#           # " << endl;
        cout << "# _         # " << endl;
        cout << "#############" <<endl;
    }
    else if (i == 2){
        cout << "#############" <<endl;
        cout << "#           #" << endl;
        cout << "#           #" << endl;
        cout << "# _ |       #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 3){
        cout << "#############" <<endl;
        cout << "#           #" << endl;
        cout << "#   |       #" << endl;
        cout << "# _ |       #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 4){
        cout << "#############" <<endl;
        cout << "#     -     #" << endl;
        cout << "#   |       #" << endl;
        cout << "# _ |       #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 5){
        cout << "#############" <<endl;
        cout << "#     - O   #" << endl;
        cout << "#   |       #" << endl;
        cout << "# _ |       #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 6){
        cout << "#############" <<endl;
        cout << "#     - O   #" << endl;
        cout << "#   |   |   #" << endl;
        cout << "# _ |       #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 7){
        cout << "#############" <<endl;
        cout << "#     - O   #" << endl;
        cout << "#   | / |   #" << endl;
        cout << "# _ |       #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 8){
        cout << "#############" <<endl;
        cout << "#     - O   #" << endl;
        cout << "#   | / | / #" << endl;
        cout << "# _ |       #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 9){
        cout << "#############" <<endl;
        cout << "#     - O   #" << endl;
        cout << "#   | / | / #" << endl;
        cout << "# _ | /     #" << endl;
        cout << "#############" <<endl;
    }
    else if (i == 10){
        cout << "#############" <<endl;
        cout << "#     - O   #" << endl;
        cout << "#   | / | / #" << endl;
        cout << "# _ | /   / #" << endl;
        cout << "#############" <<endl;
    }
}

// Sous-programme détectant les erreurs de saisie
void erreur(char& caractere, char lettres_dites[], int& j, int i) {
    // Vérifie si le caractère est alphabétique
    while (!isalpha(caractere)) {
        clearConsole();
        cout << endl;
        cout << "Vous avez entrer : " << caractere << endl;
        cout << endl;
        dessin(i);
        cout << endl;
        cout << "Erreur : Le caractere saisi doit etre une lettre alphabetique." << endl;
        cout << "Rentrer un nouveau caractere compatible : ";
        cin >> caractere;
        cout << endl;
    }

    // Vérifie si le caractère n'a pas déjà été dit
    while (estPresent(lettres_dites, caractere, j)) {
        clearConsole();
        cout << endl;
        cout << "Vous avez entrer : " << caractere << endl;
        cout << endl;
        dessin(i);
        cout << endl;
        cout << "Erreur : Ce caractere a deja ete dit. Rentrer un nouveau caractere : ";
        cin >> caractere;
        cout << endl;
    }

    lettres_dites[j++] = tolower(caractere);  // Ajoute le caractère au tableau
}

int pendu(){
    //Etape 0 : On explique les règle
    restart:                                //Si une nouvelle partie est jouer
    regle();

    //Etape 1 : Obtenir le nombre de mots disponibles dans le fichier
    int nombre_mot = nombreMot();

    //Si la liste est vide, affiche message erreur
    if (nombre_mot == 0){
        cout << "Jeu HS, requiert l'attention d'un administrateur, code 0" << endl;
        return 1;                                                      //Sortie du programme en cas d'erreur
    }

    //Etape 2 : Tirer un nombre aléatoire en fonction du nombre de mots
    int nombre_aleatoire = ligneAleatoire(nombre_mot);

    //Etape 3 : Obtenir la ligne correspondant au nombre aléatoire
    string mot_choisi = obtenirLigne(nombre_aleatoire);

    //Vérification si une erreur a été rencontrée lors de la récupération de la ligne
    if (mot_choisi == "ERREUR") {
        cout << "Erreur lors de la récupération de la ligne, fin du programme." << endl;
        return 1;
    }

    //Etape 4 : On cache les caractères du mot
    string mot_cacher = cache_mot(mot_choisi);

    //Etape 5 : On joue
    char lettres_dites[26];
    string lettre_propose = "";
    int j = 0;
    char caractere = 'A';
    cout << "Vous avez 10 vies !" << endl;

    //On donne au joueur le droit a 10 erreurs
    for (int i = 0; i < 10;){
        
        //Tant que le mot n'a pas été trouver
        if (mot_cacher != mot_choisi){
            cout << mot_cacher << endl;
            cout << endl;
            cout << "Entrez une lettre possible : ";
            cin >> caractere;
            caractere = tolower(caractere);
            cout << endl;

            clearConsole();
            cout << endl;
            cout << "Vous avez entrer : " << caractere << endl;
            cout << endl;

            //On enlève les erreurs
            erreur(caractere, lettres_dites, j, i);

            //On affiche si les lettres deja proposé
            lettre_propose = lettre_propose + caractere + "/";

            cout << "Vous avez deja propose : " << lettre_propose << endl;
            cout << endl;

            //On teste si le caractere rentrer est présent dans le mot
            if (mot_choisi.find(caractere) != string::npos){
                mot_cacher = cherche_caractère(caractere, mot_choisi, mot_cacher);
                cout << "Bien joue le caractere est present dans le mot" << endl;
            }

            //Sinon on enlève une vie
            else{
                cout << "Le caractere n'est pas present dans le mot" << endl;
                ++i;
            }

            //On affiche le nombre de vie restant
            if (i != 9){
                cout << "Il vous reste " << 10-i << " vies" << endl;
            }
            else{
                cout << "Il vous reste 1 vie" << endl;
            }
            lettres_dites[j] = caractere;
        }

        //Si le mot a été trouver on dit qu'on a gagner
        else{
            clearConsole();
            char entrer = ' ';
            while (entrer != 'y' && entrer != 'n'){
                cout << "#############################################################" << std::endl;
                cout << "#               " << "\033[4m" << "Felicitation vous avez gagner !" << "\033[0m" << "             #" << endl;
                cout << "#                                                           #" << std::endl;
                cout << "#  J'espere que le jeu vous a plus ! Voulez vous rejouer ?  #" << std::endl;
                cout << "#                                                           #" << std::endl;
                cout << "#############################################################" << std::endl;

                cout << "Tapez Y pour rejouer au pendu sinon taper N pour retourner au menu principal (Y/N) : ";
                cin >> entrer;

                entrer = tolower(entrer);

                if (entrer == 'n'){
                    menu();
                    return 0;
                }
                else{
                    goto restart;
                }

            }
        }

        //En fonction de i on change le dessin
        cout << endl;
        dessin(i);
        cout << endl;
    }

    //Si le mot n'a pas été trouver et qu'on a plus de vie on dit qu'on a perdu
    char restart = ' ';
    while (restart != 'n' && restart != 'y'){
        cout << "#############################################################" << std::endl;
        cout << "#                  " << "\033[4m" << "Dommage vous avez perdu !" << "\033[0m" << "                #" << endl;
        cout << "#                                                           #" << std::endl;
        cout << "#  J'espere que le jeu vous a plus ! Voulez vous retenter ? #" << std::endl;
        cout << "#                                                           #" << std::endl;
        cout << "#############################################################" << std::endl;
        cout << endl;
        cout << "Tapez Y pour retenter votre chance sinon taper N pour retourner au menu principal (Y/N) : ";
        cin >> restart;

        restart = tolower(restart);
        if (restart == 'n'){
            menu();
            return 0;
        }

        if (restart == 'y'){
            goto restart;
        }
    }
    return 0;
}