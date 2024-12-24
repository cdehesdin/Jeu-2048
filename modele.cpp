#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
#include "modele.hpp"

using namespace std;

using Plateau = vector<vector<int>>;

// Création du générateur de nombres aléatoires
random_device rd;  // Dispositif de génération aléatoire
mt19937 gen(rd()); // Générateur Mersenne Twister
uniform_int_distribution<> dist(1, 10); // Distribution entre 1 et 10
uniform_int_distribution<> dist2(0, 3); // Distribution entre 0 et 3

int tireDeuxOuQuatre() {
    srand(time(0));
    int var = dist(gen);
    if (var == 1) {
        return 4;
    } else {
        return 2;
    }
}

Plateau plateauVide() {
    Plateau plateauVide = vector<vector<int>>(4);
    for (int indice=0; indice<4; indice++) {
        plateauVide[indice] = vector<int>(4);
    }
    return plateauVide;
}

Plateau plateauInitial() {
    Plateau plateau = plateauVide();
    for (int _ = 0; _< 2; _++) {
        int i, j;
        do {
            i = dist2(gen);
            j = dist2(gen);
        } while(plateau[i][j] != 0);
        plateau[i][j] = tireDeuxOuQuatre();
    }
    return plateau;
}

Jeu deplacementGauche(Jeu jeu) {
    Plateau plateau = jeu.plateau;
    for (int k=0; k<2; k++) {
        // Mouvement
        for (int i=0; i<plateau.size(); i++) {
            for (int j=1; j<plateau.size(); j++) {
                if (plateau[i][j] != 0) {
                    int decal = 1;
                    while (j-decal>=0 and j-decal<=plateau.size()-1 and plateau[i][j-decal] == 0) {
                        plateau[i][j-decal] = plateau[i][j-decal+1];
                        plateau[i][j-decal+1] = 0;
                        decal++;
                    }
                }
            }
        }
        // Fusion
        if (k == 0) {
            for (int i=0; i<plateau.size(); i++) {
                for (int j=1; j<plateau.size(); j++) {
                    if (plateau[i][j] != 0) {
                        if (plateau[i][j-1] == plateau[i][j]) {
                            jeu.score += plateau[i][j]*2;
                            plateau[i][j-1] = plateau[i][j]*2;
                            plateau[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    jeu.plateau = plateau;
    return jeu;
}

Jeu deplacementDroite(Jeu jeu) {
    Plateau plateau = jeu.plateau;
    for (int k=0; k<2; k++) {
        // Mouvement
        for (int i=0; i<plateau.size(); i++) {
            for (int j=plateau.size()-2; j>-1; j--) {
                if (plateau[i][j]!=0) {
                    int decal = 1; 
                    while (0<=j+decal and j+decal<=plateau.size()-1 and plateau[i][j+decal] == 0) {
                        plateau[i][j+decal] = plateau[i][j+decal-1];
                        plateau[i][j+decal-1] = 0;
                        decal++;
                    }
                }
            }
        }
        // Fusion
        if (k == 0) {
            for (int i=0; i<plateau.size(); i++) {
                for (int j=plateau.size()-2; j>-1; j--) {
                    if (plateau[i][j]!=0) {
                        if (plateau[i][j+1] == plateau[i][j]) {
                            plateau[i][j+1] = plateau[i][j]*2;
                            jeu.score += plateau[i][j]*2;
                            plateau[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    jeu.plateau = plateau;
    return jeu;
}

Jeu deplacementHaut(Jeu jeu) {
    Plateau plateau = jeu.plateau;
    for (int k=0; k<2; k++) {
        // Mouvement
        for (int i=1; i<plateau.size(); i++) {
            for (int j=0; j<plateau.size(); j++) {
                if (plateau[i][j]!=0) {
                    int decal = 1; 
                    while (0<=i-decal and i-decal<=plateau.size()-1 and plateau[i-decal][j] == 0) {
                        plateau[i-decal][j] = plateau[i-decal+1][j];
                        plateau[i-decal+1][j] = 0;
                        decal++;
                    }
                }
            }
        }
        // Fusion
        if (k == 0) {
            for (int i=1; i<plateau.size(); i++) {
                for (int j=0; j<plateau.size(); j++) {
                    if (plateau[i][j] != 0) {
                        if (plateau[i-1][j] == plateau[i][j]) {
                            plateau[i-1][j] = plateau[i][j]*2;
                            jeu.score += plateau[i][j]*2;   
                            plateau[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    jeu.plateau = plateau;
    return jeu;
}

Jeu deplacementBas(Jeu jeu) {
    Plateau plateau = jeu.plateau;
    for(int k=0; k<2; k++){
        // Mouvement
        for(int i=plateau.size()-2; i>-1; i--){
            for (int j=0; j<plateau.size(); j++) {
                if (plateau[i][j] != 0) {
                    int decal = 1; 
                    while (0<=i+decal and i+decal<=plateau.size()-1 and plateau[i+decal][j] == 0) {
                        plateau[i+decal][j] = plateau[i+decal-1][j];
                        plateau[i+decal-1][j] = 0;
                        decal++;
                    }
                }
            }
        }
        // Fusion
        if (k == 0) {
            for (int i=plateau.size()-2; i>-1; i--) {
                for (int j=0; j<plateau.size(); j++) {
                    if (plateau[i][j]!=0) {
                        if (plateau[i+1][j] == plateau[i][j]) {
                            plateau[i+1][j] = plateau[i][j]*2;
                            jeu.score += plateau[i][j]*2;
                            plateau[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    jeu.plateau = plateau;
    return jeu;
}

Jeu deplacement(Jeu jeu, int direction) {
    if (direction == 0) {
        jeu = deplacementBas(jeu);
    } else if (direction == 1) {
        jeu = deplacementHaut(jeu);
    } else if (direction == 2) {
        jeu = deplacementGauche(jeu);
    } else if(direction == 3) {
        jeu = deplacementDroite(jeu);
    }
    return jeu;
}

string dessine(Plateau p) {
    string affichage = "";

    // Permet de trouver la longueur de la valeur maximum du plateau
    int valMaxi = 0, nombreChiffre = 0;
    for (int indice=0; indice<p.size(); indice++) {
        for (auto elem: p[indice]) {
            if (elem > valMaxi) {
                valMaxi = elem;
            }
        }
    }
    if (valMaxi !=0){
        nombreChiffre = std::to_string(valMaxi).size();
    }

    // Ligne d'*
    string ligne = "*";
    for (int i=1; i<=p.size(); i++) {
        for (int j=1; j<=nombreChiffre; j++) {
            ligne += "*";
        }
        ligne += "***";
    }

    // Dessine le plateau
    affichage +=  ligne + "\n";
    for (int indice=0; indice<p.size(); indice++) {
        for (auto elem: p[indice]) {
            ostringstream case_string;
            if (elem != 0) {
                case_string << "* " << setw(nombreChiffre) << elem << ' ';
            } else {
                case_string << "* " << setw(nombreChiffre+1) << ' ';
            }
            affichage += case_string.str();
        }
        affichage += '*';
        affichage += "\n";
        affichage += ligne + "\n";
    }
    return affichage;
}

bool deplacementValide(Jeu jeu, int direction) {
    Jeu newJeu = deplacement(jeu, direction);
    Plateau newPlateau = newJeu.plateau;
    for (int i=0; i<newPlateau.size(); i++) {
        for (int j=0; j<newPlateau.size(); j++) {
            if (newPlateau[i][j] != jeu.plateau[i][j]) {
                return true;
            }
        }
    }
    return false;
}

bool estTermine(Jeu jeu) {
    for (int direction=0; direction<jeu.plateau.size(); direction++) {
        if (deplacementValide(jeu, direction)) {
            return false;
        }
    }
    return true;
}

bool estGagnant(Plateau plateau) {
    for (int i=0; i<plateau.size(); i++) {
        for (auto elem:plateau[i]) {
            if (elem >= 2048) {
                return true;
            }
        }
    }
    return false;
}

int pointBot(Plateau plateau) {

    // Initialisation des 4 types de plateau pondérant les nombres du plateau initiale
    Plateau ponderationHG = {{60,50,40,30}, {50,40,30,20}, {40,30,20,10}, {30,20,10,0}};
    Plateau ponderationHD = {{30,40,50,60}, {20,30,40,50}, {10,20,30,40}, {0,10,20,30}};
    Plateau ponderationBG = {{30,20,10,0}, {40,30,20,10}, {50,40,30,20}, {60,50,40,30}};
    Plateau ponderationBD = {{0,10,20,30}, {10,20,30,40}, {20,30,40,50}, {30,40,50,60}};
    vector<Plateau> choixPlateau = {ponderationHG, ponderationHD, ponderationBG, ponderationBD};

    // Initialisation des variables pour les points
    int point, pointMaxi = 0;

    // Stocke dans pointMaxi, la meilleure pondération de plateau en fonction de chaque plateau
    for (auto plateauChoisi : choixPlateau) {
        // Calcule le nombre de point du plateau en fonction du plateauChoisi
        point = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                point += plateauChoisi[i][j] * plateau[i][j];
            }
        }
        // Si les points du plateau en fonction du plateauChoisi sont supérieurs au point maximum : ils deviennent le maximum
        if (point > pointMaxi) {pointMaxi = point;}
    }

    return pointMaxi;
}