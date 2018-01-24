#include <iostream>
#include <iomanip>
#include <windows.h>
// Victor SANTELE 5TT
using namespace std;
// Verification prblème colone 1
string erreur = "";
char bateau(254); // ■
char eau('~');
char plateau[10][10];

void initialisation(char tableau[10][10], char eau)
{
    for(int i = 0; i<10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            tableau[i][j] = eau;
        }
    }
    // return tableau[10][10];
}

bool dejaBateau(char tableau[10][10], char eau, char bateauTaille, char sens, int colonne, int ligne)
{
    char test(254);
    if(sens == 'h')
    {
        if(bateauTaille + colonne > 10){
            erreur += "Le bateau depasse du plateau | ";
            return true;
        } else {
            for(int i = colonne; i < colonne+ bateauTaille; i++ ) {
                cout << "H Colonne: " << i << " Ligne: " << ligne << endl;
                if(tableau[ligne][i] != eau) {
                    erreur += "H Il y a deja un bateau !   | ";
                    return true;
                }
            }
        }
    }
    else if( sens == 'v')
    {
        if(bateauTaille + ligne > 10){
            erreur += "Le bateau depasse du plateau | ";
            return true;
        } else {
            for(int i = ligne; i < ligne+ bateauTaille; i++ ) {
                cout << "V Ligne: " << i << " Colonne: " << colonne << endl;
                if(tableau[i][colonne] != eau) {
                    cout << "bateau ligne: " << i << " colonne: " << i << endl;
                    erreur += "V Il y a deja un bateau!   | ";
                    return true;
                }
            }
        }
    }
}

void affichage(char tableau[10][10], string erreur)
{
    cout << "    ";
    for (int i = 0; i <10; i++)
    {
        cout << setw(4)<< i + 1;
    }
    cout << endl;
    for(int i = 0; i<10; i++)
    {
        cout << setw(4)<< i + 1;
        for(int j = 0; j < 10; j++)
        {
            cout << setw(4) << tableau[i][j];
        }
        cout << endl;
    }
    cout << "Erreur : " << erreur << endl;
}

void placement(char tableau[10][10], char bateauChar, int bateau, int bateauTaille[5], string bateauNom[5])
{
    for(int i = 0; i < 5; i++ )
    {
        bool estPlace = false;
        while(!estPlace) {
            affichage(tableau, erreur);
            int col;
            int lig;
            char sens;
            cout << "Placement du bateau : " << bateauNom[i] << " (" << bateauTaille[i] << ") " << endl;
            cout << "Colonne (1-10) : ";
            cin >> col;
            col--;
            cout << "Ligne (1-10) : ";
            cin >> lig;
            lig--;
            cout << "Sens (h/v) : ";
            cin >> sens;
            int taille = bateauTaille[i];
            if(!dejaBateau(tableau, eau, taille, sens, col, lig))
            {
                for (int j=0; j < taille ; j++)
                {
                    if (sens == 'v')
                    {
                        tableau[j + lig][col] = bateauChar;
                    }
                    else if (sens == 'h')
                    {
                        tableau[lig][j + col] = bateauChar;
                    }
                }
                estPlace = true;
            } else
            {
                cout << "Pas rentrer dans ecriture" << endl;
            }
        }
    }
}
int main()
{
    system("color F0");
    string bateauNom[5] = {"Porte-avions", "Croiseur", "Contre-torpilleur", "Sous-marin","Torpilleur"};
    int bateauTaille[5] = {5,4,3,3,2};
    initialisation(plateau, eau);
    cout << "Liste Bateaux disponibles:" << endl;
    for(int i = 0; i<5; i++)
    {
        cout << i << ": " << bateauNom[i] << " de taille " << bateauTaille[i] << endl;
    }
    placement(plateau, bateau, 0, bateauTaille, bateauNom);
    affichage(plateau, erreur);
    return 0;
}

