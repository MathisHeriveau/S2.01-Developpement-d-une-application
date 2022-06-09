#include "dialogresultat.h"
#include "ui_dialogresultat.h"
#include <QSqlQuery>

DialogResultat::DialogResultat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogResultat)
{
    ui->setupUi(this);

    // On connecte les boutons
    connect(ui->BoutonQuitter,SIGNAL(clicked()),this,SLOT(close()));
    actualisation();
}

DialogResultat::~DialogResultat()
{
    delete ui;
}


void DialogResultat::actualisation(){
    QTableWidgetItem *newItem;

    QSqlQuery query;
    // Préparation de la requête
    QString insertions="select R.id_resultat,R.horodatage,R.nomJoueurHumain,R.scoreJoueurHumain,R.nomJoueurMachine,R.scoreJoueurMachine, J.login from RESULTAT R join JOUEUR J on R.id_joueur = J.id_joueur where R.scoreJoueurHumain > R.scoreJoueurMachine order by scoreJoueurHumain desc;";
    query.prepare(insertions);

    query.exec();

    // Réinitialisation de la table
    ui->TableauResultat->setRowCount(0);


    for(int i = 0; query.next() && i<10; i++){
        ui->TableauResultat->insertRow(i);
        newItem = new QTableWidgetItem(query.value(0).toString());
        ui->TableauResultat->setItem(i,0,newItem);
        newItem = new QTableWidgetItem(query.value(1).toString());
        ui->TableauResultat->setItem(i,1,newItem);
        newItem = new QTableWidgetItem(query.value(2).toString());
        ui->TableauResultat->setItem(i,2,newItem);
        newItem = new QTableWidgetItem(query.value(3).toString());
        ui->TableauResultat->setItem(i,3,newItem);
        newItem = new QTableWidgetItem(query.value(4).toString());
        ui->TableauResultat->setItem(i,4,newItem);
        newItem = new QTableWidgetItem(query.value(5).toString());
        ui->TableauResultat->setItem(i,5,newItem);
        newItem = new QTableWidgetItem(query.value(6).toString());
        ui->TableauResultat->setItem(i,6,newItem);
    }
}
