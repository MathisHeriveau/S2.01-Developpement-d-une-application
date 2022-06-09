#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"
#include <QTimer>

class MainWindow;
class presentation : public QObject
{
    Q_OBJECT
public:
    explicit presentation(modele* m,QObject *parent = nullptr);

    modele* _leModele;
    MainWindow* _laVue;

public:
    modele* getModele();
    MainWindow* getVue();
    void setModele(modele *m);
    void setVue(MainWindow *m);

private:
    void coupJoueurJoue();

public slots:
    void boutonFeuille();
    void boutonCiseau();
    void boutonPierre();
    void nvllePartieDemandee();
    void aProposDe();
    void demandePause();

private slots:
    void updateTimer();

private:
    QTimer* _time;
    int tmps;
};

#endif // PRESENTATION_H
