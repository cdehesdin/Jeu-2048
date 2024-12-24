#include <iostream>
#include <vector>
#include <random>
#include "modele.hpp"

using namespace std;
using Plateau = vector<vector<int>>;

// Création du générateur de nombres aléatoires
random_device dispositif;  // Dispositif de génération aléatoire
mt19937 generateur(dispositif()); // Générateur Mersenne Twister
uniform_int_distribution<> distribution(0, 3); // Distribution entre 0 et 3 distribution(generateur);

int main() {
 
    // Initialisation des variables utiles
    int var1, var2, nbSimulation = 100;
    double point, pointMoyen, pointMax;
    char deplacement, meilleurDeplacement;
    Jeu jeuInit, jeuDebut, jeuSimulation, jeuAleatoire, jeuFinal;

    // Initialisation du plateau initial
    Jeu jeu;
    jeu.plateau = plateauInitial();
    jeu.score = 0;

    cout << "Score : " << jeu.score << endl;
    cout << dessine(jeu.plateau) << endl;

    while (not estTermine(jeu)) {

        // Neutralisation des variables
        pointMax = 0;

        jeuInit = jeu;

        // Test tous les deplacements possibles et choisi le meilleur déplacement
        for (int direction = 0; direction < 4; direction++) {

            // Effectue la direction en fonction du nombre de la variable direction
            if (direction == 0) {
                jeuDebut = deplacementBas(jeuInit);
                deplacement = 'B';
            } else if (direction == 1) {
                jeuDebut = deplacementHaut(jeuInit);
                deplacement = 'H';
            } else if (direction == 2) {
                jeuDebut = deplacementGauche(jeuInit);
                deplacement = 'G';
            } else if (direction == 3) {
                jeuDebut = deplacementDroite(jeuInit);
                deplacement = 'D';
            }

            // Si plateauDebut est différent de plateauInit, rajoute une case (soit 2, soit 4)
            if (jeuDebut.plateau != jeuInit.plateau) {
                do {
                    var1 = distribution(generateur);
                    var2 = distribution(generateur);
                } while (jeuDebut.plateau[var1][var2] != 0);
                jeuDebut.plateau[var1][var2] = tireDeuxOuQuatre();
            }

            // Effectue nbSimulation simulations aléatoires du jeu à partir de plateauDebut
            for (int _ = 0; _ < nbSimulation; _++) {

                // Neutralisation des données
                jeuSimulation = jeuDebut;
                point = 0;

                // Tant que plateauSimulation n'est pas terminé, il continue de jouer de manière aléatoire
                while (not estTermine(jeuSimulation)) {

                    // Tire un nombre aléatoire entre 0 et 3 et effectue le mouvement
                    int choixDeplacement = distribution(generateur);
                    if (choixDeplacement == 0) {
                        jeuAleatoire = deplacementBas(jeuSimulation);
                    } else if (choixDeplacement == 1) {
                        jeuAleatoire = deplacementHaut(jeuSimulation);
                    } else if (choixDeplacement == 2) {
                        jeuAleatoire = deplacementGauche(jeuSimulation);
                    } else if (choixDeplacement == 3) {
                        jeuAleatoire = deplacementDroite(jeuSimulation);
                    }

                    // Si plateauAleatoire est différent de plateauSimulation, rajoute une case (soit 2, soit 4)
                    if (jeuAleatoire.plateau != jeuSimulation.plateau) {
                        do {
                            var1 = distribution(generateur);
                            var2 = distribution(generateur);
                        } while (jeuAleatoire.plateau[var1][var2] != 0);
                        jeuAleatoire.plateau[var1][var2] = tireDeuxOuQuatre();
                    }

                    jeuSimulation = jeuAleatoire;

                }

                // Calcul le nombre de points avec la fonction pointBot du plateau à la fin d'une simulation
                point += pointBot(jeuAleatoire.plateau);

            }

            // Fais la moyenne du nombre de points obtenue avec les différentes simulations sur ce déplacement
            pointMoyen = point / nbSimulation;

            // Si pointMoyen est supérieur à pointMax alors pointMoyen devient pointMax et le déplacement est sauvegardé comme le meilleur
            if (pointMoyen >= pointMax) {
                pointMax = pointMoyen;
                meilleurDeplacement = deplacement;
            }

        }

        // Exécution du déplacement sur le plateau de départ
        if (meilleurDeplacement == 'B') {
            jeuFinal = deplacementBas(jeu);
        } else if (meilleurDeplacement == 'H') {
            jeuFinal = deplacementHaut(jeu);
        } else if (meilleurDeplacement == 'G') {
            jeuFinal = deplacementGauche(jeu);
        } else if (meilleurDeplacement == 'D') {
            jeuFinal = deplacementDroite(jeu);
        }

        // Si plateauFinal est différent de plateau initiale, rajoute une case (soit 2, soit 4)
        if (jeuFinal.plateau != jeu.plateau) {
            do {
                var1 = distribution(generateur);
                var2 = distribution(generateur);
            } while (jeuFinal.plateau[var1][var2] != 0);
            jeuFinal.plateau[var1][var2] = tireDeuxOuQuatre();
        }

        cout << "Score : " << jeuFinal.score << endl;
        cout << dessine(jeuFinal.plateau) << endl;

        jeu = jeuFinal;

    }

    return 0;
}