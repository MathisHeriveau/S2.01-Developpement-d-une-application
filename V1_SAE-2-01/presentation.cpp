#include "presentation.h"
#include "chifoumi.h"
#include <QMessageBox>

presentation::presentation(modele* m,QObject *parent) : QObject{parent}, _leModele(m)
{
    //ctor
    // partie mod�le
    tmps = 30;
    _leModele->initScores();
    _leModele->initCoups();
    _leModele->setEtat(modele::Etat::initialiser);
    _time = new QTimer(this);
    QObject::connect(_time, SIGNAL(timeout()), this, SLOT(updateTimer()));
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
    _time->start(1000);
    _leModele->initCoups();
    _leModele->initScores();
    demandeActualisation();
    _leModele->setEtat(modele::Etat::enCours);
    tmps = 30;
    _laVue->majTimer(tmps);
}

void presentation::demandePause(){
    if(_leModele->getEtat()==modele::Etat::enPause){
        _time->start();
        _leModele->setEtat(modele::Etat::enCours);
        demandeActualisation();
    }
    else{
        _time->stop();
        _leModele->setEtat(modele::Etat::enPause);
        demandeActualisation();
    }

}



void presentation::coupJoueurJoue(){
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    _leModele->majScores(_leModele->determinerGagnant());
    if(_leModele->getNbPointsRequis()<= _leModele->getScoreJoueur() || _leModele->getNbPointsRequis()<= _leModele->getScoreMachine()){
        _time->stop();
        //Le score requis est atteint
        demandeActualisation();
        _leModele->setEtat(modele::Etat::fin);
        demandeActualisation();
        _leModele->setEtat(modele::Etat::enCours);
        nvllePartieDemandee();
    }
    else{
       demandeActualisation();
    }


}



void presentation::aProposDe()
{
    QMessageBox *msgbox = new QMessageBox;
    msgbox->setWindowTitle("A propos de cette application.");
    msgbox->setText(" - La version de l’application : V5\n- la date de création 24/05/2022\n - Les auteursProgramme développé par :\nArthur Le Menn\nColas Naudi\nMathis Heriveau");
    msgbox->setStandardButtons(QMessageBox::Ok);
    msgbox->exec();
}
void presentation::updateTimer(){
    if(tmps > 0){
        tmps--;
        _time->start(1000);
        _laVue->majTimer(tmps);
        //Afficher le timer
    }
    else{
        _time->stop();
        //Le score requis est atteint
        demandeActualisation();
        _leModele->setEtat(modele::Etat::fin);
        demandeActualisation();
        _leModele->setEtat(modele::Etat::enCours);
        nvllePartieDemandee();

    }
}


void presentation::demandeActualisation(){
     _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat(), _leModele->getNbPointsRequis(), tmps );
}
