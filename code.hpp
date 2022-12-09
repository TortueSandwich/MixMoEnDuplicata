#include <string>

using namespace std;

typedef vector<vector<char>> Grid;

string litParametres( string nomDuFichier, int n = 0 );

/** @brief les lettres tirées visible, les caché sont remplacé par des "???"
* @param tirage : le tirage
* @param premierCache : position de la 1ere lettre cachée 
* @bug Quand on utilise un tirage aleatoire
* @details Taux de confiance 80%
*/
void afficheTirage(string tirage, int premierCache);

/** @brief l'ecran de jeu ( Grille + Vrac )
* @param vrac : vrac a ce tour
* @param grille : grille a ce tour
* @param selection : la selection a ce tour
* @param theme : le theme de la partie
* @param tirage : le tirage de la partie
* @param motDansTheme si il y a un mot dans le theme
* @param motsDansLeThemePresent le mot du theme qui est present
* @details taux de confiance : 99% (cf bug affiche tirage)
*/
void ecranDeJeu(Grid vrac, Grid grille, Grid selection, string theme, string tirage, bool motDansTheme, string motsDansLeThemePresent);

/** @brief Place une lettre dans le vrac
* @param lettre : la lettre a placer
* @details Taux de confiance 100% si vrac.size() > nombre de jeton
*/
void placedansvrac(char lettre);

/** @brief Devoile DEUX nouvelles lettres
*
*/
void nouvelleLettre();

/** @brief Verrifie la connexité d'une grille
* @param grille : la grille a verifier
* @return true ou false
* @details Taux de confiance 100%
* @cite J'en suis fier
*/
bool estConnexe(Grid grille);

/** @brief Donne la liste des mots de la grille
* @param grille : la grille a controler
* @return un vecteur des mots
* @details Taux de confiance : 100%
*/
vector<string> listeDeMotDeLaGrille(Grid grille);

/** @brief regarde si le mot est dans le dictionnaire
* @param mot : le mot a regarder
* @param nomDico Nom du dictionnaire
* @return true ou false
* @details Taux de confiance 100%
*/
bool motDansDico(string mot, string nomDico);

/** @brief regarde si le mot est dans le dictionnaire du theme
* @param mot : le mot a regarder
* @param nomDico Nom du dictionnaire
* @return true ou false
* @details Taux de confiance 100%
*/
bool motsDansLeTheme(vector<string> mots, string nomDicoTheme);

/** @brief check si une liste de mot est dans le dictionnaire
* @param listeDeMots : la liste de mot
* @param nomDico Nomdu dictionnaire
* @return true ou false
* @details Taux de confiance 100%
*/
bool listeDeMotsDansDico( vector<string> listeDeMots, string nomDico);

/** @brief Check si une grille est conforme au MixMo
* @param grille la grille en question
* @param nomDico Nomdu dictionnaire
* @param themeEstRevele si le theme est revele
* @param nomDicoTheme nom du dictionnaire de theme
* @return true ou false
* @details Taux de confiance : 100%
*/
bool estValide(Grid grille, string nomDico, bool themeEstRevele, string nomDicoTheme);

/** @brief Trouve le 1er nombre 1er apres un nombre de depart
* @param debut le nombre de depart
* @return Le nombre premier trouvé
* @details Taux de confiance 100%
*/
int prochainNombrePremier( int debut );

/** @brief le ieme nombre premier en partant de 0
* @param i : indice du nombre 1er a trouver
* @return : le nombre 1er trouvé
* @details Taux de confiance 100%
*/
int iemeNbPremier(int i);

/** @brief Donne le score obtenu pour un mot
* @param mot le mot en question
* @return le score du mot
* @details Taux de confiance 100%
*/
int scoreMot( string mot );

/** @brief Dans le score total d'une liste de mot
* @param mots La liste de mots
* @details Taux de confiance 100%
*/
int totalscore( vector<string> mots);

/** @brief Affiche le nom des colonnes */
void afficheColonnes(int nbColonne);
/** @brief affiche une ligne */
void afficheLigne(int numLigne);
/** @brief affiche une separation */
void afficheSeparation(int nbColonne, char cha);
/** @brief Affiche une grille propre mais plus grande */
void afficheGrilleFinale(Grid grille);

/** @brief Affiche un tableau de scores finaux
* @param grille la grille a l'état
* @details Taux de confiance 100%
*/
void afficheScoreFinal(Grid grille);

/** @brief Affiche la grille et le score final
* @param la grille a l'etat
* @details Taux de confiance 100%
*/
void finDePartie(Grid grille);

/** @brief Bouton MixMo
* @param grille la grille a l'état
* @param nomDico Nom du dictionnaire general
* @param themeEstRevele si le theme est revelé
* @param nomDicoTheme Nom du dictionnaire theme  
* @details Taux de confiance 100%
*/
void mixmo(Grid grille, string nomDico, bool themeEstRevele, string nomDicoTheme);

/** @brief Affiche les actions possibles et demande a l'user de rentrer ce qu'il veut faire
* @param toogle Etat du deplacement de la selection
*/
char afficheActionPossible(bool toogle);

/** @brief affiche un tableau avec les occurances des jetons
* @param grille Lagrille a l'etat
*/
void afficheTableauDesOccurencesDesJetons(Grid grille);


int tests();