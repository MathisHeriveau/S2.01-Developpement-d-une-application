#include "database.h"
#include <QSqlQuery>

DataBase::DataBase()
{

}


bool DataBase::openDataBase(){
    this->mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    this->mydb.setDatabaseName(DATABASE_NAME);
    return this->mydb.open();
}

void DataBase::clseDataBase(){
    this->mydb.close();
}


bool DataBase::restorDataBase(){
    QSqlQuery query;
    QString insertions="Select * from JOUEUR";
    query.prepare(insertions);

    if(query.exec()){
        qDebug("Table existante");
    }else{
        qDebug("Table inexistante. Création de la table en cours...");
        QSqlQuery query;
        QString insertions="create table JOUEUR (id_joueur integer(3) primary key, login varchar(50), mdp varchar(50));";
        query.prepare(insertions);
        if(query.exec())  qDebug("Create table JOUEUR");
        else qDebug("Create table fail");
        if(insertJoueur()) qDebug("Insertion des premiers JOUEUR");
        else qDebug("Insert JOUEUR fail");

    }
    return true;
}

bool DataBase::insertJoueur()
{
     QSqlQuery query;
     if (!query.exec("insert into JOUEUR values(1, 'root', 'root');")) return false;

     QString insertions="insert into JOUEUR values(?, ?, ?);";
     query.prepare(insertions);

     QVariantList id;
     id << 2 ;
     query.addBindValue(id);

     QVariantList login;
     login << "SAE";
     query.addBindValue(login);

     QVariantList mdp;
     mdp << "1234";
     query.addBindValue(mdp);

     if (!query.execBatch()) return false;

     return true;
}
