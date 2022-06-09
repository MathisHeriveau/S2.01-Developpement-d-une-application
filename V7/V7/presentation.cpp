#include "presentation.h"
#include "chifoumi.h"
#include "dialogparametre.h"
#include "dialogconnexion.h"
#include <QMessageBox>

presentation::presentation(modele* m,QObject *parent) : QObject{parent}, _leModele(m)
{


    //ctor
    // partie mod�le
    tmps = 30;
    _leModele->setNom("Vous");
    _leModele->setTpsMax(30);
    _leModele->setNbPtsMax(5);
    _leModele->initScores();
    _leModele->initCoups();
    _leModele->setEtat(modele::Etat::initialiser);
    _time = new QTimer(this);
    QObject::connect(_time, SIGNAL(timeout()), this, SLOT(updateTimer()));

    DialogConnexion* maDLG = new DialogConnexion;
    maDLG->exec();
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
    _leModele->setEtat(modele::Etat::enCours);
    demandeActualisation();
    tmps = _leModele->getTpsMax();
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

#include <QDebug>

void presentation::coupJoueurJoue(){
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    _leModele->majScores(_leModele->determinerGagnant());
    if(_leModele->getNbPtsMax()<= _leModele->getScoreJoueur() || _leModele->getNbPtsMax() <= _leModele->getScoreMachine()){
        _time->stop();

        demandeActualisation();
        _leModele->setEtat(modele::Etat::fin);
        demandeActualisation();
    }
    else{
       demandeActualisation();
    }

}



void presentation::aProposDe()
{
    QMessageBox *msgbox = new QMessageBox;
    msgbox->setWindowTitle("A propos de cette application.");
    msgbox->setText(" - La version de l’application : V6\n- la date de création 24/05/2022\n - Les auteursProgramme développé par :\nArthur Le Menn\nColas Naudi\nMathis Heriveau");
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
        _leModele->setEtat(modele::Etat::fin);
        demandeActualisation();

    }
}


void presentation::demandeActualisation(){
     _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat(), tmps,  _leModele->getTpsMax());
}

void presentation::parametre(){
    if(_leModele->getEtat()!=modele::Etat::initialiser && _leModele->getEtat()!=modele::Etat::fin){
        QMessageBox msgBox;
        msgBox.setText("L’utilisateur peut modifier différents paramètres que avant de commencer une partie.");
        msgBox.setInformativeText("Veillez attendre la fin de la partie avant d'accéder aux parametres");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else{
        DialogParametre* madlg = new DialogParametre(_laVue,_leModele->getNom(),_leModele->getNbPtsMax(),_leModele->getTpsMax());
        madlg->exec();
        if(madlg->getEnregistrer()){
            _leModele->setNom(madlg->getNom());
            _leModele->setNbPtsMax(madlg->getNbPtsMax());
            _leModele->setTpsMax(madlg->getTpsMax());
            qDebug() << _leModele->getNbPtsMax();
            _laVue->majParametre(_leModele->getNom(),_leModele->getNbPtsMax(),_leModele->getTpsMax());
        }
    }
}
