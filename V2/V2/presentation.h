#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"

class MainWindow;
class presentation : public QObject
{
    Q_OBJECT
public:
    explicit presentation(modele* m,QObject *parent = nullptr);

    modele* _leModele;
    MainWindow* _laVue;

public:
    /**
     * @brief Get the Modele object
     * 
     * @return modele* le modele de l'application
     */
    modele* getModele();
    /**
     * @brief Get the Vue object
     * 
     * @return MainWindow* vue de l'application
     */
    MainWindow* getVue();

    /**
     * @brief Set the Modele object
     * 
     * @param m modele* le modele de l'application
     */
    void setModele(modele *m);
    /**
     * @brief Set the Vue object
     * 
     * @param m MainWindow* vue de l'application
     */
    void setVue(MainWindow *m);

private:
    /**
     * @brief Fonction qui permet de faire jouer le jeu
     */
    void coupJoueurJoue();

public slots:
     /**
     * @brief Slot pour le bouton Feuille qui permet de jouer
     */
    void boutonFeuille();
    /**
     * @brief Slot pour le bouton Ciseau qui permet de jouer
     */
    void boutonCiseau();
    /**
     * @brief Slot pour le bouton Pierre qui permet de jouer
     */
    void boutonPierre();
    /**
     * @brief Slot pour le bouton Nouvelle Partie qui permet de relancer une partie
     */
    void nvllePartieDemandee();
};

#endif // PRESENTATION_H
