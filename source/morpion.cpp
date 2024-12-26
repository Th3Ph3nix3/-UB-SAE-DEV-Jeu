#include<iostream>
#include<ctime>
#include <cctype> // pour tolower()

#include "../include/menu.hpp"
#include "../include/morpion.hpp"

using namespace std;

void gameRegle(){
    cout << "---------------- M O R P I O N ----------------" << endl;
    cout << endl;
    cout << "Jeu avec 2 joueurs humains ou 1 joueur contre la machine et une grille de 9 cases : 3 lignes et 3 colonnes." << endl; 
    cout << "Chaque joueur joue a tour de role." << endl;
    cout << "Le but du jeu est d'aligner, avant son adversaire, 3 symboles identiques, horizontalement, verticalement ou en diagonale" << endl;
    cout << endl;
    cout << "La partie se termine :" << endl;
    cout << "- quand l'un des joueurs a aligne ses 3 symboles, et il gagne," << endl;
    cout << "- quand la grille est complete, et il y a egalite (pas de gagnant)" << endl;
    cout << "- quand l'un des joueurs abandonne, et c'est alors l'autre joueur qui gagne." << endl;
    cout << "Chaque joueur a donc son propre symbole." << endl;
    cout << endl;
    cout << "-----------------------------------------------" << endl;

}

char tab[3][3]={
        {'1','2','3'},{'4','5','6'},{'7','8','9'}
};

string joueur1;
string joueur2;
char currenPlayer = 'x';
int position;
bool equality;
int ligne,colonne;
char dernierJoueur;

//Sous programme pour l'affichage de la grille 
void affichageDuPlateau(){
    cout<<"    |    |    \n";
    cout<<" "<<tab[0][0]<<"  | " <<tab[0][1]<<"  | "<<tab[0][2]<< " \n" ;
    cout<<"____|____|____\n";
    cout<<"    |    |    \n";
    cout<<" "<<tab[1][0]<<"  | " <<tab[1][1]<<"  | "<<tab[1][2]<< " \n" ;
    cout<<"____|____|____\n";
    cout<<"    |    |    \n";
    cout<<" "<<tab[2][0]<<"  | " <<tab[2][1]<<"  | "<<tab[2][2]<< " \n" ;
    cout<<"    |    |    \n";
}

//Sous-programme pour la reinitialisation du plateau
void reinitialiserPlateau(){
    char caseInit = '1';
    for(int i = 0; i<3; ++i){
        for(int j=0; j<3; ++j){
            tab[i][j] = caseInit++;
        }
    }
    currenPlayer ='x';
    equality = false;
}

//Sous-programme qui récupère les données de l'utilisateur 
void proccessInput(){
    
    if(currenPlayer =='x'){
        cout<<"[X] "<<joueur1<<" a vous de jouer : ";
        cin>>position;
        
    }else if (currenPlayer == 'o'){
        cout<<"[O] "<<joueur2<<" a vous de jouer : ";
        cin>>position;  
    }
    clearConsole();

    if(position == 1){
        ligne =0; colonne = 0;
    }
     if(position == 2){
        ligne =0; colonne = 1;
    }
     if(position == 3){
        ligne =0; colonne = 2;
    }
     if(position == 4){
        ligne =1; colonne = 0;
    }
     if(position == 5){
        ligne =1; colonne = 1;
    }
     if(position == 6){
        ligne =1; colonne = 2;
    }
     if(position == 7){
        ligne =2; colonne = 0;
    }
     if(position == 8){
        ligne =2; colonne = 1;
    }
     if(position == 9){
        ligne =2; colonne = 2;
    }

    if(position  < 1 || position > 9 || tab[ligne][colonne] == 'x' || tab[ligne][colonne] == 'o'){
        cout<<"Invalide veuiilez reeasyer \n";
        affichageDuPlateau();
        proccessInput();
    }else{
        tab[ligne][colonne] = currenPlayer;
        
        cout<<tab[ligne][colonne] <<" viens de jouer \n";
    }

    // Alternance des joeurs

     dernierJoueur = currenPlayer;
     if (currenPlayer == 'x') {
            currenPlayer = 'o';
        } else {
            currenPlayer = 'x';
    }
}

/*Sous programme qui controle le vainceur du jeu */
bool gamesResult(){

    for(int i=0; i < 3; i++){
        if ((tab[i][0] == tab[i][1] && tab[i][0] == tab[i][2]) || 
            (tab[0][i] == tab[1][i] && tab[0][i] == tab[2][i])){
            return false;
        }
    }

    if( (tab[0][0]== tab[1][1] && tab[1][1] == tab[2][2]) || (tab[0][2]== tab[1][1] && tab[1][1] == tab[2][0] )){
        return false;
    }
    // Vérification de l'égalité
    for (int i = 0; i < 3; i++){
       for(int j = 0; j<3; j++){
            if(tab[i][j] != 'x' && tab[i][j] != 'o'){
                return true;
            }
       }
    }
    equality  = true;
    
    return false; 
}

/*
    Sous-programme qui contient l'algo d'exécution contre 
    la machine.
*/
void JouerContreMachine(){
    cout<<joueur1<< " votre symbole est x \n";
    cout<<"Le symbole [o] est prise par la machine \n";
    while (gamesResult()){
        clearConsole();
        affichageDuPlateau();
        if(currenPlayer == 'x'){
            proccessInput();
        }else{
            srand(time(0));
            do{
                position = rand()%9;
                ligne = position/3;
                colonne = position %3;
            }while(tab[ligne][colonne]=='x' || tab[ligne][colonne]=='o');
            tab[ligne][colonne] = 'o';
            currenPlayer = 'x';
        }

    }
    // affichageDuPlateau();
     if(equality){
            cout<<"Match nul !\n";
        } else if( dernierJoueur == 'x'){
            cout<<joueur1<<" vous avez gagnez !\n";
        } else{
            cout<<"La machine a gagnez ! \n";
    } 
         
}



int menu1(){
    int choix;
    cout<<"\n MENU";
    cout<<"\n 1 - Lancer une partie contre la machine ";
    cout<<"\n 2 - Lancer une partie contre un autre joueur  ";
    cout<<"\n 3 - Afficher les regles du jeu ";
    cout<<"\n 4 - Quitter le programme  "<<std::endl;
    cin>>choix;
    return choix;
};

int morpion(){
    bool continuer = true;
    cout<<"--------------------Lancement du jeu morpion -------------------- ";
    cout<<"\nAppuyez sur la touche entrez pour continuez .....";
    cin.get();

    while (continuer)
    {
        clearConsole();
        int choix = menu1();  
        switch (choix){
            case 1:
                cout<<"Mode Contre la machine Selectionner \n";
                cout<<"Entrez votre nom : ";
                cin>>joueur1;
                JouerContreMachine();
                break;
            case 2:
                    cout<<"Entrez le nom du joueur 1 : ";
                    cin>>joueur1;
                    do{
                        cout<<"\nEntrez le nom du Joueur 2 : ";
                        cin>>joueur2;
                    }while(joueur1 == joueur2);
                    clearConsole();

                    cout<<joueur1<<" votre symbole est : x \n";
                    cout<<joueur2<<" votre symbole est : o \n";
                    
                    while(gamesResult()){
                        affichageDuPlateau();
                        proccessInput();
                    }
                    affichageDuPlateau();
                    if(dernierJoueur == 'x' && equality == false){
                        cout<<"Felicitaions "<<joueur1<<" vous avez gagner";
                    }else if(dernierJoueur == 'o' && equality == false){
                        cout<<"Felicitations "<<joueur2<<" vous avez gagner";
                    }else{
                        cout<<"Match null";
                    }    
                break;
            case 3:
                cout<<"Regle du jeu\n";
                gameRegle();
                break;
            case 4:
                cout<<"Au revoir !\n";
                menu();
                break;
            default:
                cout<<"Choix invalide"<<endl;
                menu1();
                break;
            }

            if(choix == 1 || choix == 2){
                char rejouer;
                do{
                    cout<<"\n Voulez-vous rejouer ? (Y pour continuer, N pour retourner au menu principale ) : ";
                    cin>>rejouer;
                    rejouer = tolower(rejouer);
                }while(rejouer!= 'y' && rejouer != 'n');

                if (rejouer == 'y'){
                    reinitialiserPlateau();
                }else{
                    menu();
                }
            }
    }
    return 0;
}