#include "dialogparametre.h"
#include "ui_dialogparametre.h"
#include <QDebug>

DialogParametre::DialogParametre(QWidget *parent, QString nom, int nbPtsMax,int tpsMax) :
    QDialog(parent),
    ui(new Ui::DialogParametre)
{
    ui->setupUi(this);
    // Configuration des premiers elements de la fenetre
    ui->SaisieNom->setText(nom);
    ui->SaisiePtsMax->setValue(nbPtsMax);
    ui->SaisieTmpMax->setValue(tpsMax);
    estEnregistrer = false;

    // Connexion des slots
    connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->Enregistrer,SIGNAL(clicked()),this,SLOT(enregistrer()));
}

DialogParametre::~DialogParametre()
{
    delete ui;
}


QString DialogParametre::getNom(){
    return ui->SaisieNom->text();
}
int DialogParametre::getNbPtsMax(){
    return ui->SaisiePtsMax->value();
}
int DialogParametre::getTpsMax(){
    return ui->SaisieTmpMax->value();
}

bool DialogParametre::getEnregistrer(){
    return estEnregistrer;
}

void DialogParametre::enregistrer(){
    estEnregistrer = true;
    qDebug() << "Fermeture";
    this->close();
}
