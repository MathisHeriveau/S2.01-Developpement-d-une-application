#include "database.h"
#include <QSqlQuery>
#include <QDateTime>
#include <qDebug>

DataBase::DataBase()
{

}


bool DataBase::openDataBase(){
    // on crée une connexion à la base de données
    this->mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    this->mydb.setDatabaseName(DATABASE_NAME);
    return this->mydb.open();
}

void DataBase::clseDataBase(){
    // on ferme la connexion à la base de données
    this->mydb.close();
}


bool DataBase::restorDataBase(){
    QSqlQuery query;

    // On test si la table existe
    QString insertions="Select * from JOUEUR";
    query.prepare(insertions);

    if(query.exec()){
        // Si la table existe on affiche un message d'erreur
        qDebug("Table JOUEUR existante");
    }else{
        // Si la table n'existe pas on la crée
        qDebug("Table inexistante. Création de la table en cours...");
        QSqlQuery query;
        // On crée la table JOUEUR
        QString insertions="create table JOUEUR (id_joueur integer(3) primary key, login varchar(50), mdp varchar(50));";
        query.prepare(insertions);
        if(query.exec())  qDebug("Create table JOUEUR");
        else qDebug("Create table fail");

        // On inserte des données dans la table JOUEUR
        if(insertJoueur()) qDebug("Insertion des premiers JOUEUR");
        else qDebug("Insert JOUEUR fail");

    }
    return true;
}

bool DataBase::insertJoueur()
{
    // On insère des données dans la table JOUEUR

    // Premier possibilité d'insérer des données
     QSqlQuery query;
     if (!query.exec("insert into JOUEUR values(1, 'root', 'root');")) return false;

    // Deuxième possibilité d'insérer des données
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

    // On véfifie si la table Resultat existe
    QString insertions="Select * from RESULTAT";
    query.prepare(insertions);

    if(query.exec()){
        // Si la table existe on affiche un message d'erreur
        qDebug("Table RESULTAT existante");
    }else{
        // Si la table n'existe pas on la crée
        qDebug("Table inexistante. Création de la table en cours...");
        QSqlQuery query;
        // On crée la table RESULTAT
        QString insertions="create table RESULTAT (id_resultat integer(6) primary key,horodatage DATE, nomJoueurHumain varchar(50),scoreJoueurHumain integer(6), nomJoueurMachine varchar(50),scoreJoueurMachine integer(6), id_joueur integer(3),foreign key (id_joueur) REFERENCES JOUEUR(id_joueur));";
        query.prepare(insertions);
        if(query.exec())  qDebug("Create table RESULTAT");
        else qDebug("Create table fail");
    }

    // On insère les données dans la table RESULTAT
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
