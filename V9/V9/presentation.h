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

    modele* _leModele;  //!< Le modele de l'application
    MainWindow* _laVue; //!< La vue de l'application

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
    /**
     * @brief Fonction qui appel l'actualisation de la vue
     */
    void demandeActualisation();

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
    /**
     * @brief Slot pour le bouton Pause qui permet de visualiser la version et nom des créateurs
     */
    void aProposDe();
    /**
     * @brief Slot pour le bouton Pause qui permet de mettre le jeu en pause
     */
    void demandePause();
    /**
     * @brief Slot pour le bouton parametre qui permet de lancer la fenetre de parametre
     */
    void parametre();
    /**
     * @brief Slot pour le bouton resultat qui permet de lancer la fenetre de resultat
     */
    void resultat();

private slots:
    /**
     * @brief Slot pour le timer qui permet de actualiser la vue
     */
    void updateTimer();

private:
    QTimer* _time;  //!< Le timer de l'application
    int tmps;       //!< Le temps actuel
};

#endif // PRESENTATION_H
