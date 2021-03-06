#include "presentation.h"
#include "chifoumi.h"

presentation::presentation(modele* m,QObject *parent) : QObject{parent}, _leModele(m)
{
    //ctor
    // partie mod�le
    _leModele->initScores();
    _leModele->initCoups();
    _leModele->setEtat(modele::Etat::initialiser);
}


modele *presentation::getModele()
{
    return _leModele;
}

MainWindow *presentation::getVue()
{
    return _laVue;
}

void presentation::setModele(modele *m)
{
    _leModele = m;
}

void presentation::setVue(MainWindow *v)
{
    _laVue = v;
}


void presentation::boutonFeuille(){
    _leModele->setCoupJoueur(_leModele->UnCoup::papier);
    coupJoueurJoue();
}
void presentation::boutonCiseau(){
    _leModele->setCoupJoueur(_leModele->UnCoup::ciseau);
    coupJoueurJoue();
}
void presentation::boutonPierre(){
    _leModele->setCoupJoueur(_leModele->UnCoup::pierre);
    coupJoueurJoue();

}
void presentation::nvllePartieDemandee(){
    //Reinitialisation des scores et des coups
    _leModele->initCoups();
    _leModele->initScores();
    // Actualisation de la vue
    _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat());
    _leModele->setEtat(modele::Etat::enCours);
}


void presentation::coupJoueurJoue(){
    // Génération du coup machine
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    // Calcul du score
    _leModele->majScores(_leModele->determinerGagnant());
    // Actualisation de la vue
    _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat());
}
