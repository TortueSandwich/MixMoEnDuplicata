#include <vector>
using namespace std;

typedef vector<vector<char>> Grid;

extern Grid vrac;
extern Grid grille;

/** @brief Colle bout à bout deux grille ici le vrac et la grille
* @param vracM le vrac à l'état
* @param grilleM la grille à l'état
* @return les grilles melangées
*/
Grid merge(Grid vracM = vrac, Grid grilleM = grille);

/** @brief inclu la coordonnée X dans une grille
* @param x la coordonée en x
* @param grille la grille où l'inclure
* @return la coordonée incluse
* @details Taux de confiance 100%
*/
int incluX( int x, Grid grille );
/** @brief inclu la coordonnée Y dans une grille
* @param y la coordonée en y
* @param grille la grille où l'inclure
* @return la coordonée incluse
* @details Taux de confiance 100%
*/
int incluY( int y, Grid grille );

/** @brief ajoute ou enlève la lettre dans la selection
* @param x coordonée en X
* @param y coordonée en Y
* @param c la lettre en X,Y
* @details Taux de confiance 100%
*/
void selectioner(int x, int y, char c);

/** @brief bouge la selection vers le haut
* @details Taux de confiance 100%
*/
void bougeSelectionHaut();
/** @brief bouge la selection vers la gauche
* @details Taux de confiance 100%
*/
void bougeSelectionGauche();
/** @brief bouge la selection vers le bas
* @details Taux de confiance 100%
*/
void bougeSelectionBas();
/** @brief bouge la selection vers la droite
* @details Taux de confiance 100%
*/
void bougeSelectionDroite();

/** @brief Pose tout les jetons selectioné et renvois dans le vrac en cas de superposition
*  @details Taux de confiance 100%
*/
void poseSelection();

/** @brief Envoie la position au vrac
* @param X coordonnée x
* @param Y coordonnée Y
*/
void envoieAuVrac(int X, int Y);