#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "modele.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // pour créer une connexion avec la présentation
    void nvlleConnexion(QObject *c);
    void supprConnexion(QObject *c);

    void actualisation(modele::UnCoup, modele::UnCoup, int scoreJ,int scoreM, modele::Etat, int, int);
    void majTimer(int);
    void majParametre( QString nom, int nbMaxPts, int tmpsMax);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
