#include "chifoumi.h"
#include "ui_chifoumi.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    srand(time(NULL));
    ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/rien.gif"));
    ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/rien.gif"));
    ui->iconFeuille->setEnabled(false);
    ui->iconCiseau->setEnabled(false);
    ui->iconPierre->setEnabled(false);
    ui->NvllPartie->setFocus();
    ui->NvllPartie->setDefault(true);
    ui->Pause->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nvlleConnexion(QObject *c)
{
    //pour se connecter avec la presentation
    connect(ui->iconFeuille, SIGNAL(clicked()), c, SLOT(boutonFeuille()));
    connect(ui->iconCiseau, SIGNAL(clicked()), c, SLOT(boutonCiseau()));
    connect(ui->iconPierre, SIGNAL(clicked()), c, SLOT(boutonPierre()));
    connect(ui->NvllPartie, SIGNAL(clicked()), c, SLOT(nvllePartieDemandee()));
    connect(ui->actionA_propos_de, SIGNAL(triggered()), c, SLOT(aProposDe()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->Pause,SIGNAL(clicked()),c,SLOT(demandePause()));
}

void MainWindow::supprConnexion(QObject *c)
{
    //pour se déconnecter de c
    disconnect(ui->iconFeuille, SIGNAL(clicked()), c, SLOT(boutonFeuille()));
    disconnect(ui->iconCiseau, SIGNAL(clicked()), c, SLOT(boutonCiseau()));
    disconnect(ui->iconPierre, SIGNAL(clicked()), c, SLOT(boutonPierre()));
    disconnect(ui->NvllPartie, SIGNAL(clicked()), c, SLOT(nvllePartieDemandee()));
    disconnect(ui->actionA_propos_de, SIGNAL(triggered()), c, SLOT(aProposDe()));
    disconnect(ui->actionQuitter, SIGNAL(triggered()), c, SLOT(close()));
    disconnect(ui->Pause,SIGNAL(clicked()),c,SLOT(demandePause()));
}


void MainWindow::actualisation(modele::UnCoup coupJ, modele::UnCoup coupM, int scoreJ,int scoreM, modele::Etat e){

    switch (e) {
        case modele::initialiser:
            ui->iconFeuille->setEnabled(true);
            ui->iconCiseau->setEnabled(true);
            ui->iconPierre->setEnabled(true);
            ui->Pause->setEnabled(true);
            ui->Pause->setText("Pause");
            ui->NvllPartie->setEnabled(true);

            ui->labelVous->setStyleSheet("color: blue;");
            ui->labelScoreVous->setStyleSheet("color: blue;");
            break;
        case modele::enPause:
            ui->iconFeuille->setEnabled(false);
            ui->iconCiseau->setEnabled(false);
            ui->iconPierre->setEnabled(false);
            ui->Pause->setText("Reprise jeu");
            ui->Pause->setDefault(true);
            ui->Pause->setEnabled(true);
            ui->NvllPartie->setEnabled(false);
        break;
        case modele::enCours:
            QString txt;

            ui->Pause->setText("Pause");
            ui->Pause->setEnabled(true);
            ui->NvllPartie->setEnabled(true);
            ui->Pause->setDefault(false);
            ui->iconFeuille->setEnabled(true);
            ui->iconCiseau->setEnabled(true);
            ui->iconPierre->setEnabled(true);

            ui->labelScoreMachine->setText(txt.QString::setNum(scoreM));
            ui->labelScoreVous->setText(txt.QString::setNum(scoreJ));

            switch (coupJ) {
                case modele::UnCoup::pierre: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/pierre.gif"));  break;
                case modele::UnCoup::ciseau: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/ciseau.gif")); break;
                case modele::UnCoup:: papier: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/papier.gif"));break;
                case modele::UnCoup::rien: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/rien.gif")); break;
            }

            switch (coupM) {
                case modele::UnCoup::pierre: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/pierre.gif")); break;
                case modele::UnCoup::ciseau: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/ciseau.gif")); break;
                case modele::UnCoup::papier: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/papier.gif")); break;
                case modele::UnCoup::rien: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/rien.gif")); break;
            }
            break;

    }

}


void MainWindow::majTimer(int temps){
    ui->timer->setText(QString::number(temps));
}
