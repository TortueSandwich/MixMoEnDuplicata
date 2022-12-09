#include <string>
#include <vector>
using namespace std;
typedef vector<vector<char>> Grid;


/** @brief Repete un ou une chaine de caractère à repeter
* @param n Le nombre de fois a repeter
* @param c Le/La chaine de caractère
* @return la chaine en string
*/
string repeteChar(int n,char c);
string repeteChar(int n,string c);

/** @breif Mets en majuscule un caractère ou une chaine de caractère
* @param sale le/la chaine sale
* @return l'entrée nettoyée
*/
char nettoie(char c);
string nettoie(string motsale);

/** @brief tourne de 90° une grille
* @param grille la grille a tourner
* @return La grille tournée
*/
vector<vector<char>> rotate(vector<vector<char>> grid);

/** @brief compte le nombre de jetons posé, prends tout les jetons par default
* @param grille la grille à l'état
* @param L Un caractère une question
*/
int nbdejetonpose(Grid grid);
int nbdejetonpose(vector<vector<char>> grid, char L);

/** @brief Donne n nombre alèatoire
* @param nb le nombre de nombre à tirer
* @param min le minimum des nombre
* @param max le maximum possible
* @return un vecteur des nombre aléatoire
* @details Taux de confiance 100%
* @attention NE PAS FAIRE 2 TIR DANS LA MEME SECONDE la seed est generée a partir du temps
*/
vector<int> random(int nb, int min, int max);

/** @brief Crée un tirage aléatoire
* @return Le tirage sous forme de string
* @details Taux de confiance 100%
*/
string tirtirage();


