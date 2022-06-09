#include "database.h"
#include <QSqlQuery>
#include <QDateTime>

DataBase::DataBase()
{

}


bool DataBase::openDataBase(){
    // Connexion à la base de données
    this->mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    this->mydb.setDatabaseName(DATABASE_NAME);
    return this->mydb.open();
}

void DataBase::clseDataBase(){
    // Déconnexion de la base de données
    this->mydb.close();
}


bool DataBase::restorDataBase(){
    QSqlQuery query;

    // Test de l'existence de la table joueur
    QString insertions="Select * from JOUEUR";
    query.prepare(insertions);

    if(query.exec()){
        qDebug("Table JOUEUR existante");
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
     // Premiere insertion des joueurs
     if (!query.exec("insert into JOUEUR values(1, 'root', 'root');")) return false;

    // Deuxieme insertion des joueurs
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

bool DataBase::insertScore(int idJ, QString nomJ,int scoreJ, int scoreM){
    QSqlQuery query;

    // Test de l'existence de la table Resultat
    QString insertions="Select * from RESULTAT";
    query.prepare(insertions);

    if(query.exec()){
        qDebug("Table RESULTAT existante");
    }else{
        qDebug("Table inexistante. Création de la table en cours...");
        QSqlQuery query;
        QString insertions="create table RESULTAT (id_resultat integer(6) primary key,horodatage DATE, nomJoueurHumain varchar(50),scoreJoueurHumain integer(6), nomJoueurMachine varchar(50),scoreJoueurMachine integer(6), id_joueur integer(3),foreign key (id_joueur) REFERENCES JOUEUR(id_joueur));";
        query.prepare(insertions);
        if(query.exec())  qDebug("Create table RESULTAT");
        else qDebug("Create table fail");
    }

    // Insertion des scores

    insertions="INSERT INTO `RESULTAT`(`id_resultat`, `horodatage`, `nomJoueurHumain`, `scoreJoueurHumain`, `nomJoueurMachine`, `scoreJoueurMachine`, `id_joueur`) VALUES (?,?,?,?,?,?,?)";
    query.prepare(insertions);

    QSqlQuery maxID;
    if(!maxID.exec("select MAX(id_resultat) from RESULTAT")) return false;
    maxID.next();

    QVariantList idResultat;
    idResultat << maxID.value(0).toInt()+1;
    query.addBindValue(idResultat);

    QVariantList date;
    date << QDateTime::currentDateTime().toString("yyyy/MM/dd");
    query.addBindValue(date);


    QVariantList nomJoueur;
    nomJoueur << nomJ;
    query.addBindValue(nomJoueur);

    QVariantList scoreJoueur;
    scoreJoueur << scoreJ;
    query.addBindValue(scoreJoueur);

    QVariantList nomMachine;
    nomMachine << "Machine";
    query.addBindValue(nomMachine);

    QVariantList scoreMachine;
    scoreMachine << scoreM;
    query.addBindValue(scoreMachine);

    QVariantList id;
    id << idJ ;
    query.addBindValue(id);

    if (!query.execBatch()) {
        qDebug("Insert score Fail");
        return false;
    }
    else qDebug("Insert score réussit");
    return true;
}

bool DataBase::insertUnJoueur(QString name, QString motDePasse){
    QSqlQuery query;

    QString insertions="insert into JOUEUR values(?, ?, ?);";
    query.prepare(insertions);


    QSqlQuery maxID;
    if(!maxID.exec("select MAX(id_joueur) from JOUEUR")) return false;
    maxID.next();

    QVariantList idJoueur;
    idJoueur << maxID.value(0).toInt()+1;
    query.addBindValue(idJoueur);

    QVariantList login;
    login << name;
    query.addBindValue(login);

    QVariantList mdp;
    mdp << motDePasse;
    query.addBindValue(mdp);

    if (!query.execBatch()) return false;

    return true;
    return true;
}
