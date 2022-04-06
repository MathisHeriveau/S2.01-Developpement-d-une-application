#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ctor
    // partie mod�le
    initScores();
    initCoups();
    srand(time(NULL));

    ui->setupUi(this);
    connect(ui->iconFeuille, SIGNAL(clicked()), this, SLOT(boutonFeuille()));
    connect(ui->iconCiseau, SIGNAL(clicked()), this, SLOT(boutonCiseau()));
    connect(ui->iconPierre, SIGNAL(clicked()), this, SLOT(boutonPierre()));
    connect(ui->NvllPartie, SIGNAL(clicked()), this, SLOT(boutonNvllPartie()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



/// Getters

MainWindow::UnCoup MainWindow::getCoupJoueur() {
    return coupJoueur;
}

MainWindow::UnCoup MainWindow::getCoupMachine() {
    return coupMachine;
}

unsigned int MainWindow::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int MainWindow::getScoreMachine() {
    return scoreMachine;
}

char MainWindow::determinerGagnant(){
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

MainWindow::UnCoup MainWindow::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    unsigned int nbAleatoire;
    nbAleatoire = randMinMax(1, 4);
    switch (nbAleatoire) {
        case 1 : valeurGeneree = MainWindow::pierre;break;
        case 2 : valeurGeneree = MainWindow::papier;break;
        case 3 : valeurGeneree = MainWindow::ciseau;break;
        default: break;
    }
    return valeurGeneree;
}

/// Setters

void MainWindow::setCoupJoueur(UnCoup p_coup){
    coupJoueur = p_coup;
}

void MainWindow::setCoupMachine(UnCoup p_coup) {
    coupMachine = p_coup;
}

void MainWindow::setScoreJoueur(unsigned int p_score) {
    scoreJoueur = p_score;
}

void MainWindow::setScoreMachine(unsigned int p_score) {
    scoreMachine = p_score;
}

void MainWindow::majScores(char p_gagnant) {
    switch(p_gagnant)
    {
        case 'M' : scoreMachine++; break;
        case 'J' : scoreJoueur++; break;
        case 'N' :
        default : break;
    }
}

void MainWindow::initScores() {
    setScoreMachine(0);
    setScoreJoueur(0);
}

void MainWindow::initCoups() {
    setCoupJoueur(rien);
    setCoupMachine(rien);
}



void MainWindow::boutonFeuille(){
    this->setCoupJoueur(MainWindow::papier);
    this->setCoupMachine(this->genererUnCoup());
    this->majScores(determinerGagnant());
    this->actualisation();
}
void MainWindow::boutonCiseau(){
    this->setCoupJoueur(MainWindow::ciseau);
    this->setCoupMachine(this->genererUnCoup());
    this->majScores(determinerGagnant());
    this->actualisation();
}
void MainWindow::boutonPierre(){
    this->setCoupJoueur(MainWindow::pierre);
    this->setCoupMachine(this->genererUnCoup());
    this->majScores(determinerGagnant());
    this->actualisation();

}
void MainWindow::boutonNvllPartie(){
    this->initCoups();
    this->initScores();
    this->actualisation();

}



void MainWindow::actualisation(){

    QString txt;

    ui->labelScoreMachine->setText(txt.QString::setNum(getScoreMachine()));
    ui->labelScoreVous->setText(txt.QString::setNum(getScoreJoueur()));

    switch (getCoupJoueur()) {
        case pierre: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/pierre.gif"));  break;
        case ciseau: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/ciseau.gif")); break;
        case papier: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/papier.gif"));break;
        case rien: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/rien.gif")); break;
    }

    switch (getCoupMachine()) {
        case pierre: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/pierre.gif")); break;
        case ciseau: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/ciseau.gif")); break;
        case papier: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/papier.gif")); break;
        case rien: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/rien.gif")); break;
    }
}
