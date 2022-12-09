#include <vector>

#include <iostream>

#include "code.hpp"
#include "tools.hpp" 

using namespace std;
typedef vector<vector<char>> Grid;

extern Grid vrac;
extern Grid grille;
extern Grid selection;



extern char Bandit;
extern string messageLog;

Grid merge(Grid vracM = vrac, Grid grilleM = grille){
    Grid merged;
    merged = Grid(vracM.size(), vector<char>(vracM[0].size() + grilleM[0].size(), 'P' ));
    for(int Y = 0; Y < vracM.size(); Y++){
        for(int X = 0; X < vracM[0].size(); X++){
            merged[Y][X] = vracM[Y][X];
        }
        for(int X = 0; X < grilleM[0].size(); X++){
            merged[Y][X + vracM[0].size()] = grilleM[Y][X];
        }
    }
    return merged;
}


int incluX( int x, Grid grille ){
    return (x + grille[0].size()) % grille[0].size();
}
int incluY( int y, Grid grille ){
    return (y + grille.size()) % grille.size();
}

void selectioner(int x, int y, char c){
    char memoire;
    // DESELECTION
    if ( char(c) == '.' || char(c) == ' ' ){
        if ( selection[y][x] != ' ' && selection[y][x] != '.'){
            if (x < vrac[0].size()){
                vrac[y][x] = selection[y][x];
            } else {
                grille[y][x - vrac[0].size()] = selection[y][x];
            }
            selection[y][x] = ' ';
        }
    } else { // SELECTION
        if ( selection[y][x] != ' ' && selection[y][x] != '.'){
            memoire = (x < vrac.size())? vrac[y][x] : grille[y][x - vrac[0].size()];
            placedansvrac(memoire);
        }
        if (x < vrac[0].size() && y < vrac.size()){
            vrac[y][x] = '.';
        } else grille[y][x - vrac[0].size()] = ' ';
        selection[y][x] = c;
    }   
}

void bougeSelectionHaut(){
    Grid old = selection;
    for(int Y = 0; Y < selection.size(); Y++){
        for(int X = 0; X < selection[0].size(); X++){
            selection[Y][X] = old[incluY(Y+1,selection)][X];
        }
    }
} 
void bougeSelectionGauche(){
    Grid old = selection;
    for(int Y = 0; Y < selection.size(); Y++){
        for(int X = 0; X < selection[0].size(); X++){
            selection[Y][X] = old[Y][incluX(X+1, selection)];
        }
    }
} 
void bougeSelectionBas(){
    Grid old = selection;
    for(int Y = 0; Y < selection.size(); Y++){
        for(int X = 0; X < selection[0].size(); X++){
            selection[Y][X] = old[incluY(Y-1,selection)][X];
        }
    }
} 
void bougeSelectionDroite(){
    Grid old = selection;
    for(int Y = 0; Y < selection.size(); Y++){
        for(int X = 0; X < selection[0].size(); X++){
            selection[Y][X] = old[Y][incluX(X-1, selection)];
        }
    }
} 


void poseSelection(){
    char memoire;
    char valJeton;
    for(int Y = 0; Y < selection.size(); Y++){
        for(int X = 0; X < selection[0].size(); X++){
            if (selection[Y][X] == ' ' || selection[Y][X] == '.') {
                continue;
            }else{
                if (selection[Y][X] == '*'){
                    do {
                        cout << "entez la valeur du Joker : \n";
                        cin >> valJeton;
                        if ('A' <= valJeton && valJeton <= 'Z') valJeton = char(valJeton - 'A'-'a'); 
                    }while ( 'a' <= valJeton && valJeton <= 'z' );   
                
                } else if ( selection[Y][X] == '+'){
                    do {
                        cout << "entez la valeur du Bandit (k, w, x, y ou z) : \n";
                        cin >> valJeton;
                        if ('A' <= valJeton && valJeton <= 'Z') valJeton = char(valJeton - 'A'-'a');    
                        Bandit = valJeton;
                    }while (valJeton != 'k' && valJeton != 'w' && valJeton != 'x' && valJeton != 'y' && valJeton != 'z' ); 

                } else {
                    valJeton = selection[Y][X];
                }  
                   
                if( X < vrac[0].size() && Y < vrac.size()){
                      //Dans vrac
                    if ( vrac[Y][X] != '.'){
                       memoire = vrac[Y][X]; 
                       vrac[Y][X] = valJeton;
                       placedansvrac(memoire);
                       
                    } else vrac[Y][X] = valJeton;
                } else {    
                    //Dans grille
                    if ( grille[Y][X - vrac[0].size()] != ' '){
                        memoire = grille[Y][X  - vrac[0].size()]; 
                        placedansvrac(memoire);
                        grille[Y][X - vrac[0].size()] = valJeton;
                       
                    } else grille[Y][X - vrac[0].size()] = valJeton;
                }

            }
        }
    }
    //reset selection
    for(int Y = 0; Y < selection.size(); Y++){
        for(int X = 0; X < selection[0].size(); X++){
            selection[Y][X] = ' ';
        }
    }
    return;
}

void envoieAuVrac(int X, int Y){
    char memoire;
    if( X < vrac[0].size()){
        if (vrac[Y][X] != '.'){
            memoire = vrac[Y][X];
            vrac[Y][X] = '.';
            placedansvrac(memoire);
            return;
        }
    } else if(grille[Y][X - vrac[0].size()] != ' '){
        memoire = grille[Y][X - vrac[0].size()];
        grille[Y][X - vrac[0].size()] = ' ';
        placedansvrac(memoire);
        return;
    }
    //grille vide mais selection pleine
    if (selection[Y][X] != ' '){ 
        memoire = selection[Y][X];
        selection[Y][X] = ' ';
        placedansvrac(memoire);
        return;
    }
    return;
}