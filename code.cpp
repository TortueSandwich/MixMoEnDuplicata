#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>


#include "tools.hpp" 

using namespace std;
typedef vector<vector<char>> Grid;



//* IMPORT VARIABLE GLOBALES
extern Grid grille;
extern Grid vrac;
extern Grid selection;


extern string theme;
extern string tirage;

extern int curseurX; 
extern int curseurY;
extern char curseurC;

extern int premierInvisible;
extern int nombreDeMixMo;
extern bool themeEstRevele;

extern vector<int>  occMax;
extern vector<char> possible;
extern char Bandit;
extern string messageLog;



string litParametres( string nomDuFichier, int n = 0 ){
    ifstream fichier;
    string nomDico,theme,tirage;
    fichier.open("./"+nomDuFichier);
    if (!fichier) throw "Le fichier parametre n'est pas lu !";
    fichier >> nomDico >> theme >> tirage;
    if (n == 0) return nomDico;
    if (n == 1) return theme;
    if (n == 2) return tirage;
    return "5";
}

void afficheTirage (string tirage, int premierCache){
    cout << repeteChar(tirage.size()/4,"-=") <<"- Tirage " << repeteChar(tirage.size()/4 - 2,"=-") << endl;
    cout << "|" << tirage.substr(0 , premierCache) << repeteChar(tirage.size() - premierCache,'?') << "|" << endl; 
    cout << repeteChar(tirage.size()/2 + 1,"-=")+"-" << endl;
}

void ecranDeJeu(Grid vrac, Grid grille, Grid selection, string theme, string tirage, bool motDansTheme, string motsDansLeThemePresent){
    string ecart = "    ";
    string slignevrac = "";
    string slignegrille = "";
    string sGrilleVrac = "";
    string themeAffiche;

    themeAffiche = (themeEstRevele) ? theme : "???";

    // En-tête
    cout << repeteChar(26," =") << " M I X M O " << repeteChar(26,"= ") << endl << endl;

    try{ // Jaime pas ça :(
        afficheTirage(tirage, premierInvisible);
    }catch(const std::exception& e){
        cerr << e.what() << '\n';
    }
    
    cout << repeteChar(2,'_')+ "/ Vrac \\"+repeteChar(12,'_') 
    << ecart + repeteChar(5,'_')+ "/ Grille \\" + repeteChar(49,'_');
    cout << sGrilleVrac << " Nombre de MixMo : " << nombreDeMixMo << endl << "|";

    for(int i = 0; i < vrac[0].size(); i++){
        cout << setw(3) << to_string(i);
    }
    cout << "  |" + ecart + "|";
    for(int i = 0; i < grille[0].size(); i++){
        cout << setw(3) << to_string(i);
    } 
    cout << "  |";
    
    cout << " Theme : " << themeAffiche << endl;
    
    sGrilleVrac = "";
    
    

    cout << "|-" + repeteChar(vrac[0].size()*3,'-') + "-|" + ecart + "|-" + repeteChar(grille[0].size()*3,'-') + "-|";
    if (themeEstRevele && motDansTheme){
        cout << " Mot placé qui est dans le theme : " << motsDansLeThemePresent << endl;
    } else cout << endl;
    

    for( int ligne = 0; ligne < grille[0].size(); ligne++ ){
        string slignevrac = "";
        string slignegrille = "";
        //PARTIE VRAC
        for( int c = 0; c < vrac[0].size(); c++){
            if( selection[ligne][c] != ' ' && selection[ligne][c] != '.' ){
                if (vrac[ligne][c] != ' ' && vrac[ligne][c] != '.'){
                    if(curseurY != ligne || curseurX != c){ //SI SELECTION ET AVEC SUPERPOSITION /// MAIS SANS CURSEUR 
                        slignevrac += selection[ligne][c];
                        slignevrac += "!";
                        slignevrac += vrac[ligne][c];    
                    } else {                                //SI SELECTION ET AVEC SUPERPOSITION /// AVEC CURSEUR 
                        slignevrac += selection[ligne][c];
                        slignevrac += ">";
                        slignevrac += vrac[ligne][c];    
                    }
                } else { 
                    if(curseurY != ligne || curseurX != c){ //SI SELECTION ET sans superposition /// MAIS SANS CURSEUR 
                        slignevrac += "!";
                        slignevrac += selection[ligne][c];
                        slignevrac += "!";  
                    } else {                                //SI SELECTION ET sans SUPERPOSITION /// AVEC CURSEUR 
                        slignevrac += "}";
                        slignevrac += selection[ligne][c];
                        slignevrac += "{";   
                    }
                }
            } else { // SANS SELECTION
                if(curseurY != ligne || curseurX != c){ //SANS SELECTION ET AVEC SUPERPOSITION /// MAIS SANS CURSEUR 
                    slignevrac += " "; 
                    slignevrac += vrac[ligne][c];
                    slignevrac += " ";     
                } else {                                //SANS SELECTION ET AVEC SUPERPOSITION /// AVEC CURSEUR 
                    slignevrac += ">"; 
                    slignevrac += vrac[ligne][c];
                    slignevrac += "<";   
                }

            }
        }
            //slignevrac += (curseurY == ligne && curseurX == c) ? ">" : " ";
            //slignevrac += vrac[ligne][c];
            //slignevrac += (curseurY == ligne && curseurX == c) ? "<" : " ";
        
        //PARTIE GRILLE

        
        for( int c = 0; c < grille[0].size(); c++){
            if( selection[ligne][c + vrac[0].size()] != ' ' && selection[ligne][c + vrac[0].size()] != '.' ){
                if (grille[ligne][c] != ' ' && grille[ligne][c] != '.'){
                    if(curseurY != ligne || curseurX != c){ //SI SELECTION ET AVEC SUPERPOSITION /// MAIS SANS CURSEUR 
                        slignegrille += selection[ligne][c + vrac[0].size()];
                        slignegrille +=  "!";
                        slignegrille += grille[ligne][c];    
                    } else {                                //SI SELECTION ET AVEC SUPERPOSITION /// AVEC CURSEUR 
                        slignegrille += selection[ligne][c + vrac[0].size()];
                        slignegrille +=  ">";
                        slignegrille +=  grille[ligne][c];    
                    }
                } else { 
                    if(curseurY != ligne || curseurX != c + vrac[0].size()){ //SI SELECTION ET sans superposition /// MAIS SANS CURSEUR 
                        slignegrille += "!";
                        slignegrille += selection[ligne][c  + vrac[0].size()];
                        slignegrille +=  "!";  
                    } else {                                //SI SELECTION ET sans SUPERPOSITION /// AVEC CURSEUR 
                        slignegrille += "}";
                        slignegrille += selection[ligne][c  + vrac[0].size()];
                        slignegrille +=  "{";   
                    }
                }
            } else { // SANS SELECTION
                if(curseurY != ligne || curseurX != c + vrac[0].size()){ //SANS SELECTION ET AVEC SUPERPOSITION /// MAIS SANS CURSEUR 
                    slignegrille += " ";
                    slignegrille += grille[ligne][c];
                     slignegrille += " ";    
                } else {                                //SANS SELECTION ET AVEC SUPERPOSITION /// AVEC CURSEUR 
                    slignegrille += ">";
                    slignegrille += grille[ligne][c];
                    slignegrille += "<";    
                }

            }
        }
    cout << "| " << slignevrac << " |" << setw(3) << ligne << " | " << slignegrille << " |" << endl;
    }    
    cout << "|-" + repeteChar(vrac[0].size()*3,'-') + "-|" + ecart + "|-" + repeteChar(grille[0].size()*3,'-') + "-|" << endl;
    cout << sGrilleVrac << endl;       
}

void placedansvrac(char lettre){
    bool estAjoute = false;
    int l = 0;
    if (lettre == Bandit){
        lettre = '+';
    }
    if('a' <= lettre && lettre <= 'z') lettre = '*';

    while (!estAjoute){
        for(int col = 0; col < vrac[0].size(); col++){
            if ((vrac[l][col] == '.' || vrac[l][col] == ' ') && !estAjoute){
                vrac[l][col] = lettre;
                estAjoute = true;
                break;
            }
        }
        l++;
    }
    return;
}

void nouvelleLettre(){
    if (premierInvisible < tirage.size()){
        premierInvisible ++;
        if (premierInvisible <= vrac.size()*vrac[0].size()) placedansvrac(tirage[premierInvisible-1]);
        if ( tirage[premierInvisible-1] == '+' ) themeEstRevele = true;
    } else {
        messageLog += "Il n'y a plus de lettre !";
        premierInvisible = tirage.size();
        return;
    }
    if (premierInvisible < tirage.size()){
        premierInvisible ++;
        if (premierInvisible <= vrac.size()*vrac[0].size()) placedansvrac(tirage[premierInvisible-1]);
        if ( tirage[premierInvisible-1] == '+' ) themeEstRevele = true;
    } else { 
        messageLog += "Il n'y a plus de lettre !";
        return;
    }
}

/****************************
*  verifie si la grille est connexe
*  @param grille à checker
*  @return true/false 
*/
bool estConnexe(Grid grille){
    //fier de la methode
    int changement;
    int numeroDeLaComposante = 1;
    int supmax = ( grille.size() * grille[0].size() ) + 1; // nb jamais atteint si on remplis chaque case par un nb distinct
    vector<vector<int>> maquette = vector<vector<int>>(grille.size() + 2, vector<int>(grille.size() + 2, supmax));
    for(int x = 1; x < grille.size() + 1; x++){
        for(int y = 1; y < grille.size() + 1; y++){
            if (grille[x-1][y-1] == ' '){ // grille = ' '  =>   maquette = supmax
                maquette[x][y] = supmax;
            } else if (maquette[x-1][y] == supmax && maquette[x][y-1] == supmax){ // grille = 'char' isolé   =>    maquette = nouveau nb
                maquette[x][y] = numeroDeLaComposante;

                numeroDeLaComposante++;
            } else { // grille = 'char' relié    =>     maquette = nb proche
                maquette[x][y] = min(maquette[x-1][y],maquette[x][y-1]);

            }
        }    
    }
    if (numeroDeLaComposante > 1) {
        do {
            changement = 0;
            for (int X = 1; X< grille.size() + 1; X++){
                for (int Y = 1; Y< grille.size() + 1; Y++){
                    if (grille[X-1][Y-1] == ' '){
                        maquette[X][Y] = supmax;
                    } else {
                        int ancien = maquette[X][Y];
                        maquette[X][Y] = min( maquette[X][Y] , min( min (maquette[X-1][Y], maquette[X][Y-1]) , min( maquette[X+1][Y], maquette[X][Y+1])));
                    if (maquette[X][Y] != ancien)changement ++;
                    }
                }
            }
        } while (changement > 0 );
    }
    int plusGrandRestant = 0;
    for(int i = 0; i < maquette.size(); i++){ 
        for (int v : maquette[i]){
            if ( v != supmax)
            {
                plusGrandRestant = max(plusGrandRestant,v);
            }  
        }
    }
    return plusGrandRestant == 1 ;
}

vector<string> listeDeMotDeLaGrille(Grid grille){
    vector<string> listeDesMots = vector<string>(0);
    int indiceDebut;
    int indiceFin;
    bool grilleTournee = false;
    string mot;

    litHorizontalement:
    for(int ligne = 0; ligne < grille.size(); ligne++ ){
        for(int indice = 0; indice < grille[ligne].size()-1; indice++){
            if  ( grille[ligne][indice]   !=' ' && grille[ligne][indice+1] !=' '){
                indiceDebut = indice;
                indiceFin = indiceDebut + 1;
                while ( grille[ligne][indiceFin] != ' ' && indiceFin < grille[ligne].size()) {
                    indiceFin++;
                }
                mot = "";
                for (int pos = indiceDebut ; pos < indiceFin; pos++){
                    if(grille[ligne][pos] !=' '){
                        mot += grille[ligne][pos];
                    }
                }
                mot = nettoie(mot);
                if(mot.size() != 0) listeDesMots.push_back(mot);
                indice = indiceFin;
            }
        }
    }
    if (!grilleTournee){
        grille = rotate(grille);
        grilleTournee = true;
        goto litHorizontalement;
    }
    return listeDesMots;
}

bool motDansDico(string mot, string nomDico){
    string referance;
    ifstream motsDuDictionnaire;
    bool present = false;
    motsDuDictionnaire.open("./donnee/" + nomDico);
    if( ! motsDuDictionnaire ) throw invalid_argument("ERREUR A L'OUVERTURE DU DICTIONAIRE : " + nomDico);
    while (motsDuDictionnaire >> referance && !present){
        if (referance == mot) present = true;
    }
    motsDuDictionnaire.close();
    if( !present ) messageLog += "Un mot n'est pas dans le dictionaire ! le voici : " + mot + "\n";
    return present;
}

bool motsDansLeTheme(vector<string> mots, string nomDicoTheme){
    extern string motDuThemePresent;
    string referance;
    ifstream motsDuDictionnaireTheme;
    bool present = false;
    motsDuDictionnaireTheme.open("./donnee/theme_" + nomDicoTheme + ".txt");
    if( ! motsDuDictionnaireTheme ) throw invalid_argument("ERREUR A L'OUVERTURE DU DICTIONAIRE : " + nomDicoTheme);
    while (motsDuDictionnaireTheme >> referance && !present){
        for(string mot : mots){
            if (referance == mot) {
                motDuThemePresent = mot;
                present = true;
            }
        }
    }
    motsDuDictionnaireTheme.close();
    if(!present) motDuThemePresent = "";
    return present;
}


/********************
*/
bool listeDeMotsDansDico( vector<string> listeDeMots,string nomDico){
    bool resultat = true;
    for(string mot : listeDeMots){
        resultat = ( resultat && motDansDico(mot,nomDico) );
    }
    return resultat;
}


bool estValide(Grid grille,string nomDico,bool themeEstRevele, string nomDicoTheme){
    bool valide = true;
    messageLog = "";
    if ( !estConnexe(grille)){
        messageLog = "La grille n'est pas connexe !!! \n";
        valide = false;
    }
    if ( !listeDeMotsDansDico(listeDeMotDeLaGrille(grille),nomDico) ){
        valide = false;
    }
    if (themeEstRevele){
        if ( !motsDansLeTheme(listeDeMotDeLaGrille(grille), nomDicoTheme)){
            valide = false;
            messageLog += "Il faut un mot compris dans le theme !\n";
        }
    }

    int sum = 0;
    for (int i = 0; i < vrac[0].size(); i++){
        for (int j = 0; j < vrac.size(); j++){
            if(vrac[j][i] != ' ' && vrac[j][i] != '.') {
                valide = false;
                messageLog = "L'espace vrac n'est pas vide !";
            }
        }
    }
    return valide;
}


// SCORE
int prochainNombrePremier( int debut ){
    //Methode Crible d'Ératosthène
    vector<bool> tableauDePremier = vector<bool>( debut * debut, true );
    tableauDePremier[0] == false;
    tableauDePremier[1] == false;
    int i = 2;
    for (int j = 4; j <= tableauDePremier.size(); j += 2){
                tableauDePremier[j] = false;
    }
    while (i*i <= tableauDePremier.size()){
        if (tableauDePremier[i] == true){
            for (int j = i*i; j <= tableauDePremier.size(); j += 2*i){
                tableauDePremier[j] = false;
            } 
        }
        i++;
    }
    for (int k = debut + 1; k <tableauDePremier.size(); k++){
        if (tableauDePremier[k] == true) {return k;}
    }
    return -1;
}

int iemeNbPremier(int i){
    if (i<=0) {return -1;}
    if (i<=3) {return i;}
    else {
        return prochainNombrePremier(iemeNbPremier(i-1));
    }
}

int scoreMot( string mot ){
    int n = nettoie(mot).size();
    if ( n <  2  ) return 0;
    if ( n == 2  ) return n *(-200);
    if ( n >= 10 ) return 17 * n;  
    else return n * iemeNbPremier(n-2);
}

int totalscore( vector<string> mots){
    int sum = 0;
    for(string mot : mots){
        sum += scoreMot(mot);
    }
    return sum;
}


void afficheColonnes(int nbColonne){
    cout<< setw(7) <<"/|";
    for (int i = 0; i < nbColonne; i++){    
        cout << "C" << i/10 << i%10 << "|"; 
    }                  //dizaine  unité
    cout << "\\" <<endl;
}
void afficheLigne(int numLigne){   
    cout << "L "<< numLigne/10 << numLigne%10;
}
void afficheSeparation(int nbColonne, char cha){
    cout << setw(7) << "||";
    for (int i = 0;i < nbColonne; i++){    
        cout << repeteChar(3,cha) <<"|"; 
    }
    cout <<"|"<<endl;
}
void afficheGrilleFinale(Grid grille){
    int width = grille[0].size(); 
    afficheColonnes(width);

    afficheSeparation(width,'=');
    
    for (int ligne = 0; ligne < grille.size(); ligne++){
        afficheSeparation(grille[ligne].size(),'-');
        afficheLigne(ligne);                                               //LNB
        cout<<" ]|";                                                       //    ]|
        for (char colonne : grille[ligne]) cout << setw(2) << colonne << setw(2) <<"|"; //       'X'                                                          
        cout << "[";                                                       //           |[
        afficheLigne(ligne);                                               //               LNB
        cout <<endl;
    }
    afficheSeparation(width,'-');
    
    afficheSeparation(width,'=');
    afficheColonnes(width);
}


void afficheScoreFinal(Grid grille){
    // fonction la plus moche
    int score = totalscore(listeDeMotDeLaGrille(grille));
    vector<string> listeMots = listeDeMotDeLaGrille(grille);
    vector<int> listeTaille = vector<int> (listeMots.size());
    vector<int> listePointparLettre = vector<int> (listeMots.size());
    vector<int> listePointMot = vector<int> (listeMots.size());

    for( int i = 0; i < listeMots.size(); i++){
        listeTaille[i] = listeMots[i].size();
        if (listeTaille[i]==2) listePointparLettre[i] = -200; 
        else listePointparLettre[i] = (listeTaille[i] < 10) ? iemeNbPremier(listeTaille[i] - 2) : 17;
        listePointMot[i] = scoreMot(listeMots[i]);
    }

    int tailleMotLePlusGrand = 0;

    for(string s : listeMots) tailleMotLePlusGrand = tailleMotLePlusGrand < s.size() ? s.size() : tailleMotLePlusGrand;
    int tailleMotLePlusPetit = tailleMotLePlusGrand;
    for(string s : listeMots) tailleMotLePlusPetit = tailleMotLePlusPetit > s.size() ? s.size() : tailleMotLePlusPetit;
    tailleMotLePlusGrand = (tailleMotLePlusGrand % 2 == 0) ? tailleMotLePlusGrand :  tailleMotLePlusGrand + 1;
    string s1 = "Mot";
    string s2 = "Taille";
    string s3 = "Points/lettre";
    string s4 = "Points du mot";
    string range =  to_string(tailleMotLePlusPetit) + " a " + to_string(tailleMotLePlusGrand) + "lettres" ;
//entête
    cout << "__"+ repeteChar(tailleMotLePlusGrand +range.size() +s3.size() + s4.size(),'_')+"__"+"___"+"___"+"___\n"; 
    cout << "|" + repeteChar((tailleMotLePlusGrand + range.size() + s3.size() + s4.size())/2 + 2,' ')+" Scores "+repeteChar((tailleMotLePlusGrand + range.size()+1 + s3.size() + s4.size())/2 + 1,' ')+"| \n";
    cout << "|"+ repeteChar(tailleMotLePlusGrand +range.size() +s3.size() + s4.size() + 11,'-')+"|\n"; 

    cout << "|" + repeteChar(tailleMotLePlusGrand/2 - 1,' ') << s1 << repeteChar(tailleMotLePlusGrand/2 - 1,' ')<<" | " << repeteChar(range.size()/2 -2, ' ') << s2  << repeteChar(range.size()/2 -3, ' ') <<" | " << s3 <<" | " << s4 <<" | " << endl; 
    cout << "|="+ repeteChar(tailleMotLePlusGrand,'=')+"=|="+repeteChar(range.size(),'=')+"=|="+repeteChar(s3.size(),'=')+"=|="+repeteChar(s4.size(),'=')+"=| \n";
//body
    for(int i = 0; i < listeMots.size(); i++){
        cout << "| " 
                                    << listeMots[i]           << repeteChar(tailleMotLePlusGrand-listeMots[i].size(), ' ')  <<" | "
        << setw(range.size()/2 + 1) << listeTaille[i]         << repeteChar(range.size()/2 ,' ')            <<" | "
        << setw(s3.size()/2 + 2)    << listePointparLettre[i] << repeteChar(s3.size()/2 -1 , ' ')          <<" | "
        << setw(s4.size()/2 + 2)    << listePointMot[i]       << repeteChar(s4.size()/2 -1, ' ')           <<" |" 
        << endl; 
    }
    cout << "|-"+ repeteChar(tailleMotLePlusGrand,'-')+"-|-"+repeteChar(range.size(),'-')+"-|-"+repeteChar(s3.size(),'-')+"-|-"+repeteChar(s4.size(),'-')+"-| \n";
//feets
    cout << "| " <<  "Total :" << repeteChar(tailleMotLePlusGrand - 7, ' ') << "| " << range << " | " << setw(s3.size()) << to_string(listeMots.size()) + " mots" << " | " << setw(s4.size())<< "Score : " + to_string(score) << " |\n";
    cout << "|-"+ repeteChar(tailleMotLePlusGrand,'-')+"-|-"+repeteChar(range.size(),'-')+"-|-"+repeteChar(s3.size(),'-')+"-|-"+repeteChar(s4.size(),'-')+"-| \n";
}

void finDePartie(Grid grille){
    afficheGrilleFinale(grille);
    afficheScoreFinal(grille);
}

void mixmo(Grid grille, string nomDico, bool themeEstRevele, string nomDicoTheme){
    if (!estValide(grille, nomDico, themeEstRevele, nomDicoTheme)){
        messageLog += "\nLa grille n'est pas valide !";
        return;
    }
    if (premierInvisible < tirage.size()){
        nombreDeMixMo ++;
        nouvelleLettre();
        messageLog = "Bravo !! Voici deux nouvelles lettres";
        return;
    } else {
        nombreDeMixMo ++;
        extern char action;
        action = 'q';
    }
}


char afficheActionPossible(bool toggle){
    char action;
    string actif = (toggle)? "Actif" : "desactif";
    cout << "Bouger selection : " << actif << endl;
    cout << "M = MixMo !" << endl;
    cout << "V = verifier l'existance d'un mot" << endl;
    cout << "Y = verifier si la grille est valide" << endl;
    cout << "S = ajoute a la selection" << endl;
    cout << "P = Poser la selection" << endl;
    cout << "D = Donne 2 nouvelles lettres" << endl;
    cout << "O = Affiche le tableaux des occurances" << endl;
    if (messageLog.size() > 0) cout << ">>> " + messageLog << endl;
    messageLog = "";
    cout << "Que veux tu faire ? : " << endl;
    cin >> action;
    return action;
}


void afficheTableauDesOccurencesDesJetons(Grid grille){
    vector<string> display = {"lettre","max", "pose"};
    int disp = 0;
    for(string s : display) if (disp < s.size()) disp = s.size();
    

    vector<int> tabOcc = vector<int>(possible.size());
    for( int i = 0; i < possible.size(); i++){
        tabOcc[i] = nbdejetonpose(grille, possible[i]); 
    }

    cout << repeteChar(4 * (possible.size() + 1) + disp,"_") << endl;     //-------

    cout << "|" << setw(disp + 1) << display[0] << setw(2) << "|";
    for( char lettre : possible){                                         //LETTRES
        cout << setw(2) << lettre << setw(2) << "|";
    } cout << endl;
    
    cout << "|" << repeteChar(disp + 2,'=') << "|";                       //=======
    for( int i = 0; i < possible.size(); i++){    
        cout << repeteChar(3,'=') << "|";
    } cout << endl;
    
    cout<<"|" << setw(disp+1) << display[1] << setw(2) << "|";           //  MAX
    for( int i = 0; i < possible.size(); i++){      
        cout << setw(2) << occMax[i] << setw(2) << "|";
    } cout << endl;

    cout << "|" << repeteChar(disp + 2,'-') << "|";                      // - - -
    for( int i = 0; i< possible.size(); i++){    
        cout << repeteChar(3,'-') << "|";
    } cout << endl;

    cout<<"|" << setw(disp + 1) << display[2] << setw(2) << "|";        // POSéS
    for( int i = 0; i< possible.size(); i++){    
        cout<< setw(2) << tabOcc[i] << setw(2) <<"|";
    } cout << endl;

    cout << "|" << repeteChar(disp+2,'_') << "|";                       // ____
    for( int i=0; i<possible.size(); i++){    
        cout << repeteChar(3,'_') << "|";
    } cout << endl;

    /*for( int i=0; i<possible.size(); i++){    
        cout<<"|";
        if ( occMax[i]-tabOcc[i] < 0 ) cout<<  setw(3) << "ERR" ; 
        else if ( occMax[i]-tabOcc[i] == 0 ) cout<<  setw(2) << "O" << setw(2);
        else cout<<repeteChar(3,' ');    
    }
    cout << "|" << endl;*/
    cout << endl;
}