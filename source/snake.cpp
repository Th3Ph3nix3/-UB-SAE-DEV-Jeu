#include <conio.h>
#include <iostream>
#include <windows.h>

#include "../include/snake.hpp"
#include "../include/menu.hpp"

using namespace std;

//Variables globales du jeu 

//Couleurs
const string RED ="\033[31m";
const string GREEN="\033[32m";
const string RESET="\033[0m";

//Hauteur et largeur de la fronctière
const int width = 80;
const int height = 20;

//Coordonnées de la tête du serpent 
int x, y;

//Coordonnées de la nouriture
int fruitX, fruitY;

// variable to store the score of he player
int playerScore;

//Tableau pour stocker les coordonnées de la queue du serpent sur l'axe des X et l'axe des Y
int queueSnakeX[100], queueSnakeY[100];

//Variable pour stocker la taille de la queue serpent 
int snakeTaille;

//énumération pour stocker les mouvements du serpent
enum snakeDirections{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
}; 
snakeDirections sDir;

// variable booléenne permettant de vérifier si le jeu est terminé ou non
bool isGameOver;

//règles du jeu
void gameRegle1(){
    clearConsole();
    cout << "===== Regles du jeu Snake =====" << endl;
    cout << "1. Le but du jeu est de manger la nourriture (o) pour obtenir des points." << endl;
    cout << "2. Utilisez les touches suivantes pour deplacer le serpent :" << endl;
    cout << "   - 'z' : Haut" << endl;
    cout << "   - 's' : Bas" << endl;
    cout << "   - 'q' : Gauche" << endl;
    cout << "   - 'd' : Droite" << endl;
    cout << "3. Chaque fois que vous mangez une nourriture, votre score augmente de 5 points." << endl;
    cout << "4. Si vous heurtez un mur ou votre propre queue, le jeu est terminer." << endl;
    cout << "5. Appuyez sur 'x' pour quitter la partie a tout moment." << endl;
    cout << "\nAppuyez sur une touche pour continuer..." << endl;
    _getch(); // Attendre que l'utilisateur appuie sur une touche
}


//Sous-programme pour l'Initialisation du jeu 
void setup()
{
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    playerScore = 0;
}

// Sous programme qui créer une grille 

void boardRendering(string playerName)
{
    clearConsole();
    for (int i = 0; i < width + 2; i++)
         cout<<RED<<"-"<<RESET;
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                cout<<RED<<"|"<<RESET;
            //Créattion de la tête de serpent 
            if (i == y && j == x)
                 cout<<GREEN<<"O"<<RESET;
             //Création de la nourriture du serpent 
            else if (i == fruitY && j == fruitX)
               cout<<"o";
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTaille; k++) {
                    if (queueSnakeX[k] == j
                        && queueSnakeY[k] == i) {
                        cout<<GREEN<<"o"<<RESET;
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

     //Ligne du bas
    for (int i = 0; i < width + 2; i++)
        cout<<RED<<"-"<<RESET;
    cout << endl;

     //Affichage du score du joueur
    cout << playerName << "'s Score: " << playerScore
         << endl;
}

//sous-programme qui met à jour l'état du jeu
void UpdateGameSnake()
{
    int prevX = queueSnakeX[0];
    int prevY = queueSnakeY[0];
    int prev2X, prev2Y;
    queueSnakeX[0] = x;
    queueSnakeY[0] = y;

    for (int i = 1; i < snakeTaille; i++) {
        prev2X = queueSnakeX[i];
        prev2Y = queueSnakeY[i];
        queueSnakeX[i] = prevX;
        queueSnakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

   // Vérifie la collision du serpent avec le mur
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    //Vérifie la collision avec la queue
    for (int i = 0; i < snakeTaille; i++) {
        if (queueSnakeX[i] == x && queueSnakeY[i] == y)
            isGameOver = true;
    }

    //Vérifie la collision avec la nouriture
    if (x == fruitX && y == fruitY) {
        playerScore += 5;
        fruitX = rand() % width;
        fruitY = rand() % height;
        snakeTaille++;
    }
}

//Fonction pour choisir la difficulté du jeu qui Renvoie le niveau de difficulté choisir 
int levelDifficulty()
{
    int level, choice;
    cout<<"Choissisez le niveau de difficulter "<<endl;
    cout<<"1 - Facile "<<endl;
    cout<<"2 - Moyen "<<endl;
    cout<<"3 - Difficile "<<endl;
    cin >> choice;
    switch (choice) {
    case '1':
        level = 50;
        break;
    case '2':
        level = 100;
        break;
    case '3':
        level = 150;
        break;
    default:
        level = 100;
    }
    return level;
}

//Fonction pour gérer l'entrée de l'utilisateur en fonction de la direction choisir
void userDirection()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'q':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'z':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            menu();
            break;
        }

    }
}

//sous programme qui affiche un petit menu à la fin de la partie  
void menuDeFIn( string playerName){
    char choice;
    clearConsole();
    cout<<"==== Fin de la partie ==="<<endl;
    cout<<playerName<<", votre score est : "<<playerScore<<endl;
    cout<<"Que voulez-vous faire ? "<<endl;
    cout<<"1. Rejouer"<<endl;
    cout<<"2. Retourner au menu principal"<<endl;
    cin>>choice;
    switch (choice)
    {
    case '1':
        snake();
        break;
    case '2':
        menu();
        break;
    default:
        cout<<"Choix invalide, retour au menu principal ....";
        Sleep(2000);
        menu();
        break;
    }

}


int snake()
{
    clearConsole();
    string playerName;
    cout << "Entrez votre nom : ";
    cin >> playerName;
    gameRegle1();
    clearConsole();
    int level = levelDifficulty();
    setup();
    while (!isGameOver) {
        boardRendering(playerName);
        userDirection();
        UpdateGameSnake();
        Sleep(level);
    }

    menuDeFIn(playerName);
    return 0;
}

