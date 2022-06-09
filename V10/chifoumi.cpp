#include "chifoumi.h"
#include "ui_chifoumi.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisation de la vue
    ui->iconFeuille->setEnabled(false);
    ui->iconCiseau->setEnabled(false);
    ui->iconPierre->setEnabled(false);
    ui->Pause->setEnabled(false);
    ui->NvllPartie->setEnabled(true);
    ui->NvllPartie->setDefault(true);

    // Passage en mode light
    modeDark(false);

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
    // Actualisation de la vue
    ui->labelVous->setText(nomj);
    switch (e) {
        case modele::initialiser:
            // Parametrage de la vue
            ui->iconFeuille->setEnabled(false);
            ui->iconCiseau->setEnabled(false);
            ui->iconPierre->setEnabled(false);
            ui->Pause->setEnabled(false);
            ui->NvllPartie->setEnabled(true);
            ui->NvllPartie->setDefault(true);
            break;
        case modele::fin:

            // Si le temps n'est pas écoulé
            if(tps!=0){
                tps = tpsMax - tps;
                if(scoreJ > scoreM){
                    QMessageBox::information(this, "Fin de la partie gagnant", "Bravo "+ nomj+ ". Vous gagnez la partie avec " + txt.QString::setNum(scoreJ) + " points en " + QString::number(tps)+ " secondes. ");
                }
                else{
                    QMessageBox::information(this, "Fin de la partie perdant", "Dommage "+nomj+". Vous avez perdu la partie avec " + txt.QString::setNum(scoreJ) + " points en " + QString::number(tps)+ " secondes. ");
                }
            } // SI le temps est écoulé
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

            // Reinitialisation de la vue
            ui->iconFeuille->setEnabled(false);
            ui->iconCiseau->setEnabled(false);
            ui->iconPierre->setEnabled(false);
            ui->Pause->setEnabled(false);
            ui->NvllPartie->setEnabled(true);
            ui->NvllPartie->setDefault(true);
        break;




        case modele::enPause:
            // Parametrage de la vue
            ui->iconFeuille->setEnabled(false);
            ui->iconCiseau->setEnabled(false);
            ui->iconPierre->setEnabled(false);
            ui->Pause->setText("Reprise jeu");
            ui->Pause->setDefault(true);
            ui->NvllPartie->setEnabled(false);
        break;

        case modele::enCours:
            // Regle d'ergonomie
            ui->Pause->setDefault(false);
            ui->NvllPartie->setDefault(true);

            ui->iconFeuille->setEnabled(true);
            ui->iconCiseau->setEnabled(true);
            ui->iconPierre->setEnabled(true);
            ui->Pause->setText("Pause");
            ui->Pause->setEnabled(true);
            ui->NvllPartie->setEnabled(true);


            // Mise a jour des scores
            ui->labelScoreMachine->setText(txt.QString::setNum(scoreM));
            ui->labelScoreVous->setText(txt.QString::setNum(scoreJ));

            switch (coupJ) {
                // Mise a jour de l'image coup du joueur
                case modele::UnCoup::pierre: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/pierre.gif"));  break;
                case modele::UnCoup::ciseau: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/ciseau.gif")); break;
                case modele::UnCoup:: papier: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/papier.gif"));break;
                case modele::UnCoup::rien: ui->iconVous->setPixmap(QPixmap(":/chifoumi/images/rien.gif")); break;
            }

            switch (coupM) {
                // Mise a jour de l'image coup de la machine
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

void MainWindow::majParametre( QString nom, int nbMaxPts, int tmpsMax){
    ui->labelVous->setText(nom);
    majTimer(tmpsMax);
    ui->labelNbPointRequis->setText(QString::number(nbMaxPts));

}

void MainWindow::modeDark(bool e){
    if (e){
        QString  menuStyle(
                    "MainWindow{background-color:rgba(83,83,83,83);}"
                    "QLabel"
                    "{"
                        "border: 2px solid black;"
                        "border-radius: 4px;"
                        "padding: 2px;"
                        "background-color: rgb(75,75,75);"
                        "color: beige;"
                    "}"

                   " QGroupBox {"
                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                          "stop: 0 rgba(83,83,83,83), stop: 1 #FFFFFF);"
                        "border: 2px solid gray;"
                        "border-radius: 5px;"
                        "margin-top: 1ex; /* leave space at the top for the title */"
                    "}"

                    "QGroupBox::title {"
                        "subcontrol-origin: margin;"
                        "subcontrol-position: top center; /* position at the top center */"
                        "padding: 0 3px;"
                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                          "stop: 0 rgb(200,200,200), stop: 1 #FFFFFF);"
                    "}"

                    "QPushButton{ "
                        "background-color: rgb(75,75,75);"
                        "color: beige;"
                    "}"

                    "QMenu"
                    "{"
                        "background-color: rgb(75, 75, 75);"
                    "}"

                    "QMenu::item"
                    "{"
                        "background-color: rgb(0, 170, 127);"
                        "color: rgb(255, 255, 255);"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "border-color: beige;"
                        "font: bold ;padding:2px;}"
                    "}"

                    "QMenu::item:selected"
                    "{"
                        "background-color: rgb(0, 85, 127);"
                        "color: rgb(255, 255, 255);"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "border-color: beige;"
                        "font: bold ;padding:3px;}"
                    "}"




               );
        qDebug() << "Erreur inconnu juste au dessous";
        this->setStyleSheet(menuStyle);
        qDebug() << "Erreur inconnu juste au dessus";
        ui->labelVous->setStyleSheet("color: beige;");
        ui->labelScoreVous->setStyleSheet("color: beige;");

    }
    else{
        QString  menuStyle(
                    "MainWindow{background-color:beige;}"
                    "QLabel"
                    "{"
                        "border: 1px solid black;"
                        "border-radius: 4px;"
                        "padding: 2px;"
                        "background-color: rgb(175,175,175);"
                        "color: black;"
                    "}"

                   " QGroupBox {"
                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                          "stop: 0 rgba(165,165,165,83), stop: 1 #FFFFFF);"
                        "border: 2px solid gray;"
                        "border-radius: 5px;"
                        "margin-top: 1ex; /* leave space at the top for the title */"
                    "}"

                    "QGroupBox::title {"
                        "subcontrol-origin: margin;"
                        "subcontrol-position: top center; /* position at the top center */"
                        "padding: 0 3px;"
                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                          "stop: 0 rgba(165,165,165,83), stop: 1 #FFFFFF);"
                    "}"

                    "QPushButton{ "
                        "background-color: rgb(175,175,175);"
                        "color: black;"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "border-color: black;"
                        "padding:6px;"
                    "}"

                    "QMenu"
                    "{"
                        "background-color:  rgb(175,175,175);"
                    "}"

                    "QMenu::item"
                        "{"
                        "background-color: rgb(0, 170, 127);"
                        "color: rgb(255, 255, 255);"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "border-color: black;"
                        "font: bold ;padding:2px;}"
                    "}"

                    "QMenu::item:selected"
                    "{"
                        "background-color: rgb(0, 85, 127);"
                        "color: rgb(255, 255, 255);"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "border-color: black;"
                        "font: bold ;padding:3px;}"
                    "}"




               );
        qDebug() << "Erreur inconnu juste au dessous";
        this->setStyleSheet(menuStyle);
        qDebug() << "Erreur inconnu juste au dessus";
        ui->labelVous->setStyleSheet("color: light blue;");
        ui->labelScoreVous->setStyleSheet("color: light blue;");

    }
}




