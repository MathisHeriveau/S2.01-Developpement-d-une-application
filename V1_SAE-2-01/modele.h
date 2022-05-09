#ifndef MODELE_H
#define MODELE_H

#include <QObject>

class modele : public QObject
{
    Q_OBJECT
public:
    explicit modele(QObject *parent = nullptr);


public:
    enum UnCoup {pierre, papier, ciseau, rien};

    ///* Méthodes du Modéle
public:
        // Getters
    UnCoup getCoupJoueur();
        /* retourne le dernier coup joué par le joueur */
    UnCoup getCoupMachine();
        /* retourne le dernier coup joué par le joueur */
    unsigned int getScoreJoueur();
        /* retourne le score du joueur */
    unsigned int getScoreMachine();
        /* retourne le score de la machine */
    char determinerGagnant();
        /* détermine le gagnant 'J' pour joueur, 'M' pour machine, 'N' pour match nul
           en fonction du dernier coup joué par chacun d'eux */

    // Setters
public:
    void setCoupJoueur(UnCoup p_coup);
        /* initialise l'attribut coupJoueur avec la valeur
           du paramétre p_coup */
    void setCoupMachine(UnCoup p_coup);
        /* initialise l'attribut coupmachine avec la valeur
           du paramétre p_coup */
    void setScoreJoueur(unsigned int p_score);
        /* initialise l'attribut scoreJoueur avec la valeur
           du paramétre p_score */
    void setScoreMachine(unsigned int p_score);
        /* initialise l'attribut coupMachine avec la valeur
           du paramétre p_score */

    // Autres modificateurs
    void majScores(char p_gagnant);
        /* Mise é jour des scores en fonction des régles de gestion actuelles :
            - 1 point pour le gagnant lorsqu'il y a un gagnant
            - 0 point en cas de match nul
        */
    void initScores();
        /* initialise é 0 les attributs scoreJoueur et scoreMachine
           NON indispensable */
    void initCoups();
        /* initialise é rien les attributs coupJoueur et coupMachine
           NON indispensable */


    ///* Méthodes utilitaires du Modéle
   UnCoup genererUnCoup();
/* retourne une valeur aléatoire = pierre, papier ou ciseau.
  Utilisée pour faire jouer la machine */


private:
    unsigned int scoreJoueur;   // score actuel du joueur
    unsigned int scoreMachine;  // score actuel de la Machine
    UnCoup coupJoueur;          // dernier coup joué par le joueur
    UnCoup coupMachine;         // dernier coup joué par la machine

};

#endif // MODELE_H
