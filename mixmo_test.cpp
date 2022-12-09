#include <stdexcept>
#include <iostream>
#include <vector>

#include "code.hpp"
#include "selection.hpp"
#include "tools.hpp"
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

typedef vector<vector<char>> Grid;

Grid grilleConsigne = {{'I','C','I',' ','O','N','T',' ','D','O','S',' ','S'},
                       {'R','I','R','E','S',' ','A','N','E',' ','U','N','I'},
                       {'A','M','E',' ','E','R','S',' ','S','O','R',' ','X'},
                       {' ','E',' ',' ',' ','U',' ',' ',' ','S',' ',' ',' '},
                       {'O','S','A',' ','R','E','A',' ','N','E','S',' ','C'},
                       {'N',' ','N',' ','E',' ','I','V','E',' ','O','V','E'},
                       {'T','A','S',' ','E','U','T',' ','T','O','T',' ','T'},
                       {' ','R',' ',' ',' ','N',' ',' ',' ','D',' ',' ',' '},
                       {'P','A','S',' ','T','E','R',' ','D','E','R',' ','V'},
                       {'O',' ','A','M','I',' ','E','T','E',' ','Y','U','E'},
                       {'T','A','C',' ','R','I','Z',' ','S','U','E',' ','R'},
                       {' ','L',' ',' ',' ','V',' ',' ',' ','N',' ',' ','T'},
                       {'N','E','S',' ','B','E','E',' ','A','S','T','R','E'}};

Grid grilleErreur = {{'N','O','T','E'},
                     {' ',' ',' ',' '},
                     {' ','C','A','S'},
                     {' ',' ',' ',' '}};




int tests(){

    clog << "lancement des tests : " << endl;

    CHECK( repeteChar(5,'t') == "ttttt");
    CHECK( repeteChar(0,"y") == "");

    CHECK(nettoie('b') == 'B');
    CHECK(nettoie("string") == "STRING");

    Grid quad;
    quad = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    Grid tourn = {{'1','4','7'},{'2','5','8'},{'3','6','9'}};
    CHECK(rotate(quad) == tourn);

    CHECK(nbdejetonpose(quad) == 9);
    CHECK(nbdejetonpose(quad,'1') == 1);


    Grid vracT = {{'.','.'},{'1','2'}};
    Grid grilleT = {{' ',' '},{'3','4'}};
    Grid mergedT = {{'.','.',' ',' '},{'1','2','3','4'}};
    CHECK(merge(vracT,grilleT) == mergedT);
    
    CHECK(incluX(-1,mergedT) == 3);
    CHECK(incluX(4,mergedT) == 0);
    

    CHECK(incluY(-1,mergedT) == 1);
    CHECK(incluY(4,mergedT) == 0);

    CHECK(estConnexe(grilleConsigne));
    CHECK(!estConnexe(grilleErreur));

    vector<string> motsGrilleErreur = {"NOTE","CAS"};
    CHECK(listeDeMotDeLaGrille(grilleErreur) == motsGrilleErreur);
    
    CHECK(motDansDico("PATATE","dictionnaire78854mots.txt"));
    vector<string> mots = {"PATATE","NOTE","NOTES"};
    CHECK(listeDeMotsDansDico(mots,"dictionnaire78854mots.txt"));
    vector<string> motsincorrect = {"PATOTOE","POTEX","NOTIS"};
    CHECK(!listeDeMotsDansDico(mots,"dictionnaire78854mots.txt"));

    CHECK(estValide(grilleConsigne,"dictionnaire78854mots.txt", false,"emotions"));
    CHECK(!estValide(grilleErreur,"dictionnaire78854mots.txt", false, "emotions"));

    CHECK(prochainNombrePremier(27) == 29);
    CHECK(iemeNbPremier(5) == 7);
    CHECK(iemeNbPremier(0) == -1);
    CHECK(iemeNbPremier(2) == 2);
    
    CHECK(scoreMot("DA") == -400);
    CHECK(scoreMot("AVION") == 15);
    CHECK(scoreMot("A") == 0);
    CHECK(scoreMot("AAAAAAAAAA") == 170);

    CHECK(totalscore( listeDeMotDeLaGrille(grilleConsigne)) == 228 );
        
    vector<string> motsSport = {"FOOT","BALLON"};
    CHECK(motsDansLeTheme(motsSport,"sports"));

    clog << "fin des test" << endl;
    return 0;
}