#include <iostream>
#include <iomanip>
#include <curses.h>
#include "modele.hpp"
#include "affichage.hpp"

#define WIDTH 30
#define HEIGHT 10

using namespace std;
using Plateau = vector<vector<int>>;

int main() {
    bool couleur = false;   // Pour affichier ou non les couleurs sur le plateau (oui / non)
    cout << "Voulez-vous avoir des couleurs sur le plateau ? (0 : non / 1 : oui) ";
    cin >> couleur;
    cout << endl;

    WINDOW *menu_win;
    int startx = (80 - WIDTH) / 2;
	int starty = (24 - HEIGHT) / 2;

    Jeu jeu;
    jeu.plateau = plateauInitial();
    jeu.score = 0;
    int direction;
    int c;

    // Initialisation de ncurses
    initscr();
    use_default_colors();
    cbreak(); // Désactive le buffering du terminal
    noecho(); // N'affiche pas les touches appuyées
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);

    while (not estTermine(jeu)) {
        clear();
        printw("Score : ");
        printw("%s", to_string(jeu.score).c_str());
        printw("\n");
        if (not couleur) {
            printw("%s", dessine(jeu.plateau).c_str());   // Pour afficher le plateau sans les couleurs
        } else {
            affiche(jeu.plateau);                         // Pour afficher le plateau avec les couleurs
        }
        printw("A toi de jouer : ");
        refresh();
        keypad(stdscr, true);
        do {
            c =  wgetch(menu_win);
        } while (c != 259 and c != 258 and c != 261 and c!= 260);
        direction = c-258;
        Jeu newJeu = deplacement(jeu, direction);
        if (deplacementValide(jeu, direction)) {
            jeu = newJeu;
            int i, j;
            do {
                i = rand()%jeu.plateau.size();
                j = rand()%jeu.plateau.size();
            } while(jeu.plateau[i][j] != 0);
            jeu.plateau[i][j] = tireDeuxOuQuatre();
        }
    }
    clear();
    printw("Score : ");
    printw("%s", to_string(jeu.score).c_str());
    printw("\n");
    printw("%s", dessine(jeu.plateau).c_str());
    if (estGagnant(jeu.plateau)) {
        printw("\nBien joué tu as gagné !\n");
    } else {
        printw("\nDommage tu as perdu !\n");
    }
    refresh();
    do {
        c =  wgetch(menu_win);
    } while (c != KEY_ENTER);
    endwin();

    return 0;
}