/***************************************************************
 * Name:      main.cpp
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : Programme TEST de la classe m�tier Chifoumi-v1
 **************************************************************/

// cd "/Users/colasnaudi/Desktop/GitHub/BUT-INFO/S2/S2.01-Développement-d-une-application/CHIFOUMI/" && g++ main.cpp chifoumi.cpp -o main && "/Users/colasnaudi/Desktop/GitHub/BUT-INFO/S2/S2.01-Développement-d-une-application/CHIFOUMI/"main


#include <iostream>

using namespace std;
#include "chifoumi.h"
#include <cstdlib>
#include <ctime>

///* ------  Sp�cifications des Sous-pogrammes utilitaires ------------

Chifoumi::UnCoup genererCoup();
/* duplique la m�thode priv�e de la classe Chifoumi,
    pour ne pas modifier le code de la classe en la rendant publique
*/

void afficherScores(Chifoumi& p_jeu);
// affiche les scores actuels des joueurs

void afficherCoups(Chifoumi& p_jeu);
// affiche les valeurs actuellement stock�es dans les attributs coupJoeur et coupMachine

string coup2String(Chifoumi::UnCoup p_coup);
/* retourne une chaine correspondant � la valeur de p_coup, cad :
    retourne "rien" si p_coup = Chifoumi::rien,
    retourne "pierre" si p_coup = Chifoumi::pierre,
    etc...
*/

///* ------  MAIN  ------------
int main()
{
    ///teste constructeur
    Chifoumi monJeu; // un jeu de chifoumi
    char rep ;      // r�ponse � demande de Quitter
    cout << "appel du constructeur : construction d'un chifoumi : scores a 0, et coupsJoueurs a RIEN' " << endl;
    cout << endl;

    ///teste getScore()
    cout << "teste les methodes get() associees aux attributs 'score' " << endl;
    afficherScores(monJeu);
    cout << endl;

    ///teste getCoup()
    cout << "teste les methodes get() associees aux attributs 'coup' " << endl;
    afficherCoups(monJeu);
    cout << endl;

    /// teste setScore();
    cout << "teste les methodes set() associees aux attributs 'score' " << endl;
    monJeu.setScoreJoueur(1);
    monJeu.setScoreMachine(2);
    afficherScores(monJeu);
    cout << endl;

    /// teste initScore()
    cout << "teste initScores() "<< endl;
    monJeu.initScores();
    afficherScores(monJeu);
    cout << endl;

     /// teste setCoupJoueur et setCoupMachine()
    cout << "teste les m�thodes set() et get() associees aux attributs 'coup'/'choix' " << endl;
    monJeu.setCoupJoueur(Chifoumi::pierre);
    monJeu.setCoupMachine(Chifoumi::ciseau);
    afficherCoups(monJeu);
    cout << endl;

    cout << "quelques tours de jeu pour tester l'identification du gagnant et la maj des scores" << endl;
    // le testeur peut it�rer auatnt de fois qu'il/elle veut
    while (true)
    {
        monJeu.setCoupJoueur(genererCoup());
        monJeu.setCoupMachine(genererCoup());
        monJeu.majScores(monJeu.determinerGagnant());
        afficherCoups(monJeu);
        afficherScores(monJeu);
        cout << endl << endl;

        // -- >> ARRETER >> rep
        cout << "Quitter ? (o/n) " ;
        rep= getchar();
        if ((rep == 'o') | (rep == 'O'))
        {
            break;
        }
        cout << endl;
    }

    return 0;
}

///* ------  D�finitions des sous-pogrammes utilitaires ------------

Chifoumi::UnCoup genererCoup()
{
    Chifoumi::UnCoup valeurGeneree;   // valeur � retourner
    unsigned int nbAleatoire;
    nbAleatoire = rand()%(4-1) + 1;
    switch (nbAleatoire)
    {
    case 1 :
        valeurGeneree = Chifoumi::pierre;
        break;
    case 2 :
        valeurGeneree = Chifoumi::papier;
        break;
    case 3 :
        valeurGeneree = Chifoumi::ciseau;
        break;
    default:
        break;
    }
    return valeurGeneree;
}

void afficherScores(Chifoumi& p_jeu)
{
    cout << "score Joueur : " << p_jeu.getScoreJoueur() <<  "       ";
    cout << "score Machine : " << p_jeu.getScoreMachine() << endl;
}

void afficherCoups(Chifoumi& p_jeu)
{
    cout << "coup Joueur : " << coup2String(p_jeu.getCoupJoueur()) <<  "   ";
    cout << "coup Machine : " << coup2String(p_jeu.getCoupMachine()) << endl;
}

string coup2String(Chifoumi::UnCoup p_coup)
{
    string chaineCoup;
    chaineCoup = "";
    switch (p_coup)
    {
    case Chifoumi::rien :
        chaineCoup = "rien" ;
        break;
    case Chifoumi::papier :
        chaineCoup = "papier" ;
        break;
    case Chifoumi::ciseau :
        chaineCoup = "ciseau" ;
        break;
    case Chifoumi::pierre :
        chaineCoup = "pierre" ;
        break;
    default :
        break;
    }
    return chaineCoup;
}
