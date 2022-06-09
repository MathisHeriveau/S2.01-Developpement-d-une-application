#ifndef DIALOGPARAMETRE_H
#define DIALOGPARAMETRE_H

#include <QDialog>

namespace Ui {
class DialogParametre;
}

class DialogParametre : public QDialog
{
    Q_OBJECT

public:
    explicit DialogParametre(QWidget *parent = nullptr, QString = "Vous", int=5,int=30);
    ~DialogParametre();
    QString getNom();
    int getNbPtsMax();
    int getTpsMax();
    bool getEnregistrer();

private slots:
    void enregistrer();

private:
    Ui::DialogParametre *ui;
    bool estEnregistrer;
};

#endif // DIALOGPARAMETRE_H
