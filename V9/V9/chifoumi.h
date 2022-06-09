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
     * @param tpsMax Le temps maximum
     * @param nomj Le nom du joueur
     * 
     */
    void actualisation(modele::UnCoup, modele::UnCoup, int,int, modele::Etat, int, int ,QString);

    /**
     * @brief Fonction permettant d'actualiser le timer
     * @param tps Le temps actuel
     * 
     */
    void majTimer(int);

    /**
     * @brief Fonction permettant d'actualiser le nom du joueur, le nombre maximum de point et le temps maximum suite a
     *  un changement de parametre dans la fenetre de parametre
     * 
     * @param nom 
     * @param nbMaxPts 
     * @param tmpsMax 
     */
    void majParametre( QString nom, int nbMaxPts, int tmpsMax);


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
