#include "dialogparametre.h"
#include "ui_dialogparametre.h"
#include <QDebug>

DialogParametre::DialogParametre(QWidget *parent, QString nom, int nbPtsMax,int tpsMax, bool dark) :
    QDialog(parent),
    ui(new Ui::DialogParametre)
{
    ui->setupUi(this);

    // On initialise les paramètres
    isDark = dark;
    ui->SaisieNom->setText(nom);
    ui->SaisiePtsMax->setValue(nbPtsMax);
    ui->SaisieTmpMax->setValue(tpsMax);
    ui->darckRadio->setChecked(isDark);

    estEnregistrer = false;

    // On connecte les boutons
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
    // On enregistre les paramètres
    estEnregistrer = true;
    if (ui->darckRadio->isChecked()) isDark =true;
    else isDark = false;
    this->close();
}

bool DialogParametre::getDark(){
    return isDark;
}


