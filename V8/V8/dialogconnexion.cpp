#include "dialogconnexion.h"
#include "ui_dialogconnexion.h"
#include <QSqlQuery>
#include <QDebug>

DialogConnexion::DialogConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnexion)
{
    ui->setupUi(this);
    ui->Erreur->setHidden(true);
    db = new DataBase();
    db->openDataBase();
    db->restorDataBase();

    estConnecter = false;
    connect(ui->Connexion, SIGNAL(clicked()),this,SLOT(demandeConnexion()));
}

DialogConnexion::~DialogConnexion()
{
    delete ui;
}

void DialogConnexion::demandeConnexion(){
    ui->Erreur->setHidden(true);
    if(ui->LineLogin->text() == "" ||ui->LineMDP->text() == "" ) ui->Erreur->setHidden(false);
    else {
        //Vérification du mdp et login
        QSqlQuery query;
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
        id_joueur = query.value(0).toInt();
        log = query.value(1).toString();
        if (query.value(1).toString()==ui->LineLogin->text() && query.value(2).toString() == ui->LineMDP->text()) {
            estConnecter = true;
            qDebug() << "Login";
            this->close();

        }else {estConnecter = false;  qDebug() << "Fail";}

    }



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
