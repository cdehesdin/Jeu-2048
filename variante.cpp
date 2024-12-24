#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "modele.hpp"

using namespace std;

using Plateau = vector<vector<int>>;

int tireDeuxOuQuatreBase(int base) {
    srand(time(0));
    int var = rand()%10 + 1;
    if (var == 1) {
        return base * base;
    } else {
        return base;
    }
}

Plateau plateauVideNbCase(int nbreCase) {
    Plateau plateauVide = vector<vector<int>>(nbreCase);
    for (int indice=0; indice<nbreCase; indice++) {
        plateauVide[indice] = vector<int>(nbreCase);
    }
    return plateauVide;
}

Plateau plateauInitialNbCase(int nbreCase, int base) {
    Plateau plateau = plateauVideNbCase(nbreCase);
    for (int _ = 0; _< 2; _++) {
        int i, j;
        do {
            i = rand()%nbreCase;
            j = rand()%nbreCase;
        } while(plateau[i][j] != 0);
        plateau[i][j] = tireDeuxOuQuatreBase(base);
    }
    return plateau;
}

Jeu deplacementGaucheBase(Jeu jeu, int base) {
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
                            plateau[i][j-1] = plateau[i][j]*base;
                            jeu.score += plateau[i][j]*base;
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

Jeu deplacementDroiteBase(Jeu jeu, int base) {
    Plateau plateau = jeu.plateau;
    for(int k=0; k<2; k++){
        // Mouvement
        for (int i=0; i<plateau.size(); i++) {
            for (int j=plateau.size()-2; j>-1; j--) {
                if (plateau[i][j] != 0){
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
                    if (plateau[i][j] != 0) {
                        if (plateau[i][j+1] == plateau[i][j]) {
                            plateau[i][j+1] = plateau[i][j]*base;
                            jeu.score += plateau[i][j]*base;
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

Jeu deplacementHautBase(Jeu jeu, int base) {
    Plateau plateau = jeu.plateau;
    for (int k=0; k<2; k++) {
        // Mouvement
        for (int i=1; i<plateau.size(); i++) {
            for (int j=0; j<plateau.size(); j++) {
                if (plateau[i][j] != 0) {
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
                    if (plateau[i][j]!=0) {
                        if (plateau[i-1][j] == plateau[i][j]) {
                            plateau[i-1][j] = plateau[i][j]*base;
                            jeu.score += plateau[i][j]*base;
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

Jeu deplacementBasBase(Jeu jeu, int base) {
    Plateau plateau = jeu.plateau;
    for(int k=0; k<2; k++){
        // Mouvement
        for (int i=plateau.size()-2; i>-1; i--) {
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
                    if (plateau[i][j] != 0) {
                        if (plateau[i+1][j] == plateau[i][j]) {
                            plateau[i+1][j] = plateau[i][j]*base;
                            jeu.score += plateau[i][j]*base;
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

Jeu deplacementBase(Jeu jeu, int direction, int base) {
    if (direction == 0) {
        jeu = deplacementBasBase(jeu, base);
    } else if (direction == 1) {
        jeu = deplacementHautBase(jeu, base);
    } else if (direction == 2) {
        jeu = deplacementGaucheBase(jeu, base);
    } else if(direction == 3) {
        jeu = deplacementDroiteBase(jeu, base);
    }
    return jeu;
}

bool estGagnantBase(Plateau plateau, int base) {
    int exposant = base;
    for (int _=1; _<11; _++) {
        exposant *= base;
    }
    for (int i=0; i<plateau.size(); i++) {
        for (auto elem:plateau[i]) {
            if (elem >= exposant) {
                return true;
            }
        }
    }
    return false;
}