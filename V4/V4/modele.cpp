#include "modele.h"

modele::modele(QObject *parent) : QObject(parent)
{

}

/// Getters

modele::UnCoup modele::getCoupJoueur() {
    return coupJoueur;
}

modele::UnCoup modele::getCoupMachine() {
    return coupMachine;
}

unsigned int modele::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int modele::getScoreMachine() {
    return scoreMachine;
}

modele::Etat modele::getEtat(){
    return etatJeu;
}

unsigned int modele::getNbPointsRequis(){
    return nbPointsRequis;
}

char modele::determinerGagnant(){
    char gagnantARetourner;
    // avant de commencer : match nul
    gagnantARetourner = 'N';

    // il sera modifi� dans l'un des cas suivants

    // si le joueur a choisi pierre
    if (getCoupJoueur() == pierre) {
        // si la machine a choisi pierre
        if (getCoupMachine() == pierre) {
            // match nul
            gagnantARetourner = 'N';
        }
        // si la machine a choisi papier
        else if (getCoupMachine() == papier) {
            // le joueur gagne
            gagnantARetourner = 'M';
        }
        // si la machine a choisi ciseau
        else if (getCoupMachine() == ciseau) {
            // la machine gagne
            gagnantARetourner = 'J';
        }
    }
    // si le joueur a choisi papier
    else if (getCoupJoueur() == papier) {
        // si la machine a choisi pierre
        if (getCoupMachine() == pierre) {
            // la machine gagne
            gagnantARetourner = 'J';
        }
        // si la machine a choisi papier
        else if (getCoupMachine() == papier) {
            // match nul
            gagnantARetourner = 'N';
        }
        // si la machine a choisi ciseau
        else if (getCoupMachine() == ciseau) {
            // le joueur gagne
            gagnantARetourner = 'M';
        }
    }
    // si le joueur a choisi ciseau
    else if (getCoupJoueur() == ciseau) {
        // si la machine a choisi pierre
        if (getCoupMachine() == pierre) {
            // le joueur gagne
            gagnantARetourner = 'M';
        }
        // si la machine a choisi papier
        else if (getCoupMachine() == papier) {
            // la machine gagne
            gagnantARetourner = 'J';
        }
        // si la machine a choisi ciseau
        else if (getCoupMachine() == ciseau) {
            // match nul
            gagnantARetourner = 'N';
        }
    }

    return gagnantARetourner;
}

///* M�thodes utilitaires du Mod�le

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
    return rand()%(max-min) + min;
}

modele::UnCoup modele::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    unsigned int nbAleatoire;
    nbAleatoire = randMinMax(1, 4);
    switch (nbAleatoire) {
        case 1 : valeurGeneree = modele::pierre;break;
        case 2 : valeurGeneree = modele::papier;break;
        case 3 : valeurGeneree = modele::ciseau;break;
    }
    return valeurGeneree;
}

/// Setters

void modele::setCoupJoueur(UnCoup p_coup){
    coupJoueur = p_coup;
}

void modele::setCoupMachine(UnCoup p_coup) {
    coupMachine = p_coup;
}

void modele::setScoreJoueur(unsigned int p_score) {
    scoreJoueur = p_score;
}

void modele::setScoreMachine(unsigned int p_score) {
    scoreMachine = p_score;
}

void modele::setEtat(Etat e){
    etatJeu = e;
}

void modele::setNbPointsRequis(unsigned int nbPoints){
    nbPointsRequis = nbPoints;
}

void modele::majScores(char p_gagnant) {
    switch(p_gagnant)
    {
        case 'M' : scoreMachine++; break;
        case 'J' : scoreJoueur++; break;
        case 'N' :
        default : break;
    }
}

void modele::initScores() {
    setNbPointsRequis(5);
    setScoreMachine(0);
    setScoreJoueur(0);
}

void modele::initCoups() {
    setCoupJoueur(rien);
    setCoupMachine(rien);
}




