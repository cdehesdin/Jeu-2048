#include <vector>
#include <string>
#include <iostream>
using namespace std;

using Plateau = vector<vector<int>>;

struct Jeu {
    Plateau plateau;
    int score;

    // Opérateurs de comparaison (égalité et différence) pour la structure de données Jeu (réalisé par Clément DEHESDIN)
    bool operator==(const Jeu& autre) const {
       return (plateau == autre.plateau) && (score == autre.score);
    }
    bool operator!=(const Jeu& autre) const {
       return (plateau != autre.plateau) || (score != autre.score);
    }
};

/** Génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
int tireDeuxOuQuatre();

/** Génère un plateau de dimensions 4*4 ne contenant que des 0
 *  @return un plateau vide
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Plateau plateauVide();

/** Génère deux nombres sur des cases aléatoires d'un plateau vide
 *  @return un plateau en debut de jeu
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Plateau plateauInitial();

/** Déplace les tuiles d'un plateau vers la gauche et les combine si possible
 *  @param jeu le jeu
 *  @return le jeu une fois déplace vers la gauche
 *  @authors Léanne ROCHE et Clément DEHESDIN : Très confiants grâce à la présence de tests et les résultats dans la console
 **/
Jeu deplacementGauche(Jeu jeu);

/** Déplace les tuiles d'un plateau vers la droite et les combine si possible
 *  @param jeu le jeu
 *  @return le jeu une fois déplace vers la droite
 *  @authors Léanne ROCHE et Clément DEHESDIN : Très confiants grâce à la présence de tests et les résultats dans la console
 **/
Jeu deplacementDroite(Jeu jeu);

/** Déplace les tuiles d'un plateau vers le haut et les combine si possible
 *  @param jeu le jeu
 *  @return le jeu une fois déplace vers le haut
 *  @authors Léanne ROCHE et Clément DEHESDIN : Très confiants grâce à la présence de tests et les résultats dans la console
 **/
Jeu deplacementHaut(Jeu jeu);

/** Déplace les tuiles d'un plateau vers le bas et les combine si possible
 *  @param jeu le jeu
 *  @return le jeu une fois déplace vers le bas
 *  @authors Léanne ROCHE et Clément DEHESDIN : Très confiants grâce à la présence de tests et les résultats dans la console
 **/
Jeu deplacementBas(Jeu jeu);

/** Déplace les tuiles d'un plateau dans la direction donnee et genere une nouvelle tuile si le deplacement est valide
 *  @param jeu le jeu
 *  @param direction la direction (0:bas, 1:haut, 2:gauche, 3:droite)
 *  @return le jeu déplace dans la direction
 *  @authors Léanne ROCHE et Clément DEHESDIN : Très confiants grâce à la présence de tests et les résultats dans la console
 **/
Jeu deplacement(Jeu jeu, int direction);

/** Permet de savoir si le déplacement est valide
 *  @param jeu le jeu
 *  @param direction le mouvement (0:bas, 1:haut, 2:gauche, 3:droite)
 *  @return true si le mouvement est valide false sinon
 *  @author Léanne ROCHE : Très confiante grâce à la présence de tests
 **/
bool deplacementValide(Jeu jeu, int direction);

/** Affiche un jeu
 *  @param p le plateau
 *  @authors Léanne ROCHE et Clément DEHESDIN : Très confiants grâce aux résultats dans la console
 **/
string dessine(Plateau p);

/** Permet de savoir si une partie est terminée
 *  @param jeu un jeu
 *  @return true si la partie est terminée false sinon
 *  @authors Léanne ROCHE et Clément DEHESDIN : Très confiants grâce à la présence de tests
 **/
bool estTermine(Jeu jeu);

/** Permet de savoir si une partie est gagnée
 *  @param plateau un plateau
 *  @return true si le plateau contient un élément supérieur ou égal à 2048, false sinon
 *  @author Léanne ROCHE : Très confiante grâce à la présence de tests
 **/
bool estGagnant(Plateau plateau);

/** Permet d'attribuer un certain nombre de points à un plateau
 *  @param plateau un plateau
 *  @return nombre de points associés au plateau
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
int pointBot(Plateau plateau);