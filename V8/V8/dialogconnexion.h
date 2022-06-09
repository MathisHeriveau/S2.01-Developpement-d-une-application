#ifndef DIALOGCONNEXION_H
#define DIALOGCONNEXION_H

#include <QDialog>
#include "database.h"

namespace Ui {
class DialogConnexion;
}

class DialogConnexion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnexion(QWidget *parent = nullptr);
    ~DialogConnexion();

    bool getEstConnecter();
    bool getQuitter();
    int getId();
    QString getLog();

private slots:
    void demandeConnexion();
    void demandeQuitter();

private:
    Ui::DialogConnexion *ui;
    DataBase *db;
    bool estConnecter;
    bool quitter;
    int id_joueur;
    QString log;
};

#endif // DIALOGCONNEXION_H
