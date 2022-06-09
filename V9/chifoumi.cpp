#include "chifoumi.h"
#include "ui_chifoumi.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuration des premiers elements de la fenetre
    ui->iconFeuille->setEnabled(false);
    ui->iconCiseau->setEnabled(false);
    ui->iconPierre->setEnabled(false);
    ui->Pause->setEnabled(false);
    ui->NvllPartie->setEnabled(true);

    srand(time(NULL));

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
    connect(ui->actionParametre,SIGNAL(triggered()),c,SLOT(parametre()));
    connect(ui->actionResultat,SIGNAL(triggered()),c,SLOT(resultat()));
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
    disconnect(ui->actionParametre,SIGNAL(triggered()),c,SLOT(parametre()));
    disconnect(ui->actionResultat,SIGNAL(triggered()),c,SLOT(resultat()));
}

void MainWindow::actualisation(modele::UnCoup coupJ, modele::UnCoup coupM, int scoreJ,int scoreM, modele::Etat e, int tps, int tpsMax, QString nomj){
    QString txt;

    //actualisation du nom du joueur
    ui->labelVous->setText(nomj);

    // actualisation en fonction de l'etat
    switch (e) {
        case modele::initialiser:

            // Configuration des premiers elements de la fenetre
            ui->iconFeuille->setEnabled(false);
            ui->iconCiseau->setEnabled(false);
            ui->iconPierre->setEnabled(false);
            ui->Pause->setEnabled(false);
            ui->NvllPartie->setEnabled(true);
            ui->NvllPartie->setDefault(true);
            break;

        case modele::fin:

            // Si le temps n'est pas écoulé, on affiche le message de fin de partie et on affiche le score
            if(tps!=0){
                tps = tpsMax - tps;
                if(scoreJ > scoreM){
                    QMessageBox::information(this, "Fin de la partie gagnant", "Bravo "+ nomj+ ". Vous gagnez la partie avec " + txt.QString::setNum(scoreJ) + " points en " + QString::number(tps)+ " secondes. ");
                }
                else{
                    QMessageBox::information(this, "Fin de la partie perdant", "Dommage "+nomj+". Vous avez perdu la partie avec " + txt.QString::setNum(scoreJ) + " points en " + QString::number(tps)+ " secondes. ");
                }
            }
            // Sinon, on affiche le message de fin de partie avec le tempe de la partie
            else{
                tps = tpsMax - tps;
                if(scoreJ > scoreM){
                    QMessageBox::information(this, "Helas chers joueurs, temps de jeu fini !", "Bravo "+ nomj+ ". Vous gagnez la partie avec " + txt.QString::setNum(scoreJ) + " points.");
                }
                else if(scoreJ == scoreM){
                    QMessageBox::information(this, "Helas chers joueurs, temps de jeu fini !", "Egalité...");
                }
                else{
                    QMessageBox::information(this,  "Helas chers joueurs, temps de jeu fini !", "La machine termine toutefois mieux, avec " + txt.QString::setNum(scoreM) + " points.");
                }
            }

            // Réinitialisation des elements de la fenetre
            ui->iconFeuille->setEnabled(false);
            ui->iconCiseau->setEnabled(false);
            ui->iconPierre->setEnabled(false);
            ui->Pause->setEnabled(false);
            ui->NvllPartie->setEnabled(true);
            ui->NvllPartie->setDefault(true);
        break;


        case modele::enPause:

            // Mise en place des régles ergonomiques
            ui->iconFeuille->setEnabled(false);
            ui->iconCiseau->setEnabled(false);
            ui->iconPierre->setEnabled(false);
            ui->Pause->setText("Reprise jeu");
            ui->Pause->setDefault(true);
            ui->NvllPartie->setEnabled(false);

        break;

        case modele::enCours:
            
            // Mise en place des régles ergonomiques
            ui->Pause->setDefault(false);
            ui->NvllPartie->setDefault(true);

            // Configuration des elements de la fenetre
            ui->iconFeuille->setEnabled(true);
            ui->iconCiseau->setEnabled(true);
            ui->iconPierre->setEnabled(true);
            ui->Pause->setText("Pause");
            ui->Pause->setEnabled(true);
            ui->NvllPartie->setEnabled(true);

            // Choix de couleur nom du joueur et score en bleu
            ui->labelVous->setStyleSheet("color: blue;");
            ui->labelScoreVous->setStyleSheet("color: blue;");

            // Mise a jour des scores 
            ui->labelScoreMachine->setText(txt.QString::setNum(scoreM));
            ui->labelScoreVous->setText(txt.QString::setNum(scoreJ));

            switch (coupJ) {
                // Mise a jour des icones du joueur
                case modele::UnCoup::pierre: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/pierre.gif"));  break;
                case modele::UnCoup::ciseau: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/ciseau.gif")); break;
                case modele::UnCoup:: papier: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/papier.gif"));break;
                case modele::UnCoup::rien: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/rien.gif")); break;
            }

            switch (coupM) {
                // Mise a jour des icones de la machine
                case modele::UnCoup::pierre: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/pierre.gif")); break;
                case modele::UnCoup::ciseau: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/ciseau.gif")); break;
                case modele::UnCoup::papier: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/papier.gif")); break;
                case modele::UnCoup::rien: ui->iconMachine->setPixmap(QPixmap(":/chifoumi/images/rien.gif")); break;
            }
            break;



    }


}

void MainWindow::majTimer(int temps){
    // Mise a jour du timer
    ui->timer->setText(QString::number(temps));
}

void MainWindow::majParametre( QString nom, int nbMaxPts, int tmpsMax){
    // Mise a jour des parametres
    ui->labelVous->setText(nom);
    majTimer(tmpsMax);
    ui->labelNbPointRequis->setText(QString::number(nbMaxPts));

}


