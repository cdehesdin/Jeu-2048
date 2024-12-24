#include <iostream>
#include <iomanip>
#include "modele.hpp"
#include "variante.hpp"
#include <curses.h>

#define WIDTH 30
#define HEIGHT 10

using namespace std;

int main() {
    WINDOW *menu_win;
    int startx = (80 - WIDTH) / 2;
    int starty = (24 - HEIGHT) / 2;
    int nbCase, base;
    cout << "Quel base voulez vous utiliser ? : ";
    cin >> base;
    cout << "Quel taille de tableau voulez-vous ? : ";
    cin >> nbCase;

    Jeu jeu;
    jeu.plateau = plateauInitialNbCase(nbCase, base);
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
        printw("%s", dessine(jeu.plateau).c_str());
        printw("A toi de jouer : ");
        refresh();
        keypad(stdscr, true);
        do {
            c =  wgetch(menu_win);
        } while (c != 259 and c != 258 and c != 261 and c!= 260);
        direction = c-258;
        Jeu newJeu = deplacementBase(jeu, direction, base);
        if (deplacementValide(jeu, direction)) {
            jeu = newJeu;
            int i, j;
            do {
                i = rand()%jeu.plateau.size();
                j = rand()%jeu.plateau.size();
            } while(jeu.plateau[i][j] != 0);
            jeu.plateau[i][j] = tireDeuxOuQuatreBase(base);
        }
    }
    clear();
    printw("Score : ");
    printw("%s", to_string(jeu.score).c_str());
    printw("\n");
    printw("%s", dessine(jeu.plateau).c_str());
    if (estGagnantBase(jeu.plateau, base)) {
        printw("\nBien joué tu as gagné !\n");
    } else {
        printw("\nDommage tu as perdu !\n");
    }
    refresh();
    do {
        c = wgetch(menu_win);
    } while (c != KEY_ENTER);
    endwin();

    return 0;
}