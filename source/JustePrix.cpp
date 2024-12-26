// Importation des librairies nécessaires
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <sstream>

#include "../include/menu.hpp"
#include "../include/juste_prix.hpp"

// Fonction qui verifie si le string comporte que des nombres ou pas
bool isDigit(std::string str){
    for (unsigned int i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }   
    }
    return true;
}

// Fonction qui convertie un string en int grâce à la librairie sstream
int convertStringToDigit(const std::string& str) {
    std::istringstream iss(str);
    int nombre;
    iss >> nombre;
    return nombre;
}

// Affichage du menu principal
int menuPrincipal(){
    clearConsole();
    int choix = 0;
    std::cout << "Jouer - 1 " << std::endl;
    std::cout << "Regles - 2 " << std::endl;
    std::cout << "Menu Principal - 3" << std::endl;

    do {
        std::cout << "Entrez votre choix : ";
        std::cin >> choix;
        if (choix != 1 && choix != 2 && choix != 3){
            std::cout << "Veuillez choisir entre 1, 2 ou 3. " << std::endl;
        }
    } while (choix != 1 && choix != 2 && choix != 3);

    std::cout << std::endl;
    clearConsole();

    return choix;
}

// Affichage des règles
void regleJeuNiveau() {
    clearConsole();
    std::string entrer = "";

    std::cout << "#########################################################" << std::endl;
    std::cout << "#                     Regles du jeu :                   #" << std::endl;
    std::cout << "#########################################################" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#  1. Un prix aleatoire sera genere entre 0 et 100.     #" << std::endl;
    std::cout << "#  2. Vous devez deviner ce prix en un nombre limite    #" << std::endl;
    std::cout << "#     de tentatives.                                    #" << std::endl;
    std::cout << "#  3. Apres chaque tentative, vous recevrez un indice : #" << std::endl;
    std::cout << "#     - Si votre nombre est trop bas, il vous sera      #" << std::endl;
    std::cout << "#       indique que le prix est plus grand.             #" << std::endl;
    std::cout << "#     - Si votre nombre est trop haut, il vous sera     #" << std::endl;
    std::cout << "#       indique que le prix est plus petit.             #" << std::endl;
    std::cout << "#  4. Essayez de deviner le prix dans le nombre         #" << std::endl;
    std::cout << "#     de tentatives imparties !                         #" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#########################################################" << std::endl;

    std::cout << std::endl;

    std::cout << "#########################################################" << std::endl;
    std::cout << "#                       Les Niveaux                     #" << std::endl;
    std::cout << "#########################################################" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#  1. Il existe 4 niveaux disponibles :                 #" << std::endl;
    std::cout << "#     - Niveau facile    (20 essais)                    #" << std::endl;
    std::cout << "#     - Niveau moyen     (10 essais)                    #" << std::endl;
    std::cout << "#     - Niveau difficile (5 essais)                     #" << std::endl;
    std::cout << "#     - Niveau hardcore  (3 essais)                     #" << std::endl;
    std::cout << "#                                                       #" << std::endl;
    std::cout << "#########################################################" << std::endl;


    std::cout << std::endl;
    std::cout << "Tapez sur Entrer pour revenir au menu principal... ";
    std::cin.ignore();
    std::cin.get();
    clearConsole();
}

// Fonction qui s'occupe du choix du niveau
int choixNiveau(){
    std::string niveau;

    do {
        clearConsole();

        std::cout << "Niveau facile (20 essais) - 1\n";
        std::cout << "Niveau moyen (10 essais) - 2\n";
        std::cout << "Niveau difficile (5 essais) - 3\n";
        std::cout << "Niveau hardcore (3 essais) - 4\n";

        std::cout << "\nEntrez votre niveau: ";
        std::cin >> niveau;

        if (!isDigit(niveau)){
            std::cout << "\nErreur ! Veuillez choisir un nombre et/ou positif." << std::endl;
            Sleep(2000);
            continue;
        }

        int niveauInt = convertStringToDigit(niveau);

        if (niveauInt < 1 || niveauInt > 4){
            std::cout << "\nErreur ! Vous n'avez pas choisi de niveau ! " << std::endl;
            Sleep(2000);
        }
        else {
            clearConsole();
            return niveauInt;
        }
    } while (true);
}

// Fontion qui s'occupe de chaque tentative de l'utilisateur
int tentativeChoix(int& essaisRestants, int& compteur, int tentativePrecedente, int prix){
    std::string tentative;

    do
    {
        clearConsole();

        std::cout << "Il vous reste " << essaisRestants << " tentatives.\n";
        
        if (compteur > 0){
            if (tentativePrecedente < prix) {
                std::cout << "Le prix est plus grand que " << tentativePrecedente << std::endl;
            }
            else if (tentativePrecedente > prix) {
                std::cout << "Le prix est plus petit que " << tentativePrecedente << std::endl;
            }
        }
        std::cout << "\nEntrez votre nombre : ";
        std::cin >> tentative;

        if (!isDigit(tentative)){
            std::cout << "\nErreur ! Veuillez choisir un nombre et/ou positif." << std::endl;
            Sleep(2000);
            continue;
        }

        int tentativeInt = convertStringToDigit(tentative);

        if (tentativeInt < 0 || tentativeInt > 100) {
            std::cout << "Veuillez entrer un nombre entre 0 et 100." << std::endl;
            Sleep(2000);
        }
        else{
            std::cout << std::endl;
            
            return tentativeInt;
        }
    } while (true);
}

// Fonction qui comporte toutes les manches donc les tentatives du joueur dans le jeu
bool Jeu(int& essaisRestants, int prix, int& compteur) {
    int tentative;
    
    tentative = tentativeChoix(essaisRestants, compteur, tentative, prix);

    if (tentative == prix) {
        clearConsole();

        std::cout << "\033[1;32mFelicitations !\033[0m Vous avez devine le prix !" << std::endl;

        Sleep(3000);

        return true;
    }

    compteur++;

    essaisRestants--;
    return false;
}

// Fonction principale qui gère la partie entière
void jeuEssais(int essaisRestants, int prix, int& compteur) {
    std::cout << "Essayez de deviner le prix !" << std::endl;

    while (essaisRestants > 0) {
        if (Jeu(essaisRestants, prix, compteur)) {
            break;
        }
    }

    if (essaisRestants == 0) {
        clearConsole();

        std::cout << "Desole, vous avez epuise vos tentatives. Le prix etait : " << prix << std::endl;

        Sleep(3000);
    }
}

// Fonction qui gère le replay du jeu s'il veut
int rejouer(){
    std::string replay;

    do {
        clearConsole();
   
        std::cout << "Rejouer - 1 " << std::endl;
        std::cout << "Arreter - 2 " << std::endl;
        std::cout << "\nEntrez votre choix : ";
        std::cin >> replay;

        if (!isDigit(replay)){
            std::cout << "\nErreur ! Veuillez choisir un nombre et/ou positif." << std::endl;
            Sleep(2000);
            continue;
        }

        int replayInt = convertStringToDigit(replay);

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

// Fonction qui demande à l'utilisateur s'il veut changer de niveau que si un premiere manche a été déjà faite
int nouveauNiveauChoix(int& niveau){
    std::string nouveauNiveau;

    do {
        clearConsole();

        if (niveau == 1)
        {
            std::cout << "Voulez-vous changer de niveau pour plus de difficulte ? " << std::endl;
        }
        else if (niveau == 4)
        {
            std::cout << "Voulez-changer de niveau pour plus de facilite ? " << std::endl;
        }
        else 
        {
            std::cout << "Voulez-changer de niveau pour plus de difficulte ou au contraire plus de facilite ? " << std::endl;
        }

        std::cout << "\nOui - 1 " << std::endl;
        std::cout << "Non - 2 " << std::endl;
        std::cout << "\nEntrez votre choix : ";
        std::cin >> nouveauNiveau;

        if (!isDigit(nouveauNiveau)){
            std::cout << "\nErreur ! Veuillez choisir un nombre et/ou positif." << std::endl;
            Sleep(2000);
            continue;
        }

        int nouveauNiveauInt = convertStringToDigit(nouveauNiveau);

        if (nouveauNiveauInt < 1 || nouveauNiveauInt > 2){
            std::cout << "\nErreur ! Veuillez choisir un nombre valide (1 ou 2). " << std::endl;
            Sleep(2000);
        }
        else {
            std::cout << std::endl;
            return nouveauNiveauInt;
        }
    } while (true);
}

// Fonction qui change de niveau
int changerNiveau(int& niveau){
    int nouveauNiveau;

    clearConsole();

    if (nouveauNiveauChoix(niveau) == 1)
    {
        nouveauNiveau = choixNiveau();
        return nouveauNiveau;
    }
    
    clearConsole();

    return niveau;
}

// Fonction qui retourne le nombre d'essai que l'utilisateur va avoir en fonction du niveau qu'il a choisi
int obtenirEssaisParNiveau(int& niveau){
    if (niveau == 1) 
    {
        return 20;
    } 
    else if (niveau == 2) 
    {
        return 10;
    } 
    else if (niveau == 3) 
    {
        return 5;
    } 
    else if (niveau == 4) 
    {
        return 3;
    } 

    std::cerr << "Niveau non valide. Le jeu va se terminer." << std::endl;
    return 0;
}

// Fonction principale
int juste_prix(){
    std::srand(static_cast<unsigned int>(std::time(0)));

    int choix;
    int niveau;
    int replay;

    while (true) {
        int compteur = 0;
        
        choix = menuPrincipal();

        if (choix == 1) {
            niveau = choixNiveau();

            do {
                int prix = std::rand() % 101;

                int compteurManche = 0;

                if (compteur != 0)
                {
                    niveau = changerNiveau(niveau);
                }

                int essaisRestants = obtenirEssaisParNiveau(niveau);

                jeuEssais(essaisRestants, prix, compteurManche);

                replay = rejouer();

                clearConsole();

                compteur++;
            } while (replay == 1);
        } else if (choix == 2) {
            regleJeuNiveau();
        } else if (choix == 3) {
            menu();
            break;
        }
    }

    return 0;
}