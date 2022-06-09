#include "presentation.h"
#include "chifoumi.h"
#include <QMessageBox>

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
    // Réinitialisation des scores et des coups
    _leModele->initCoups();
    _leModele->initScores();
    // Actualisation de la vue
    _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat());
    _leModele->setEtat(modele::Etat::enCours);
}


void presentation::coupJoueurJoue(){
    // Génération du coup machine
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    // Actualisation des score sur la vue
    _leModele->majScores(_leModele->determinerGagnant());
    // Actualisation de la vue
    _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat());
}

void presentation::aProposDe()
{   
    // Création de la message box qui affiche le message d'a propos
    QMessageBox *msgbox = new QMessageBox;
    msgbox->setWindowTitle("A propos de cette application.");
    msgbox->setText(" - La version de l’application : V3\n- la date de création 09/06/2022\n - Programme développé par :\nArthur Le Menn\nColas Naudi\nMathis Heriveau");
    msgbox->setStandardButtons(QMessageBox::Ok);
    msgbox->exec();
}
