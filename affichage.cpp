#include <vector>
#include <string>
#include <curses.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "affichage.hpp"

using namespace std;

using Plateau = vector<vector<int>>;

void affiche(Plateau p) {
    start_color();

    int valMaxi = 0, nombreChiffre = 0;
    for (int indice=0; indice<p.size(); indice++) {
        for (auto elem: p[indice]) {
            if (elem > valMaxi) {
                valMaxi = elem;
            }
        }
    }
    if (valMaxi !=0) {
        nombreChiffre = std::to_string(valMaxi).size();
    }

    init_color(10, 237, 226, 221); // 2
    init_color(11, 235, 225, 203); // 4
    init_color(12, 233, 178, 131); // 8
    init_color(13, 233, 151, 109); // 16
    init_color(14, 230, 129, 105); // 32
    init_color(15, 222, 99, 73); // 64
    init_color(16, 232, 204, 128); // 128
    init_color(17, 230, 220, 113); // 256
    init_color(18, 232, 198, 104); // 512
    init_color(19, 231, 194, 90); // 1024
    init_color(20, 231, 193, 80); // 2048

    init_pair(1, COLOR_WHITE, 10);
    init_pair(2, COLOR_WHITE, 11);
    init_pair(3, COLOR_WHITE, 12);
    init_pair(4, COLOR_WHITE, 13);
    init_pair(5, COLOR_WHITE, 14);
    init_pair(6, COLOR_WHITE, 15);
    init_pair(7, COLOR_WHITE, 16);
    init_pair(8, COLOR_WHITE, 17);
    init_pair(9, COLOR_WHITE, 18);
    init_pair(10, COLOR_WHITE, 19);
    init_pair(11, COLOR_WHITE, 20);

    // Ligne d'*
    string ligne = "*";
    for (int i=1; i<=p.size(); i++) {
        for (int j=1; j<=nombreChiffre; j++) {
            ligne += "*";
        }
        ligne += "***";
    }

    // Dessine le plateau
    printw("%s", ligne.c_str());
    printw("\n");
    for (int indice=0; indice<p.size(); indice++) {
        for (auto elem: p[indice]) {
            ostringstream case_string;
            if (elem != 0) {
                case_string << setw(nombreChiffre) <<  elem ;
            } else {
                case_string <<  setw(nombreChiffre) << " ";
            }
            printw("* ");
                attron(COLOR_PAIR(log2(elem)));
                printw("%s", case_string.str().c_str());
                attroff(COLOR_PAIR(log2(elem)));
            printw(" ");
        }
        printw("*\n");
        printw("%s", ligne.c_str());
        printw("\n");
    }
}