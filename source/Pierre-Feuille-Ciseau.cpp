/*####################################################################################
Créateur : Th3Ph3nix3
Date de dernière mise à jour : 17/11/2024

Description : Ce programme est le jeu du pierre feuille ciseau qui sera executé lors 
              du menu si il est selectionné par le joueur. Le jeu choisi un nombre au
              hasard entre 1 , 2 et 3 correspondant a pierre, feuille ou ciseau.
              Le joueur choisi le numéro correspondant a l'action qu'il souhaite
              et le programme détermine qui a gagné la manche entre le bot et le 
              joueur et le premier arrivé a 3 points gagne.
              
Mode d'emploi : Le jeu du pierre feuille ciseau est compilé avec le menu donc quand 
                vous executé le jeu.exe vous n'avez qu'a le selctionné dans le menu 
                pour y jouer

                                Amusez vous bien !
####################################################################################*/

#include <iostream>
#include <random>

#include "../include/pfc.hpp"
#include "../include/menu.hpp"

using namespace std;

// Message de début
int regle(char &entrer){
    while (entrer != 'y' && entrer != 'n'){
        clearConsole();
        cout << "#########################################################" << endl;
        cout << "#                    " << "\033[4m" << "Regles du jeu :" << "\033[0m" << "                    #" << endl;
        cout << "#                                                       #" << endl;
        cout << "#  Le but du jeu du pierre feuille ciseau est de battre #" << endl;
        cout << "#  le bot en un certain nombre de coups, celui arrive a #" << endl;
        cout << "#  3 points gagne. En cas d egalite aucun point n'est   #" << endl;
        cout << "#  attribue.                                            #" << endl;
        cout << "#                                                       #" << endl;
        cout << "#  La feuille bat la pierre;                            #" << endl;
        cout << "#  La pierre bat les ciseaux;                           #" << endl;
        cout << "#  Et les ciseaux bat la feuille                        #" << endl;
        cout << "#                                                       #" << endl;
        cout << "#                 Que le meilleur gagne !               #" << endl;
        cout << "#                                                       #" << endl;
        cout << "#########################################################" << endl;

        cout << "Tapez Y pour lancer le jeu sinon taper N pour retourner au menu principal (Y/N) : ";
        cin >> entrer;

        entrer = tolower(entrer);

        if (entrer == 'n'){
            menu();
            return 0;
        }
    }
    return 0;
}

// Sous-programme qui génère le choix aléatoire du bot
void bot(int &choix_bot){

    // Déclaration du moteur et de la distribution
    default_random_engine moteur(random_device{}());
    uniform_int_distribution<int> distribution(1, 3); // 1 pour Pierre, 2 pour Feuille, 3 pour Ciseaux

    // Génération d'un nombre aléatoire
    choix_bot = distribution(moteur);
}

// Sous-programme pour le choix du joueur
void joueur(int &choix_joueur, int &point_joueur, int &point_bot){

    // On demande au joueur de choisir son action
    while (choix_joueur != 1 && choix_joueur != 2 && choix_joueur != 3){
        cout << "Pierre = 1, Feuille = 2 et Ciseaux = 3" << endl;
        cout << "Veuillez entrer votre choix : ";
        cin >> choix_joueur;

        if (choix_joueur != 1 && choix_joueur != 2 && choix_joueur != 3){
            clearConsole();
            cout << "Score actuel - Vous: " << point_joueur << " | Bot: " << point_bot << endl;
            cout << endl;
        }
    }
}

// Sous-programme du résultat de l'affrontement entre les deux joueurs
void affrontement(int &choix_bot, int &choix_joueur, int &point_joueur, int &point_bot){

    //On libère l'écran
    clearConsole();

    // Même action des deux joueurs
    if (choix_bot == choix_joueur){
        cout << "Egalite ! Personne ne marque de point." << endl;
    }

    // Cas où le joueur gagne
    else if ((choix_joueur == 1 && choix_bot == 3) ||  // Pierre bat Ciseaux
             (choix_joueur == 2 && choix_bot == 1) ||  // Feuille bat Pierre
             (choix_joueur == 3 && choix_bot == 2)) {  // Ciseaux bat Feuille
        cout << "Vous avez gagne ce tour !" << endl;
        point_joueur += 1;
    }

    // Cas où le bot gagne
    else {
        cout << "Le bot a gagne ce tour !" << endl;
        point_bot += 1;
    }
    
    // Affichage des scores
    cout << "Score actuel - Vous: " << point_joueur << " | Bot: " << point_bot << endl;
    cout << endl;
}

// Sous-programme gérant le jeu
int jeu(){

    // Initialisation des points des deux joueurs
    int point_joueur = 0, point_bot = 0;

    // On fait jouer jusqu'à ce que le joueur ou le bot ait 3 points
    while (point_bot != 3 && point_joueur != 3){

        // On fait choisir le bot son action
        int choix_bot = 0;
        bot(choix_bot);

        // On fait choisir au joueur son action
        int choix_joueur = 0;
        joueur(choix_joueur, point_joueur, point_bot);

        // Affrontement entre bot et joueur
        affrontement(choix_bot, choix_joueur, point_joueur, point_bot);
    }

    // Résultat final
    char entrer = ' ';
    if (point_joueur == 3) {
        cout << "#############################################################" << std::endl;
        cout << "#                  " << "\033[4m" << "Felicitation vous avez gagner !" << "\033[0m" << "          #" << endl;
        cout << "#                                                           #" << std::endl;
        cout << "#  J'espere que le jeu vous a plus ! Voulez vous rejouer ?  #" << std::endl;
        cout << "#                                                           #" << std::endl;
        cout << "#############################################################" << std::endl;
    }
    else {
        cout << "#############################################################" << std::endl;
        cout << "#                  " << "\033[4m" << "Dommage vous avez perdu !" << "\033[0m" << "                #" << endl;
        cout << "#                                                           #" << std::endl;
        cout << "#  J'espere que le jeu vous a plus ! Voulez vous retenter ? #" << std::endl;
        cout << "#                                                           #" << std::endl;
        cout << "#############################################################" << std::endl;
    }

    while (entrer != 'n' && entrer != 'y'){
        cout << "Tapez Y pour rejouer au pendu sinon taper N pour retourner au menu principal (Y/N) : ";
        cin >> entrer;

        entrer = tolower(entrer);

        if (entrer == 'n'){
            menu();
            return 0;
        }
    }
    return 0;
}

int PFC(){

    // On affiche le menu avant de commencer le jeu
    debut:              // Goto pour recommencer la partie
    char entrer = ' ';
    regle(entrer);

    // On libère l'écran
    clearConsole();

    // Si dans le menu on a tapé Y on commence le jeu
    if ( entrer == 'y' ){
        // On joue au jeu
        jeu();
        goto debut;
    }

    // Si on a tapé N on arrête le jeu
    if ( entrer == 'n' ){
        menu();
        return 0; 
    }
    return 0; 
}