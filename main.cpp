#include <iostream>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
// Victor SANTELE 5TT
using namespace std;
// TODO: Modifier fct bataille pour implémenter ordi | bataille faux
string erreur = "";
char bateau(254); // ■
char eau('~');
char plouf(177);
char hit(219);
char plateau[10][10];
char plateauAdverse[10][10];
char plateauOrdi[10][10];
char plateauAdverseOrdi[10][10];

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
        if(bateauTaille + colonne > 10)
        {
            erreur += "Le bateau depasse du plateau | ";
            return true;
        }
        else
        {
            for(int i = colonne; i < colonne+ bateauTaille; i++ )
            {
                cout << "H Colonne: " << i << " Ligne: " << ligne << endl;
                if(tableau[ligne][i] != eau)
                {
                    erreur += "H Il y a deja un bateau !   | ";
                    return true;
                }
            }
        }
    }
    else if( sens == 'v')
    {
        if(bateauTaille + ligne > 10)
        {
            erreur += "Le bateau depasse du plateau | ";
            return true;
        }
        else
        {
            for(int i = ligne; i < ligne+ bateauTaille; i++ )
            {
                cout << "V Ligne: " << i << " Colonne: " << colonne << endl;
                if(tableau[i][colonne] != eau)
                {
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

void placement(char tableau[10][10], char tableauOrdi[10][10], char bateauChar, int bateauTaille[5], string bateauNom[5])
{
    // joueur
    for(int i = 0; i < 5; i++ )
    {

        bool estPlace = false;
        while(!estPlace)
        {
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
            /* col=0;
            lig=i;
            sens='h'; */
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
            }
        }
    }
    // ordi
    for (int i = 0; i < 5; i++)
    {
        bool estPlace = false;
        while (!estPlace)
        {
            int col = rand() % 10;
            int lig = rand() % 10;
            char sens = rand() % 2 == 0 ? 'v' : 'h';
            int taille = bateauTaille[i];
            if(!dejaBateau(tableauOrdi, eau, taille, sens, col, lig))
            {
                for (int j=0; j < taille ; j++)
                {
                    if (sens == 'v')
                    {
                        tableauOrdi[j + lig][col] = bateauChar;
                    }
                    else if (sens == 'h')
                    {
                        tableauOrdi[lig][j + col] = bateauChar;
                    }
                }
                estPlace = true;
            }
        }
    }
    affichage(tableauOrdi, erreur);
}

void bataille (char plateau [10][10], char plateauAdverse[10][10], char plateauOrdi[10][10], char plateauAdverseOrdi[10][10], char eau, char bateau, char hit, char plouf, bool estOrdi)
{
    int col, lig;
    int nbHit(0), nbPlouf(0), nbHitOrdi(0), nbPloufOrdi(0);
    while( (nbHit < 17 && nbPlouf < 73) || (nbHitOrdi < 17 && nbPloufOrdi <73))
    {
        bool ok = true;
        if(estOrdi)
        {
            col = rand() % 10;
            lig = rand() % 10;
            plateauAdverseOrdi[lig][col] == eau? plateau[lig][col] == bateau ? (plateauAdverseOrdi[lig][col] = hit, nbHitOrdi++) : (plateauAdverseOrdi[lig][col] = plouf, nbPloufOrdi++) : ok = false;
        }
        else
        {
            cout << "Cible?" << endl;
            cout << "Colonne (1-10) : ";
            cin >> col;
            col--;
            cout << "Ligne (1-10) : ";
            cin >> lig;
            lig--;
            plateauAdverse[lig][col] == eau? plateauOrdi[lig][col] == bateau ? (plateauAdverse[lig][col] = hit, nbHit++) : (plateauAdverse[lig][col] = plouf, nbPlouf++) : ok = false;
            affichage(plateauAdverse, erreur);
            cout << nbHit << " | " << nbPlouf << endl;

        }
        estOrdi = ok? !estOrdi : estOrdi;

    }
}

int main()
{
    srand(time(NULL));
    system("color F0");
    string bateauNom[5] = {"Porte-avions", "Croiseur", "Contre-torpilleur", "Sous-marin","Torpilleur"};
    int bateauTaille[5] = {5,4,3,3,2};
    bool estOrdi = false;
    initialisation(plateau, eau);
    initialisation(plateauAdverse, eau);
    initialisation(plateauOrdi, eau);
    initialisation(plateauAdverseOrdi, eau);
    cout << "Liste Bateaux disponibles:" << endl;
    for(int i = 0; i<5; i++)
    {
        cout << i << ": " << bateauNom[i] << " de taille " << bateauTaille[i] << endl;
    }
    placement(plateau, plateauOrdi, bateau, bateauTaille, bateauNom);
    affichage(plateau, erreur);
    bataille(plateau, plateauAdverse, plateauAdverse, plateauAdverseOrdi, eau, bateau, hit, plouf, estOrdi);
    affichage(plateauAdverse, erreur);
    return 0;
}

