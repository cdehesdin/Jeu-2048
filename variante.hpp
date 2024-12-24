#include <vector>

using namespace std;

using Plateau = vector<vector<int>>;

/** Génère aléatoirement un nombre étant la base élevée à la puissance 1 ou 2 avec des probabilités respectives de 9/10 et 1/10
 *  @param base un entier déterminant la base
 *  @return la base élevée à la puissance 1 ou 2
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
int tireDeuxOuQuatreBase(int base);

/** Génère deux nombres sur des cases aléatoires d'un plateau vide
 *  @param base un entier déterminant la base
 *  @return un plateau en debut de jeu
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Plateau plateauVideNbCase(int nbreCase);

/** Génère deux nombres sur des cases aléatoires d'un plateau vide
 *  @param un entier nbreCase déterminant le nombre de cases du plateau
 *  @param base un entier déterminant la base
 *  @return un plateau en debut de jeu
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Plateau plateauInitialNbCase(int nbreCase, int base);

/** Déplace les tuiles d'un plateau vers la gauche et les combine si possible
 *  @param plateau le plateau
 *  @param base un entier déterminant la base
 *  @return le plateau une fois deplace vers la gauche
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Jeu deplacementGaucheBase(Jeu jeu, int base);

/** Déplace les tuiles d'un plateau vers la droite et les combine si possible
 *  @param plateau le plateau
 *  @param base un entier déterminant la base
 *  @return le plateau une fois déplace vers la droite
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Jeu deplacementDroiteBase(Jeu jeu, int base);

/** Déplace les tuiles d'un plateau vers le haut et les combine si possible
 *  @param plateau le plateau
 *  @param base un entier déterminant la base
 *  @return le plateau une fois déplace vers le haut
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Jeu deplacementHautBase(Jeu jeu, int base);

/** Déplace les tuiles d'un plateau vers le bas et les combine si possible
 *  @param plateau le plateau
 *  @param base un entier déterminant la base
 *  @return le plateau une fois déplace vers le bas
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Jeu deplacementBasBase(Jeu jeu, int base);

/** Déplace les tuiles d'un plateau dans la direction donnee et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le plateau
 *  @param direction la direction
 *  @param base un entier déterminant la base
 *  @return le plateau déplace dans la direction
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
Jeu deplacementBase(Jeu jeu, int direction, int base);

/** Permet de savoir si une partie est gagnée
 *  @param plateau un plateau
 *  @param base la base dans laquelle est le jeu
 *  @return true si le plateau contient un élément plus grand que base^11, false sinon
 *  @author Clément DEHESDIN : Très confiant grâce à la présence de tests
 **/
bool estGagnantBase(Plateau plateau, int base);