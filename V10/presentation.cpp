#include "presentation.h"
#include "chifoumi.h"
#include "dialogparametre.h"
#include "dialogconnexion.h"
#include "dialogresultat.h"
#include <QMessageBox>

presentation::presentation(modele* m,QObject *parent) : QObject{parent}, _leModele(m)
{


    //ctor
    // partie mod�le
    tmps = 30;

    // Initilialisation de la vue
    _leModele->setDark(false);
    _leModele->setTpsMax(30);
    _leModele->setNbPtsMax(5);
    _leModele->initScores();
    _leModele->initCoups();

    // Lancement du timer
    _time = new QTimer(this);
    QObject::connect(_time, SIGNAL(timeout()), this, SLOT(updateTimer()));

    // Lancement de la dialog de connexion
    DialogConnexion* maDLG = new DialogConnexion;
    maDLG->exec();

    // Récupération du login
    if(!maDLG->getEstConnecter()) _laVue->close();
    _leModele->setId(maDLG->getId());
    _leModele->setNom(maDLG->getLog());
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
    // Reinitialisation de la partie
    _time->start(1000);
    _leModele->initCoups();
    _leModele->initScores();
    _leModele->setEtat(modele::Etat::enCours);
    // Actualisation de la vue
    demandeActualisation();
    tmps = _leModele->getTpsMax();
    _laVue->majTimer(tmps);
}

void presentation::demandePause(){
    // Demande de reprise
    if(_leModele->getEtat()==modele::Etat::enPause){
        _time->start();
        _leModele->setEtat(modele::Etat::enCours);
        demandeActualisation();
    } // Delande de pause
    else{
        _time->stop();
        _leModele->setEtat(modele::Etat::enPause);
        demandeActualisation();
    }

}

#include <QDebug>

void presentation::coupJoueurJoue(){
    // Generation du coup de l'ordinateur
    _leModele->setCoupMachine(_leModele->genererUnCoup());
    // Actualisation de la vue
    _leModele->majScores(_leModele->determinerGagnant());
    // Si l'un gagne
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
    // Affichage de la boite de dialogue
    QMessageBox *msgbox = new QMessageBox;
    msgbox->setWindowTitle("A propos de cette application.");
    msgbox->setText(" - La version de l’application : V9\n- la date de création 24/05/2022\n - Les auteursProgramme développé par :\nArthur Le Menn\nColas Naudi\nMathis Heriveau");
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
        // Actualisation de la vue
        demandeActualisation();

    }
}

void presentation::parametre(){
    // Affichage de la boite de dialogue de parametrage si le jeu est arrté
    if(_leModele->getEtat()!=modele::Etat::initialiser && _leModele->getEtat()!=modele::Etat::fin){
        // Si le jeu est en cours, on affiche un message d'erreur
        QMessageBox msgBox;
        msgBox.setText("L’utilisateur peut modifier différents paramètres que avant de commencer une partie.");
        msgBox.setInformativeText("Veillez attendre la fin de la partie avant d'accéder aux parametres");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else{
        // Si le jeu est arrté, on affiche la boite de dialogue
        // Affichage de la boite de dialogue de parametrage
        DialogParametre* madlg = new DialogParametre(_laVue,_leModele->getNom(),_leModele->getNbPtsMax(),_leModele->getTpsMax(),_leModele->getDark());
        madlg->exec();
        // Si l'utilisateur a cliqué sur enregistré
        if(madlg->getEnregistrer()){
            _leModele->setNom(madlg->getNom());
            _leModele->setNbPtsMax(madlg->getNbPtsMax());
            _leModele->setTpsMax(madlg->getTpsMax());
            _laVue->majParametre(_leModele->getNom(),_leModele->getNbPtsMax(),_leModele->getTpsMax());
            if(madlg->getDark()) _leModele->setDark(true);
            else _leModele->setDark(false);
            _laVue->modeDark(_leModele->getDark());
        }
    }
}


void presentation::demandeActualisation(){
    // Actualisation de la vue
     _laVue->actualisation(_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(),_leModele->getScoreMachine(), _leModele->getEtat(), tmps,  _leModele->getTpsMax(), _leModele->getNom());
     if(_leModele->getEtat() == modele::Etat::fin) {
         // Si la partie est terminée, on inserte le score dans la base de données
         _leModele->db->insertScore(_leModele->getId(),_leModele->getNom(),_leModele->getScoreJoueur(),_leModele->getScoreMachine());
     }

}


void presentation::resultat(){
    // Affichage de la boite de dialogue de resultat
    if(!(_leModele->getEtat()!=modele::Etat::initialiser && _leModele->getEtat()!=modele::Etat::fin)){
        DialogResultat* madlg = new DialogResultat();
        madlg->exec();
    }
}
