/*####################################################################################
Créateur : Th3Ph3nix3
Date de dernière mise à jour : 17/11/2024

Description : Ce programme est le menu de notre jeu c'est le programme principale et
              la première chose que le joueur voit, il sert a séléctionné le mode de 
              jeu que l'utilisateur souhaite et a quitter correctement le jeu.
              
Mode d'emploi : Le menu se trouve dans le dossier source pour le compiler ouvrer un 
                terminal dans ce fichier et utiliser la commande g++ *.cpp -o Jeu -lwinmm 
                pour compiler tous les fichier en un exe et lancer cet exe avec la 
                commande ./Jeu.

                                Amusez vous bien !
####################################################################################*/


#include <iostream>
#include <string>

//Module pour les commandes windows quand le système d'exploitation détecter est windows
#include <windows.h>

//Module jouer son
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//Importation des autres fichiers
#include "../include/pendu.hpp"
#include "../include/pfc.hpp"
#include "../include/juste_prix.hpp"
#include "../include/blackjack.hpp"
#include "../include/morpion.hpp"
#include "../include/snake.hpp"
#include "../include/menu.hpp"

using namespace std;

// Sous programme mettant la console en plein écran au démmarage du jeu
void pleinecran(){
    keybd_event(VK_MENU,0x38,0,0); //Appuie sur ALT
    keybd_event(VK_RETURN,0x1c,0,0); //Appuie ENTREE
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0); // Relache ENTREE
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0); //Relache ALT
}

void quittejeu(){
    keybd_event(VK_MENU, 0x38, 0, 0);    // Appuie sur ALT
    keybd_event(VK_F4, 0x3e, 0, 0);    // Appuie sur F4
    keybd_event(VK_F4, 0x3e, KEYEVENTF_KEYUP, 0);    // Relâche F4
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);     // Relâche ALT
}

//Sous programme permettant de clear l'écran
void clearConsole(){ 
    #ifdef _WIN32 
        system("cls"); // Commande pour Windows 
    #else 
        system("clear"); // Commande pour Linux et MacOS 
    #endif 
}

//Sous programme affichant le menu de présentation de la page menu
void bienvenue(){ 
    clearConsole();

    cout << "       :::::::::       :::            :::     :::   :::       ::::::::       :::::::::       ::::::::      :::    :::       ::::    :::       ::::::::: " << endl;
    cout << "     :+:    :+:      :+:          :+: :+:   :+:   :+:      :+:    :+:      :+:    :+:     :+:    :+:     :+:    :+:       :+:+:   :+:       :+:    :+: " << endl;
    cout << "    +:+    +:+      +:+         +:+   +:+   +:+ +:+       +:+             +:+    +:+     +:+    +:+     +:+    +:+       :+:+:+  +:+       +:+    +:+  " << endl;
    cout << "   +#++:++#+       +#+        +#++:++#++:   +#++:        :#:             +#++:++#:      +#+    +:+     +#+    +:+       +#+ +:+ +#+       +#+    +:+   " << endl;
    cout << "  +#+             +#+        +#+     +#+    +#+         +#+   +#+#      +#+    +#+     +#+    +#+     +#+    +#+       +#+  +#+#+#       +#+    +#+    " << endl;
    cout << " #+#             #+#        #+#     #+#    #+#         #+#    #+#      #+#    #+#     #+#    #+#     #+#    #+#       #+#   #+#+#       #+#    #+#     " << endl;
    cout << "###             ########## ###     ###    ###          ########       ###    ###      ########       ########        ###    ####       #########       " << endl;
    cout << "                                                                                                    by th3_ph3nix / whoselevenn / funaki25             " << endl;
    PlaySound(TEXT("../musique/Musique_intro.wav"), NULL, SND_FILENAME | SND_SYNC);
}

//Sous programme affichant les jeux proposés
void jeux_propose(){
    clearConsole();

    cout << "1 > Le Pendu" << endl;
    cout << endl;
    cout << "2 > Le Pierre Feuille Ciseau" << endl;
    cout << endl;
    cout << "3 > Le Juste Prix" << endl;
    cout << endl;
    cout << "4 > Le Blackjack" << endl;
    cout << endl;
    cout << "5 > Le Morpion" << endl;
    cout << endl;
    cout << "6 > Le Snake" << endl;
    cout << endl;
    cout << endl;
    cout << "0 > Quitter le jeu" << endl;
    cout << endl;
}

//Sous programme permettant au joueur de selectionner un jeu
void selection(string &jeu_select){
    while (jeu_select != "1" && jeu_select != "2" && jeu_select != "3" && jeu_select != "4" && jeu_select != "5" && jeu_select != "6" && jeu_select != "0" && jeu_select != "5218"){
        jeux_propose();
        cout << "Entrez le numero du jeux souhaite : ";
        cin >> jeu_select;
    }
}

//Sous programme affichant le menu de lancement du pendu
void affich_pendu(){
    clearConsole();

    cout << "      :::::::::       ::::::::::       ::::    :::       :::::::::      :::    ::: " << endl;
    cout << "     :+:    :+:      :+:              :+:+:   :+:       :+:    :+:     :+:    :+:  " << endl;
    cout << "    +:+    +:+      +:+              :+:+:+  +:+       +:+    +:+     +:+    +:+   " << endl;
    cout << "   +#++:++#+       +#++:++#         +#+ +:+ +#+       +#+    +:+     +#+    +:+    " << endl;
    cout << "  +#+             +#+              +#+  +#+#+#       +#+    +#+     +#+    +#+     " << endl;
    cout << " #+#             #+#              #+#   #+#+#       #+#    #+#     #+#    #+#      " << endl;
    cout << "###             ##########       ###    ####       #########       ########        " << endl;
    cout << "                                                                  by th3_ph3nix    " << endl;

    PlaySound(TEXT("../musique/Musique_intro_pendu.wav"), NULL, SND_FILENAME | SND_SYNC);
}


//Sous programme affichant le menu de lancement du pierre feuille ciseau
void affich_PFC(){
    clearConsole();

    cout << " ####     #                                       #####                  #     ##     ##                   ###     #                                      " << endl;
    cout << " #   #                                            #                             #      #                  #   #                                           " << endl;
    cout << " #   #   ##     ###   # ##   # ##    ###          #       ###   #   #   ##      #      #     ###          #       ##     ###    ###    ###   #   #  #   # " << endl;
    cout << " ####     #    #   #  ##  #  ##  #  #   #         ####   #   #  #   #    #      #      #    #   #         #        #    #      #   #      #  #   #   # #  " << endl;
    cout << " #        #    #####  #      #      #####         #      #####  #   #    #      #      #    #####         #        #     ###   #####   ####  #   #    #   " << endl;
    cout << " #        #    #      #      #      #             #      #      #  ##    #      #      #    #             #   #    #        #  #      #   #  #  ##   # #  " << endl;
    cout << " #       ###    ###   #      #       ###          #       ###    ## #   ###    ###    ###    ###           ###    ###   ####    ###    ####   ## #  #   # " << endl;
    cout << "                                                                                                                                       by th3_ph3nix      " << endl;
    
    PlaySound(TEXT("../musique/Musique_intro_PFC.wav"), NULL, SND_FILENAME | SND_SYNC);
}


//Sous programme affichant le menu de lancement du juste prix
void affich_Juste_prix(){
    clearConsole();

    cout << "     :::::::::::      :::    :::       ::::::::   :::::::::::       ::::::::::        :::::::::       :::::::::       :::::::::::       :::    ::: " << endl;
    cout << "        :+:          :+:    :+:      :+:    :+:      :+:           :+:               :+:    :+:      :+:    :+:          :+:           :+:    :+:  " << endl;
    cout << "       +:+          +:+    +:+      +:+             +:+           +:+               +:+    +:+      +:+    +:+          +:+            +:+  +:+    " << endl;
    cout << "      +#+          +#+    +:+      +#++:++#++      +#+           +#++:++#          +#++:++#+       +#++:++#:           +#+             +#++:+      " << endl;
    cout << "     +#+          +#+    +#+             +#+      +#+           +#+               +#+             +#+    +#+          +#+            +#+  +#+      " << endl;
    cout << "#+# #+#          #+#    #+#      #+#    #+#      #+#           #+#               #+#             #+#    #+#          #+#           #+#    #+#      " << endl;
    cout << "#####            ########        ########       ###           ##########        ###             ###    ###      ###########       ###    ###       " << endl;
    cout << "                                                                                                                                 by whoselevenn    " << endl;

    PlaySound(TEXT("../musique/Musique_intro_JustePrix.wav"), NULL, SND_FILENAME | SND_SYNC);
}


//Sous programme affichant le menu de lancement du Blackjack
void affich_Blackjack(){
    clearConsole();

    cout << "      :::::::::       :::            :::        ::::::::       :::    :::      :::::::::::           :::        ::::::::       :::    ::: " << endl;
    cout << "     :+:    :+:      :+:          :+: :+:     :+:    :+:      :+:   :+:           :+:             :+: :+:     :+:    :+:      :+:   :+:   " << endl;
    cout << "    +:+    +:+      +:+         +:+   +:+    +:+             +:+  +:+            +:+            +:+   +:+    +:+             +:+  +:+     " << endl;
    cout << "   +#++:++#+       +#+        +#++:++#++:   +#+             +#++:++             +#+           +#++:++#++:   +#+             +#++:++       " << endl;
    cout << "  +#+    +#+      +#+        +#+     +#+   +#+             +#+  +#+            +#+           +#+     +#+   +#+             +#+  +#+       " << endl;
    cout << " #+#    #+#      #+#        #+#     #+#   #+#    #+#      #+#   #+#       #+# #+#           #+#     #+#   #+#    #+#      #+#   #+#       " << endl;
    cout << "#########       ########## ###     ###    ########       ###    ###       #####            ###     ###    ########       ###    ###       " << endl;
    cout << "                                                                                                                        by whoselevenn    " << endl;

    PlaySound(TEXT("../musique/Musique_intro_Blackjack.wav"), NULL, SND_FILENAME | SND_SYNC);
}

//Sous programme affichant le menu de lancement du Morpion
void affich_Morpion(){
    clearConsole();

    cout << "        :::   :::       ::::::::       :::::::::       :::::::::       :::::::::::       ::::::::       ::::    ::: " << endl;
    cout << "      :+:+: :+:+:     :+:    :+:      :+:    :+:      :+:    :+:          :+:          :+:    :+:      :+:+:   :+:  " << endl;
    cout << "    +:+ +:+:+ +:+    +:+    +:+      +:+    +:+      +:+    +:+          +:+          +:+    +:+      :+:+:+  +:+   " << endl;
    cout << "   +#+  +:+  +#+    +#+    +:+      +#++:++#:       +#++:++#+           +#+          +#+    +:+      +#+ +:+ +#+    " << endl;
    cout << "  +#+       +#+    +#+    +#+      +#+    +#+      +#+                 +#+          +#+    +#+      +#+  +#+#+#     " << endl;
    cout << " #+#       #+#    #+#    #+#      #+#    #+#      #+#                 #+#          #+#    #+#      #+#   #+#+#      " << endl;
    cout << "###       ###     ########       ###    ###      ###             ###########       ########       ###    ####       " << endl;
    cout << "                                                                                                 by funaki25        " << endl;

    PlaySound(TEXT("../musique/Musique_intro_Morpion.wav"), NULL, SND_FILENAME | SND_SYNC);
}


//Sous programme affichant le menu de lancement du Snake
void affich_Snake(){
    clearConsole();

    cout << "      ::::::::       ::::    :::           :::        :::    :::       :::::::::: " << endl;
    cout << "    :+:    :+:      :+:+:   :+:         :+: :+:      :+:   :+:        :+:         " << endl;
    cout << "   +:+             :+:+:+  +:+        +:+   +:+     +:+  +:+         +:+          " << endl;
    cout << "  +#++:++#++      +#+ +:+ +#+       +#++:++#++:    +#++:++          +#++:++#      " << endl;
    cout << "        +#+      +#+  +#+#+#       +#+     +#+    +#+  +#+         +#+            " << endl;
    cout << "#+#    #+#      #+#   #+#+#       #+#     #+#    #+#   #+#        #+#             " << endl;
    cout << "########       ###    ####       ###     ###    ###    ###       ##########       " << endl;
    cout << "                                                                by funaki25       " << endl;

    PlaySound(TEXT("../musique/Musique_intro_Snake.wav"), NULL, SND_FILENAME | SND_SYNC);
}


//Sous programme lançant le jeu séléctionné par le joueur
void lancement_jeu(string &jeu_select){
    if (jeu_select == "0"){
        clearConsole();

        cout << "#############################################################" << std::endl;
        cout << "#                                                           #" << std::endl;
        cout << "#                   " << "\033[4m" << "Merci d'avoir joue !" << "\033[0m" << "                    #" << endl;
        cout << "#                                                           #" << std::endl;
        cout << "#############################################################" << std::endl;

        Sleep(2500);
    }
    
    else if (jeu_select == "1"){
        affich_pendu();
        pendu();
    }

    else if (jeu_select == "2"){
        affich_PFC();
        PFC();
    }

    else if (jeu_select == "3"){
        affich_Juste_prix();
        juste_prix();
    }
    else if(jeu_select == "5218"){test();}
    else if (jeu_select == "4"){
        affich_Blackjack();
        blackjack();
    }

    else if (jeu_select == "5"){
        affich_Morpion();
        morpion();
    }

    else if (jeu_select == "6"){
        affich_Snake();
        snake();
    }

    else{
        cout << "Jeu HS, requiert l'attention d'un administrateur, code 0" << endl;
    }
}

int menu(){
    string jeu_select = " ";
    selection(jeu_select);
    lancement_jeu(jeu_select);
    quittejeu();

    return -1;
}

int main(){
    pleinecran();
    bienvenue();
    menu();
}

