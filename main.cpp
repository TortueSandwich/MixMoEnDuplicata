#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <map>

#include "code.hpp"
#include "tools.hpp"
#include "selection.hpp"

using namespace std;

typedef vector<vector<char>> Grid;







//* IMPORT PARAMETE DE "parametre.txt"
string nomDico = litParametres("parametres.txt", 0);
string theme = litParametres("parametres.txt", 1);
string tirage = litParametres("parametres.txt", 2);
//string tirage = tirtirage();*

//* VARIABLES GLOBALES
// grille/vrac (initialisation)
Grid grille = Grid(20,vector<char>(20,' '));
Grid vrac = Grid(20,vector<char>(6,'.'));
// curseur
int curseurX = 0; 
int curseurY = 0;
char curseurC = ' ';

// etat partie
int premierInvisible = 0;
int nombreDeMixMo = 0;
bool themeEstRevele = false;
string motDuThemePresent;

int nbDeMotTourPrecedent = 0;



string messageLog = "";


char Bandit = '+'; 



                                  //   65  //? '*' = Joker   '+' = Bandit
std::map<char,int> jetonsLettres {{'A',10},{'B', 2},{'C', 3},{'D', 4},{'E',17},{'F', 2},{'G', 3},{'H', 3},
                                  {'I', 9},{'J', 2},{'K', 1},{'L', 6},{'M', 3},{'N', 7},{'O', 7},{'P', 3},
                                  {'Q', 2},{'R', 6},{'S', 7},{'T', 7},{'U', 6},{'V', 3},{'W', 1},{'X', 1},
                                  {'Y', 1},{'Z', 1},{'*', 2},{'+', 1}};
                                //        26          42      43
                                //             28 au total

vector<char> possible = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','*','+'};
vector<int>  occMax   = { 10,  2,  3,  4, 17,  2,  3,  3,  9,  2,  1,  6,  3,  7,  7,  3,  2,  6,  7,  7,  6,  3,  1,  1,  1,  1,  2,  1};

;
Grid selection = Grid(vrac.size(),vector<char>(vrac[0].size() + grille[0].size() ,' '));

char action;
int main(){

    tests();
    messageLog = "";
    vector<string> listeDeMotTourPrecedent;
    string motVerifier;
    bool toggleBougerSelection = false;
    bool motDansTheme = false;
    bool afficheOcc = false;
    for ( int i = 0; i < 3; i++) nouvelleLettre();



    // JEUUUUUUUUUUUUU
    do{
        //system("cls");
        curseurC = merge()[curseurY][curseurX];

        ecranDeJeu(vrac, grille, selection, theme, tirage, motDansTheme, motDuThemePresent);
        if (afficheOcc) {
            afficheTableauDesOccurencesDesJetons(grille);
            afficheOcc = !afficheOcc;
        }
        action = afficheActionPossible(toggleBougerSelection);
        if ('a' <= action && action <= 'z'){ 
            action = char(action +'A'-'a'); 
        }     

        switch (action){
            case 'M':
                mixmo(grille, nomDico, themeEstRevele, theme);
                break;
            case 'V':
                cout << endl << "Quel mot veux tu verifer ? :" << endl; 
                cin >> motVerifier;
                if (!motDansDico(nettoie(motVerifier),nomDico)) messageLog = "Ce mot n'est pas dans le dictionnaire !!";
                else messageLog = "Ce mot est bien dans le dictionnaire.";
                break;
            case 'Y':
                if (!estValide(grille,nomDico,themeEstRevele,theme)) messageLog += "La grille n'est pas valide !!";
                else messageLog = "La grille est valide.";
                break;
            case 'S':
                selectioner(curseurX,curseurY,curseurC);
                messageLog = "Selection effectuée";
            //TODO Ne marche pas
                /*
                if (listeDeMotTourPrecedent != listeDeMotDeLaGrille(grille)){
                    listeDeMotsDansDico(listeDeMotDeLaGrille(grille),nomDico);
                    if(motsDansLeTheme(listeDeMotDeLaGrille(grille),theme)){ 
                        motDansTheme = true;
                    } else {
                        motDansTheme  = false;
                    }
                }
                listeDeMotTourPrecedent = listeDeMotDeLaGrille(grille);
                */
            //TODO
                break;
            case 'P':
                poseSelection();
                messageLog = "Selection posée";
            //TODO Ne marche pas
                /*
                if (listeDeMotTourPrecedent != listeDeMotDeLaGrille(grille)){
                    listeDeMotsDansDico(listeDeMotDeLaGrille(grille),nomDico);
                    if(motsDansLeTheme(listeDeMotDeLaGrille(grille),theme)){ 
                        motDansTheme = true;
                    } else {
                        motDansTheme  = false;
                    }
                }
                listeDeMotTourPrecedent = listeDeMotDeLaGrille(grille);
                */
            //TODO
                break;
            case 'D':
                nouvelleLettre();
                break;
            case 'O':
                afficheOcc = true;
                break;
            case 'J':
                envoieAuVrac(curseurX, curseurY);
                break;
            case '5':
                toggleBougerSelection = !toggleBougerSelection;
                messageLog = "Etat de deplacement a ete change!";
                break;
            case '8':
                curseurY = incluY(curseurY-1,merge());
                if (toggleBougerSelection) bougeSelectionHaut();
                break;
            case '4':
                curseurX = incluX(curseurX-1,merge());
                if (toggleBougerSelection) bougeSelectionGauche();
                break;
            case '2':
                curseurY = incluY(curseurY+1,merge());
                if (toggleBougerSelection) bougeSelectionBas();
                break;
            case '6':
                curseurX = incluX(curseurX+1,merge());
                if (toggleBougerSelection) bougeSelectionDroite();
                break;    
            case 'Q':
                action = 'q';    
                break;
            default:
                break;
        }

        string sum = "";
        for(int X = 0; X < vrac[0].size(); X++){
            for(int Y = 0; Y < vrac.size(); Y++){
                if(vrac[Y][X] != ' ' && vrac[Y][X] != '.'){
                    sum += vrac[Y][X];
                }
            }
        }
        if(sum.size() == 0) mixmo(grille,nomDico,themeEstRevele,theme);

    } while ( action != 'q');

    finDePartie(grille);
    return 0;
}
