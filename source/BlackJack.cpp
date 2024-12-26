#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <sstream>

#include "../include/menu.hpp"
#include "../include/blackjack.hpp"

bool isDigit1(std::string str){
    for (unsigned int i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }   
    }
    return true;
}

int convertStringToDigit1(const std::string& str) {
    std::istringstream iss(str);
    int nombre;
    iss >> nombre;
    return nombre;
}

int menuPrincipal1(){
    std::string choix;

    do {
        clearConsole();
        
        std::cout << "Jouer - 1 " << std::endl;
        std::cout << "Regles - 2 " << std::endl;
        std::cout << "Menu Principal - 3" << std::endl;
        std::cout << "\nEntrez votre choix : ";
        std::cin >> choix;

        if (!isDigit1(choix)){
            std::cout << "\nVeuillez choisir un nombre." << std::endl;
            Sleep(2000);
            continue;
        }

        int choixInt = convertStringToDigit1(choix);

        if (choixInt < 1 || choixInt > 3){
            std::cout << "\nVeuillez choisir un nombre valide (1, 2 ou 3). " << std::endl;
            Sleep(2000);
        }
        else {
            std::cout << std::endl;
            return choixInt;
        }
        
    } while (true);
}

void regle1(){
    clearConsole();
    std::string entrer = "";

    std::cout << "#########################################################" << std::endl;
    std::cout << "#                     Regles du jeu :                   #" << std::endl;
    std::cout << "#########################################################" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#  Le blackjack se joue contre un croupier.             #" << std::endl;
    std::cout << "#  Le but est d'obtenir une main dont la valeur est     #" << std::endl;
    std::cout << "#  la plus proche possible de 21 sans la depasser.      #" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#  - Chaque carte numerique vaut sa valeur faciale.     #" << std::endl;
    std::cout << "#  - Les figures (Valet, Dame, Roi) valent 10 points.   #" << std::endl;
    std::cout << "#  - L'As vaut 1 ou 11, selon ce qui avantage le joueur.#" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#  Si vous atteignez exactement 21 avec deux cartes     #" << std::endl;
    std::cout << "#  (un As et une figure ou un 10), vous faites          #" << std::endl;
    std::cout << "#  'Blackjack' et gagnez immediatement, sauf si         #" << std::endl;
    std::cout << "#  le croupier a aussi un Blackjack, dans ce cas        #" << std::endl;
    std::cout << "#  c'est une egalite.                                   #" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#  Options de jeu :                                     #" << std::endl;
    std::cout << "#  - 'Tirer' pour recevoir une nouvelle carte.          #" << std::endl;
    std::cout << "#  - 'Rester' pour conserver votre main actuelle.       #" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#  Le croupier joue apres vous :                        #" << std::endl;
    std::cout << "#  - Il tire des cartes jusqu'a atteindre au moins 17.  #" << std::endl;
    std::cout << "#  - Si sa main depasse 21, vous gagnez.                #" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#                     Bonne chance !                    #" << std::endl;
    std::cout << "#########################################################" << std::endl;


    std::cout << "Tapez sur Entrer pour revenir au menu principal... ";
    std::cin.ignore();
    std::cin.get();
    clearConsole();
}

std::string tirerCarte(int& totalPoints) {
    std::map<std::string, int> cartes = {
        {"As de piques", 11}, {"Deux de piques", 2}, {"Trois de piques", 3}, {"Quatre de piques", 4}, {"Cinq de piques", 5},
        {"Six de piques", 6}, {"Sept de piques", 7}, {"Huit de piques", 8}, {"Neuf de piques", 9}, {"Dix de piques", 10},
        {"Valet de piques", 10}, {"Dame de piques", 10}, {"Roi de piques", 10}, {"As de carreaux", 11}, {"Deux de carreaux", 2},
        {"Trois de carreaux", 3}, {"Quatre de carreaux", 4}, {"Cinq de carreaux", 5}, {"Six de carreaux", 6}, {"Sept de carreaux", 7},
        {"Huit de carreaux", 8}, {"Neuf de carreaux", 9}, {"Dix de carreaux", 10}, {"Valet de carreaux", 10}, {"Dame de carreaux", 10},
        {"Roi de carreaux", 10}, {"As de coeurs", 11}, {"Deux de coeurs", 2}, {"Trois de coeurs", 3}, {"Quatre de coeurs", 4},
        {"Cinq de coeurs", 5}, {"Six de coeurs", 6}, {"Sept de coeurs", 7}, {"Huit de coeurs", 8}, {"Neuf de coeurs", 9},
        {"Dix de coeurs", 10}, {"Valet de coeurs", 10}, {"Dame de coeurs", 10}, {"Roi de coeurs", 10}, {"As de trefles", 11},
        {"Deux de trefles", 2}, {"Trois de trefles", 3}, {"Quatre de trefles", 4}, {"Cinq de trefles", 5}, {"Six de trefles", 6},
        {"Sept de trefles", 7}, {"Huit de trefles", 8}, {"Neuf de trefles", 9}, {"Dix de trefles", 10}, {"Valet de trefles", 10},
        {"Dame de trefles", 10}, {"Roi de trefles", 10}
    };

    std::vector<std::string> cartesValeur;

    for (const auto& pair : cartes) {
        cartesValeur.push_back(pair.first);
    }

    int numCarte = rand() % 52; // Tire une carte entre 0 et 51
    std::string carteTiree = cartesValeur[numCarte];
    int valeurCarte = cartes[carteTiree];

    if (valeurCarte == 11 && totalPoints + valeurCarte > 21) {
        valeurCarte = 1; // Si ajouter 11 ferait dépasser 21, on utilise la valeur 1 pour l'As
    }

    totalPoints += valeurCarte;
    return carteTiree;
}

void affichageMontantMise(int montant, int mise){
    std::cout << "Montant actuel: " << montant << " euros " << std::endl;
    std::cout << "Mise en jeu: " << mise << " euros " << std::endl;
    std::cout << std::endl;
}

void afficherMain(const std::vector<std::string>& mainCartes, int totalPoints, const std::string& nom) {
    std::cout << nom;
    for (const auto& carte : mainCartes) {
        std::cout << carte << " "; // Affiche chaque carte
    }
    std::cout << "(Total : " << totalPoints << ")" << std::endl; // Affiche le total
}

void tourCroupier(std::vector<std::string>& mainCroupier, std::vector<std::string>& mainJoueur, int& totalPointsCroupier, int& totalPointsJoueur, int montant, int mise) {
    if (totalPointsCroupier >= 17){
        clearConsole();

        affichageMontantMise(montant, mise);

        // Affichage des mains et des points
        afficherMain(mainJoueur, totalPointsJoueur, "Vous avez : ");
        afficherMain(mainCroupier, totalPointsCroupier, "Le croupier a : ");
        std::cout << std::endl;

        std::cout << "Le croupier ne peut pas tirer de carte" << std::endl;

        Sleep(1000);

        return;
    }
    while (totalPointsCroupier < 17) {
        clearConsole();

        affichageMontantMise(montant, mise);

        // Affichage des mains et des points
        afficherMain(mainJoueur, totalPointsJoueur, "Vous avez : ");
        afficherMain(mainCroupier, totalPointsCroupier, "Le croupier a : ");
        std::cout << std::endl;

        std::string carteTiree = tirerCarte(totalPointsCroupier);
        mainCroupier.push_back(carteTiree);

        std::cout << "Le croupier a tire la carte : " << carteTiree << std::endl;
        afficherMain(mainCroupier, totalPointsCroupier, "Le croupier a : ");
                
        Sleep(1000);
    }
}

void affichageResultat(int totalPointsJoueur, int totalPointsCroupier, int& montant, int& mise) {
    Sleep(1000);
    // Affichage final des totaux
    if (totalPointsJoueur == 21 && totalPointsCroupier == 21) {
        // Si les deux ont un BlackJack, c'est une égalité
        std::cout << "\n\033[1;37mEgalite avec BlackJack !\033[0m" << std::endl;
    } 
    else if (totalPointsJoueur == 21) {
        // Si le joueur a 21 mais pas le croupier
        std::cout << "\n\033[1;32mBlackJack du joueur !\033[0m" << std::endl;
        montant += mise * 1.5;
    } 
    else if (totalPointsCroupier == 21) {
        // Si le croupier a 21 mais pas le joueur
        std::cout << "\n\033[1;31mBlackJack de la banque\033[0m" << std::endl;
        montant -= mise;
    } 
    else {
        if (totalPointsJoueur > 21) {
            // Si le joueur dépasse 21, il perd immédiatement
            std::cout << "\n\033[1;31mVous avez perdu\033[0m" << std::endl;
            montant -= mise;
        } 
        else if (totalPointsCroupier > 21) {
            // Si le croupier dépasse 21, le joueur gagne
            std::cout << "\n\033[1;32mVous avez gagne la manche\033[0m" << std::endl;
            montant += mise;
        } 
        else if (totalPointsJoueur > totalPointsCroupier) {
            std::cout << "\n\033[1;32mVous avez gagne la manche\033[0m" << std::endl;
            montant += mise;
        } 
        else if (totalPointsJoueur < totalPointsCroupier) {
            std::cout << "\n\033[1;31mVous avez perdu\033[0m" << std::endl;
            montant -= mise;
        } 
        else {
            // Si les points sont égaux (sans BlackJack)
            std::cout << "\n\033[1;37mEgalite\033[0m" << std::endl;
        }
    } 
}

void debutPartie(std::vector<std::string>& mainJoueur, std::vector<std::string>& mainCroupier, int& totalPointsJoueur, int& totalPointsCroupier) {
    // Tirage des cartes pour le joueur
    mainJoueur.push_back(tirerCarte(totalPointsJoueur));
    mainJoueur.push_back(tirerCarte(totalPointsJoueur));

    // Tirage des cartes pour le croupier
    mainCroupier.push_back(tirerCarte(totalPointsCroupier));
    mainCroupier.push_back(tirerCarte(totalPointsCroupier));
}

void tourJoueur(std::vector<std::string>& mainJoueur, std::vector<std::string>& mainCroupier, int& totalPointsJoueur, int& totalPointsCroupier, int montant, int mise) {
    std::string answer = ""; // Initialisation de l'option par défaut pour tirer
    while (answer != "r" && totalPointsJoueur < 21) {
        clearConsole();

        affichageMontantMise(montant, mise);
        
        // Affichage des mains et des points
        afficherMain(mainJoueur, totalPointsJoueur, "Vous avez : ");
        afficherMain(mainCroupier, totalPointsCroupier, "Le croupier a : ");
        
        std::cout << std::endl;
        std::cout << "Voulez-vous tirer une nouvelle carte ? " << std::endl;
        std::cout << "Tirer - t" << std::endl;
        std::cout << "Rester - r" << std::endl;
        std::cout << "\nEntrez votre choix : ";
        std::cin >> answer; // Lecture de l'input de l'utilisateur
        std::cout << std::endl;

        if (answer == "r") {
            // Si le joueur choisit "r", on arrête le tirage
            break;
        } else if (answer == "t") {
            // Si le joueur choisit "t", il tire une nouvelle carte
            std::string carteTiree = tirerCarte(totalPointsJoueur);
            mainJoueur.push_back(carteTiree);
            std::cout << "Vous avez tire la carte : " << carteTiree << std::endl;
            Sleep(2000);

            // Si le joueur dépasse 21 après avoir tiré une carte, on arrête immédiatement
            if (totalPointsJoueur > 21) {
                clearConsole();
                break;
            }
        }
        else {
            std::cout << "Veuillez entrer soit t ou r. " << std::endl;
            std::cout << std::endl;
            Sleep(2000);
        }
    }
}

int rejouer(int& montant){
    std::string replay;

    do {
        clearConsole();

        std::cout << "Montant actuel: " << montant << " euros " << std::endl;
   
        std::cout << "\nRejouer - 1 " << std::endl;
        std::cout << "Arreter - 2 " << std::endl;
        std::cout << "\nEntrez votre choix : ";
        std::cin >> replay;

        if (!isDigit1(replay)){
            std::cout << "\nErreur ! Veuillez choisir un nombre et/ou positif." << std::endl;
            Sleep(2000);
            continue;
        }

        int replayInt = convertStringToDigit1(replay);

        if (replayInt < 1 || replayInt > 3){
            std::cout << "\nErreur ! Veuillez choisir un nombre valide (1 ou 2). " << std::endl;
            Sleep(2000);
        }
        else {
            std::cout << std::endl;
            return replayInt;
        }
    } while (true);
}

int choixMise(int& montant){
    std::string mise;

    do {
        clearConsole();

        std::cout << "Montant actuel: " << montant << " euros " << std::endl;
        std::cout << "\nEntrez la mise pour cette partie: " << std::endl;
        std::cin >> mise;

        if (!isDigit1(mise)){
            std::cout << "\nErreur ! Veuillez choisir un nombre et/ou positif." << std::endl;
            Sleep(2000);
            continue;
        }

        int miseInt = convertStringToDigit1(mise);

        if (miseInt > montant) {
            std::cout << "\nErreur ! Vous avez choisi une mise superieure à votre montant disponible ! " << std::endl;
            Sleep(2000);
        }
        else if (miseInt == 0){
            std::cout << "\nErreur ! Vous avez choisi une mise nulle ! " << std::endl;
            Sleep(2000);
        }
        else {
            std::cout << std::endl;
            return miseInt;
        }
    } while (true);
}

int choixMontant(){
    std::string montant;

    do {
        clearConsole();

        std::cout << "Entrez le montant de depart: ";
        std::cin >> montant;

        if (!isDigit1(montant)){
            std::cout << "\nErreur ! Veuillez choisir un nombre et/ou positif." << std::endl;
            Sleep(2000);
            continue;
        }

        int montantInt = convertStringToDigit1(montant);

        if (montantInt == 0){
            std::cout << "\nErreur ! Vous avez choisi un montant nulle ! " << std::endl;
            Sleep(2000);
        }
        else {
            std::cout << std::endl;
            return montantInt;
        }
    } while (true);
}

int blackjack(){
    srand(static_cast<unsigned int>(time(NULL))); // Initialise le générateur de nombres aléatoires

    // Déclaration des variables
    int choix;
    int replay;
    int montantInitial = 0;
    int montant = 0;
    int mise = 0;
    float recordDuMonde;
    float scoreActuel;
    int totalPointsJoueur = 0;
    int totalPointsCroupier = 0;
    std::vector<std::string> mainJoueur;
    std::vector<std::string> mainCroupier;

    while (true) {
        choix = menuPrincipal1();
        clearConsole();

        if (choix == 1) {
            // Initialisation et validation du montant de départ
            montant = choixMontant();
            montantInitial = montant;

            clearConsole();

            while (montant > 0) {
                mise = choixMise(montant);

                clearConsole();
                affichageMontantMise(montant, mise);

                if (montant != 0) {
                    // Initialisation de la main pour chaque partie
                    mainJoueur.clear();
                    mainCroupier.clear();
                    totalPointsJoueur = 0;
                    totalPointsCroupier = 0;

                    // Début de la partie avec tirage initial
                    debutPartie(mainJoueur, mainCroupier, totalPointsJoueur, totalPointsCroupier);

                    // Tour du joueur
                    tourJoueur(mainJoueur, mainCroupier, totalPointsJoueur, totalPointsCroupier, montant, mise);

                    // Tour du croupier
                    tourCroupier(mainCroupier, mainJoueur, totalPointsCroupier, totalPointsJoueur, montant, mise);

                    // Affichage du résultat final
                    affichageResultat(totalPointsJoueur, totalPointsCroupier, montant, mise);
                    Sleep(2000);
                    std::cout << std::endl;
                }

                // Si le montant est à 0, le joueur ne peut plus miser
                if (montant == 0) {
                    clearConsole();
                    std::cout << "\033[1;31mVous n'avez plus d'argent a miser ! :( \nAu revoir !\033[0m" << std::endl;
                    Sleep(2000);
                    break;
                }

                Sleep(5000);

                // Demande si le joueur veut rejouer
                replay = rejouer(montant);

                clearConsole();
                Sleep(2000);

                if (replay == 2) {
                    break;
                }
            }
        }
        else if (choix == 2) {
            regle1();
            continue;
        }
        else if (choix == 3) {
            menu();
            break;
        }
    }
    return 0;
}
