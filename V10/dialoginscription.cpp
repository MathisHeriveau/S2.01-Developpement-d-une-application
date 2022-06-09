#include "dialoginscription.h"
#include "ui_dialoginscription.h"
#include <QMessageBox>

DialogInscription::DialogInscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInscription)
{
    ui->setupUi(this);

    
    ui->Erreur->setHidden(true);
    ui->Erreur->setStyleSheet ("QLabel {color : blue; }");

    // Connexion au slot de demande d'inscription
    connect(ui->Cancel,SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->Creer,SIGNAL(clicked()), this, SLOT(demandeCreer()));
}

DialogInscription::~DialogInscription()
{
    delete ui;
}

void DialogInscription::demandeCreer(){
    // Récupération des données du formulaire
    ui->Erreur->setHidden(true);
    if(ui->login->text()!="" && ui->mdp->text()!="" && ui->mdp->text() ==ui->mdpConfirme->text()){
        //Vérification du mdp et login
        if(db->insertUnJoueur(ui->login->text(),ui->mdp->text())){
            // Si la requête a été effectuée avec succès on affiche un message de confirmation
            QMessageBox *msgbox = new QMessageBox;
            msgbox->setWindowTitle("Création d'un compte réussi");
            msgbox->setText("Vous venez de creer votre compte :\nVotre login : " + ui->login->text() + "\nGarder votre mot de passe");
            msgbox->setStandardButtons(QMessageBox::Ok);
            msgbox->exec();

        }
        this->close();
    }
    // Si les données sont incorrectes on affiche un message d'erreur
    else if(ui->login->text()!="" && ui->mdp->text()!="" && ui->mdp->text()!=ui->mdpConfirme->text()){
        ui->Erreur->setText("Votre mot de passe n'est pas le même, veillez verifier.");
        ui->Erreur->setHidden(false);
    }else if(ui->login->text()=="" || ui->mdp->text()=="" ||  ui->mdpConfirme->text()==""){
        ui->Erreur->setText("Veillez remplir toute les cases.");
        ui->Erreur->setHidden(false);
    }



}

