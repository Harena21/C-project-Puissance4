#include <iostream>
#include <ctime>      //pour inclure la randomisation
#include <vector>     //pour les vector
#include <algorithm>

using namespace std;

enum {VOID,CIRCLE,CROSS};     //enumeration pour faciliter l'ajout des croix et des ronds
class Player  {            //Classe player
public:
    Player();               ///constructor
    Player(int pid);
    int getId();            ///accessor
    void setId(int pid);    ///mutator
protected:
    int id;             //attribut
};
class Grid {     //la classe pour la grille
public:
    Grid();     //le constructeur
    void display();     //pour afficher la grlle
    void add(Player& player);       //pour ajouter une croix ou un rond selon le joueur
    int gameWinnerLine(Player& player);     //pour vérifier si 4 croix ou ronds sont alignés horizontalement et successivement
    int gameWinnerCol(Player& player);       //pour vérifier si 4 croix ou ronds sont alignés horizontalement et successivement
    int gameWinnerDiagonalupRight(Player& player);   //pour vérifier si 4 croix ou ronds sont alignés diagonalement et successivement vers le haut à droite
    int gameWinnerDiagonaldownRight(Player& player);  //pour vérifier si 4 croix ou ronds sont alignés diagonalement et successivement vers le bas à droite
    int gameWinnerDiagonalupLeft(Player& player);       //pour vérifier si 4 croix ou ronds sont alignés diagonalement et successivement vers le haut à gauche
    int gameWinnerDiagonaldownLeft(Player& player);     //pour vérifier si 4 croix ou ronds sont alignés diagonalement et successivement vers le bas à gauche
    int gameCheck(Player& player);                      //pour englober tous les test si un joueur gagne la partie
private:
    int i, j ;          //les attributs de la classe
    int tab[8][8];      //tableau pour la grille
};
class Menu{  ///classe Menu
public:     /// Les méthodes
    Menu();		        /// constructeur du menu
    ~Menu();            /// destructor du menu
    int  display();		/// accessor du menu pour l'afficher
private:    /// Les attributs
    int 	choice;		/// choix de l'utilisateur
    int		nbOps;		/// nombre d'options du menu
    string* ops;		/// tableau de textes du menu
};
class AIComputer : public Player {  //classe computer qui hérite de la classe player
public:
    AIComputer();       ///constructeur
};

bool checkList(vector <int>&tab,int number); // fonction pour vérifier si une valeur est dans un tableau
// void displayVect(vector<int> &tab);
///définition des méthodes de la classe Player
Player::Player(){    //constructeur vide de Player
    id = 0 ;
}
Player::Player(int pid){  //constructeur avec paramètre de player
    id = pid ;
}
int Player::getId(){      //accessor de Player
    return id ;
}
void Player::setId(int pid){   //mutator de player
    id = pid ;
}
///définition des méthodes de la classe Grid
Grid::Grid(){       //Constructeur vide de la classe Grid
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
        {
            tab[i][j] = 0 ;
        }
    }
}
void Grid::display(){       //méthodes pour afficher la grille 
    for(i=0 ; i<8 ; i++){
        for(j=0 ; j<8  ; j++){
            if(j==0){
                if (tab[i][j] == VOID)
                    cout << "| " << "-" << " | " ;
                else if(tab[i][j]==CIRCLE)
                    cout << "| " << "o"<< " | " ;
                else if(tab[i][j]==CROSS)
                    cout << "| " << "x" <<" | " ;
            }
            else{
                if (tab[i][j] == VOID/*   zvtr */)
                    cout<< "-" << " | " ;
                else if(tab[i][j]==CIRCLE)
                    cout << "o" << " | " ;
                else if(tab[i][j]==CROSS)
                    cout << "x" <<" | " ;
            }
        }
        cout << endl ;
    }
    cout << "---------------------------------" << endl ;
    for(i=0 ; i<=8 ; i++){
        if(i==0)
            cout << "  " ;
        else
            cout << i << "   " ;
    }
    cout << endl ;
}
void Grid::add(Player& player){  ////méthode de la classe grille pour faire jouer un joueur humain ou ordinateur y compris
    int number(0);              //variable pour la colonne à remplir
    vector<int> prev_number;

    if(player.getId()==0){
        cout << "It's player 1's turn" << endl ;
        cout << "Enter your column between 1 and 8:" ;       //colonne a remplir par le joueur
        cin >> number ;     
        while(number<1 || number>8){
        cout << "warning!! Enter your column between 1 and 8:" ;       //colonne a remplir par le joueur
        cin >> number ;
        }
    }
    else if(player.getId()==1){
        cout << "It's player 2's turn" << endl ;
        cout << "Enter your column between 1 and 8:" ;       //colonne a remplir par le joueur
        cin >> number ;     
        while(number<1 || number>8){
        cout << "warning!! Enter your column between 1 and 8:" ;       //colonne a remplir par le joueur
        cin >> number ;
        }
    }
    else{
        cout << "It's computer's turn" << endl ;
    }
    if(player.getId()==0 || player.getId()==1){
        for(int i=7 ; i>=0 ; i--){
            if(tab[i][number-1]==VOID){
                if(player.getId()==0)
                    tab[i][number-1]= CROSS ;
                else
                {
                    tab[i][number-1]= CIRCLE ;
                }
                return ;
            }
            else{
                if(i==0 )//&& tab[i][number-1] != VOID
                {
                    prev_number.push_back(number);
                    cout << "Enter another column :" ;       //colonne a remplir par le joueur
                    cin >> number ;     
                    while(number<1 || number>8 || checkList(prev_number,number) ){
                    cout << "warning!! Enter another column:" ;       //colonne a remplir par le joueur
                    cin >> number ;
                }
                i=7;
                while(tab[i][number-1]!=VOID && i>=0){
                    i--;
                }
                if(player.getId()==0 && i>=0)
                    tab[i][number-1]= CROSS ;
                else if(player.getId()!=0 && i>=0)
                {
                    tab[i][number-1]= CIRCLE ;
                }
                return ;
                }     
            }
        }
    }
    else{
        srand(time(NULL));      //pour utiliser le mode aléatoire
        j = rand()%8;       //la colonne est donné aléatoirement
        for(int i=7 ; i>=0 ; i--){
            if(tab[i][j]==VOID){
                tab[i][j]= CIRCLE ;

                return ;
            }
            else{
                if(i==0 )//&& tab[i][j] != VOID
                {
                    prev_number.push_back(j);
                      
                     j = rand()%8;       
                    while(checkList(prev_number,j) ){
                    
                    j = rand()%8;       
                    }
                    i=7;
                    while(tab[i][j]!=VOID && i>=0){
                        i--;
                    }
                    tab[i][j]= CIRCLE ;
                    return ;
                }
            }
        }
    }
}
int Grid::gameWinnerLine(Player& player){   //méthode pour vérifier si un joueur a placé 4 couleurs successivement à l'horizontale
    for(int i=0 ; i<8 ; i++){
        for(int j=0 ; j<5 ; j++){
            if(tab[i][j]!=VOID)
                if(tab[i][j] == tab[i][j+1] && tab[i][j] == tab[i][j+2] && tab[i][j] == tab[i][j+3]){
                    return 1;
                }
        }
    }
    return 0 ;
}
int Grid::gameWinnerCol(Player& player){    ////méthode pour vérifier si un joueur a placé 4 couleurs successivement à la verticale
    for(int j=0 ; j<5 ; j++){
        for(int i=0 ; i<8 ; i++){
            if (tab[i][j] != VOID)
                if(tab[i][j] == tab[i+1][j] && tab[i][j] == tab[i+2][j] && tab[i][j] == tab[i+3][j])
                    return 1 ;
        }
    }
    return 0 ;
}
int Grid::gameWinnerDiagonalupRight(Player& player){  ////méthode pour vérifier si un joueur a placé 4 couleurs successivement en diagonal vers le haut à droite
    for(int i=3 ; i<8 ; i++){
        for(int j=5 ; j>=0 ; j--){
            if(tab[i][j]!=VOID)
                if(tab[i][j] == tab[i-1][j+1] && tab[i][j] == tab[i-2][j+2] && tab[i][j] == tab[i-3][j+3]){
                    return 1;
                }
        }
    }
    return 0 ;
}
int Grid::gameWinnerDiagonaldownRight(Player& player){      //méthode pour vérifier si un joueur a placé 4 couleurs successivement en diagonal en bas à droite
    for(int i=5 ; i>=0 ; i--){
        for(int j=5 ; j>=0 ; j--){
            if(tab[i][j]!=VOID)
                if(tab[i][j] == tab[i+1][j+1] && tab[i][j] == tab[i+2][j+2] && tab[i][j] == tab[i+3][j+3]){
                    return 1;
                }
        }
    }
    return 0 ;
}
int Grid::gameWinnerDiagonalupLeft(Player& player){         //méthode pour vérifier si un joueur a placé 4 couleurs successivement en haut à gauche
    for(int i=3 ; i<8 ; i++){
        for(int j=3 ; j<8 ; j++){
            if(tab[i][j]!=VOID)
                if(tab[i][j] == tab[i-1][j-1] && tab[i][j] == tab[i-2][j-2] && tab[i][j] == tab[i-3][j-3]){
                    return 1;
                }
        }
    }
    return 0 ;
}
int Grid::gameWinnerDiagonaldownLeft(Player& player){       //méthode pour vérifier si un joueur a placé 4 couleurs successivement en bas à gauche
    for(int i=5 ; i>=0 ; i--){
        for(int j=3 ; j<8 ; j++){
            if(tab[i][j]!=VOID)
                if(tab[i][j] == tab[i+1][j-1] && tab[i][j] == tab[i+2][j-2] && tab[i][j] == tab[i+3][j-3]){
                    return 1;
                }
        }
    }
    return 0 ;
}
int Grid::gameCheck(Player& player){        //méthode pour vérifier si 4 couleurs ont été placées successivement dans n'importe quel cas
    if(gameWinnerLine(player)==1 || gameWinnerCol(player)==1 || gameWinnerDiagonalupRight(player)==1 || gameWinnerDiagonaldownRight(player)==1 || gameWinnerDiagonalupLeft(player)==1  || gameWinnerDiagonaldownLeft(player)==1)
        return 1 ;
    return 0 ;
}
///définition des méthodes de la classe Menu
Menu::Menu(){       //constructeur du menu
    nbOps = 3;
    ops = new (nothrow) string[nbOps];
    if(ops != nullptr){
        ops[0] = " Quit";
        ops[1] = "Play with 2 players";
        ops[2] = "Play with computer";
    }
    else{
        cout << "Can't create menu" << endl;
    }
}
Menu::~Menu(){              //destructeur du menu
    delete[]ops;         ///supprime toutes les allocations dans Menu
}
int Menu::display(){       //pour afficher le menu
    cout << "\nType a number to choose an operation:" << endl;
    for(int i=1; i<nbOps; i++)
        cout << "\t" << i << " : " << ops[i] << endl;
    cout << "\t" << 0 << " : " << ops[0] << endl;
    cout << "\tYour choice please: ";
    cin  >> choice;
    return choice;
}
AIComputer::AIComputer(){       //constructeur vide de la classe computer 
    Player(CIRCLE);
    id = 2 ;
}

bool checkList(vector<int> &tab,int number)
{
    return find(tab.begin(), tab.end(), number ) != tab.end() ;
    
}

int main(){             //fonction principale
    Menu menu;          ///initialisation de toutes les variables
    int choice(0);
    Grid grid;
    Player player(0);    //instance d'un player
    AIComputer computer;  //instance d'un ordinateur pour jouer automatiquement

       choice=menu.display();
       if(choice==1){
            while(grid.gameCheck(player)==0){
                grid.add(player);
                grid.display();
                if(player.getId()==0)
                player.setId(1);
                 else  player.setId(0);
            }
            if(player.getId()==0)
                cout << "Player 2" << " wins" << endl ;
            else if(player.getId()==1)
                cout << "Player 1" << " wins" << endl ;
        }
        else if(choice==2){
             while(grid.gameCheck(player)==0 && grid.gameCheck(computer)==0){
                grid.add(player);
                grid.display();
                grid.add(computer);
                grid.display(); 
            }
            if(grid.gameCheck(player)!=0)
                cout << "Player 1" << " wins" << endl ;
            else if(grid.gameCheck(player)==0)
                cout << "Computer" << " wins" << endl ;
        }
    return 0;
}
// void displayVect(vector<int> &tab)
// {
//     for (int i=0; i< tab.size(); i++)
//     {
//         cout << tab[i] << " " ; 
//     }
// }