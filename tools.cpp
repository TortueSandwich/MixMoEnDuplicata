#include <string>
#include <fstream>
#include <map>
#include <ctime>

#include "tools.hpp"
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

using namespace std;
typedef vector<vector<char>> Grid;

extern map<char,int> jetonsLettres;
extern vector<char> possible;
extern vector<int> occMax;

string repeteChar(int n,char c){
    string ecrit = "";
    for (int i=0; i< n; i++){
        ecrit += c;
    }
    return ecrit;
}
string repeteChar(int n,string c){
    string ecrit = "";
    for (int i=0; i< n; i++){
        ecrit += c;
    }
    return ecrit;
}

char nettoie(char c){
    if ('a' <= c && c <= 'z'){ 
        return char(c +'A'-'a'); 
    }                 //lettre + 26
    if ('A'<=c && c <='Z'){
        return c;
    }
    return ' ';       
}

string nettoie(string motsale){
    string propre = "";
    for (char lettre : motsale){
        if ('a' <= lettre && lettre <= 'z'){ 
            propre += char(lettre +'A'-'a'); 
        }                 //lettre + 26
        if ('A'<=lettre && lettre <='Z'){
            propre += lettre;
        }
    }
    return propre;       
}


vector<vector<char>> rotate(vector<vector<char>> grid){
    vector<vector<char>> result = vector<vector<char>>( grid[0].size(),vector<char>( grid.size() ) );
    for (int Y = 0; Y < result.size(); Y++){
        for (int X = 0; X < result[Y].size(); X++){
               result[X][Y] = grid[Y][X];
        }
    }
    return result;
}

int nbdejetonpose(Grid grid){
    int count = 0;
    for(vector<char> l : grid){
        for(char c : l){
            if (c != ' ')count++;
        }
    }
    return count;
}
int nbdejetonpose(vector<vector<char>> grid, char L){
    int count = 0;
    extern char Bandit;
    if(L == '+'){
        for(vector<char> l : grid){
            for(char c : l){ 
                if (c == Bandit) {
                    count++; 
                }
            }
        }
    }
    if(L == '*'){
        for(vector<char> l : grid){
            for(char c : l){ 
                if (c >= 'a' && c < 'z' && c != Bandit) {
                    count++; 
                }
            }
        }
    return count;
    }
    for(vector<char> l : grid){
        for(char c : l){
            if (c == L)count++;
        }
    }
    return count;
}



vector<int> random(int nb = 1, int min = 0, int max = 100){
    vector<int> r = vector<int> (nb); 
    srand((unsigned) time(0));
    max = max - min + 1;

    for (int i = 0; i != nb ; i++){
        r[i] = (rand() % max) + min;
    }
    return r;
}
/*TIRAGE*/
string tirtirage(){
    vector<char> jetons;
    for(char c : possible){
        for (int i = 0; i < jetonsLettres[c]; i++){
            jetons.push_back(c);
        }
        
    }
    vector<char> lettres = vector<char>(120); // Tableau avec les lettres tirées
    vector<int> nbASCII = random(lettres.size(), int('A'), int('Z') + 2);
    int count = 0;

    for(int posl = 0; posl < lettres.size(); posl++){
        int nbale = nbASCII[count];
        char cha = jetons[nbale % jetons.size()];

        if (jetonsLettres[cha] != 0){
            lettres[posl] = cha;
            jetonsLettres[cha]--;
            jetons.erase(jetons.begin() + (nbale % jetons.size()));
            count++;
        } else {
           posl--; 
        }
        
    } 
    string tirage(lettres.begin(), lettres.end());
    return tirage;
}