#include "dialogconnexion.h"
#include "ui_dialogconnexion.h"
#include "dialoginscription.h"
#include <QSqlQuery>
#include <QDebug>

DialogConnexion::DialogConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnexion)
{
    ui->setupUi(this);

    ui->Erreur->setHidden(true);

    // Connexion à la base de données
    db = new DataBase();
    db->openDataBase();
    db->restorDataBase();

    // Regle ergonomique
    ui->Connexion->setDefault(true);

    ui->Erreur->setStyleSheet ("QLabel {color : blue; }");
    estConnecter = false;

    // Connecter les boutons
    connect(ui->Connexion, SIGNAL(clicked()),this,SLOT(demandeConnexion()));
    connect(ui->inscrire,SIGNAL(clicked()), this, SLOT(demandeInscripion()));
    connect(ui->Quitter,SIGNAL(clicked()), this,SLOT(demandeQuitter()));
}

DialogConnexion::~DialogConnexion()
{
    delete ui;
}

void DialogConnexion::demandeConnexion(){

    // Récupération des données du formulaire
    ui->Erreur->setHidden(true);
    if(ui->LineLogin->text() == "" ||ui->LineMDP->text() == "" ) ui->Erreur->setHidden(false);
    else {
        //Vérification du mdp et login
        QSqlQuery query;
        // Préparation de la requête
        QString insertions="select * from JOUEUR where login = ? and mdp = ?";
        query.prepare(insertions);

        QVariantList login;
        login << ui->LineLogin->text() ;
        query.addBindValue(login);

        QVariantList mdp;
        mdp << ui->LineMDP->text();
        query.addBindValue(mdp);

        if (!query.execBatch()) qDebug() << "Lancement de la vérification fail";

        query.next();

        // Récupération des données du joueur
        id_joueur = query.value(0).toInt();
        log = query.value(1).toString();

        // Si le joueur arrive a se connecté
        if (query.value(1).toString()==ui->LineLogin->text() && query.value(2).toString() == ui->LineMDP->text()) {
            estConnecter = true;
            this->close();

        }else {
            estConnecter = false;
            ui->Erreur->setHidden(false);
            ui->Erreur->setText("Les informations que vous avez rentrer ne sont pas valide, veillez vérifier votre login ainsi que votre mot de passe.");
        }

    }



}

void DialogConnexion::demandeInscripion(){
    DialogInscription* maDLG = new DialogInscription;
    maDLG->exec();
}

void DialogConnexion::demandeQuitter(){
    quitter=true;
    this->close();
}
bool DialogConnexion::getEstConnecter(){
    return estConnecter;
}

bool DialogConnexion::getQuitter(){
    return quitter;
}

int DialogConnexion::getId(){
    return  id_joueur;
}

QString DialogConnexion::getLog(){
    return log;
}
