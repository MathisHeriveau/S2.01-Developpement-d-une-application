#include "chifoumi.h"
#include "ui_chifoumi.h"
#include <QMessageBox>

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
}


void MainWindow::actualisation(modele::UnCoup coupJ, modele::UnCoup coupM, int scoreJ,int scoreM, modele::Etat e, unsigned int nbPointsRequis){
    QString txt;
    switch (e) {
        case modele::initialiser:
            ui->iconFeuille->setEnabled(true);
            ui->iconCiseau->setEnabled(true);
            ui->iconPierre->setEnabled(true);

            ui->labelMachine->setStyleSheet("color: blue;");
            ui->labelVous->setStyleSheet("color: blue;");
            ui->labelScoreMachine->setStyleSheet("color: blue;");
            ui->labelScoreVous->setStyleSheet("color: blue;");

            break;
        case modele::fin:
            if(scoreJ > scoreM){
                QMessageBox::information(this, "Fin de la partie gagnant", "Bravo vous gagné la partie avec " + txt.QString::setNum(scoreJ) + " points");
            }
            else{
                QMessageBox::information(this, "Fin de la partie perdant", "Dommage vous avez perdu la partie avec " + txt.QString::setNum(scoreJ) + " points");
            }



        case modele::enCours:


            ui->labelScoreMachine->setText(txt.QString::setNum(scoreM));
            ui->labelScoreVous->setText(txt.QString::setNum(scoreJ));
            ui->labelNbPointRequis->setText(txt.QString::setNum(nbPointsRequis));

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

