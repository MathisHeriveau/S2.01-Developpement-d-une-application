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
    _leModele->initCoups();
    _leModele->initScores();
    _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat(), _leModele->getNbPointsRequis());
    _leModele->setEtat(modele::Etat::enCours);
}


void presentation::coupJoueurJoue(){
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    _leModele->majScores(_leModele->determinerGagnant());
    if(_leModele->getNbPointsRequis()<= _leModele->getScoreJoueur() || _leModele->getNbPointsRequis()<= _leModele->getScoreMachine()){
        //Le score requis est atteint
        _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat(), _leModele->getNbPointsRequis());
        _leModele->setEtat(modele::Etat::fin);
        _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat(), _leModele->getNbPointsRequis());
        _leModele->setEtat(modele::Etat::enCours);
        nvllePartieDemandee();
    }
    else{
        _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat(), _leModele->getNbPointsRequis());
    }


}

void presentation::aProposDe()
{
    QMessageBox *msgbox = new QMessageBox;
    msgbox->setWindowTitle("A propos de cette application.");
    msgbox->setText(" - La version de l’application : V4\n- la date de création 24/05/2022\n - Les auteursProgramme développé par :\nArthur Le Menn\nColas Naudi\nMathis Heriveau");
    msgbox->setStandardButtons(QMessageBox::Ok);
    msgbox->exec();
}
