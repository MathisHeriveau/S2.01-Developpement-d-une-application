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

    /**
     * @brief Fonction permettant d'actualiser la vue en fonction d'un état
     * @param coupJ Le coup du joueur
     * @param coupM Le coup du machine
     * @param scoreJ Le score du joueur
     * @param scoreM Le score de la machine
     * @param e L'état du jeu
     * @param tps Le temps écoulé
     * 
     */
    void actualisation(modele::UnCoup, modele::UnCoup, int scoreJ,int scoreM, modele::Etat, unsigned int);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
