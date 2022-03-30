/**
 * @file chifoumi.h
 * @author Mathis HERIVEAU, Arthur LE MENN, Colas NAUDI
 * @brief 
 * @version 0.1
 * @date 30-03-2022
 * 
 * @copyright Copyright (c) 2022
 * 
**/

#ifndef CHIFOUMI_H
#define CHIFOUMI_H
#include <iostream>

using namespace std;

class Chifoumi
{
    ///* ---- PARTIE MOD�LE ---------------------------

        ///* Une d�finition de type �num�r�
    public:
        enum UnCoup {pierre, papier, ciseau, rien};

        ///* M�thodes du Mod�le
    public:
        Chifoumi();
        virtual ~Chifoumi();

        // Getters
        UnCoup getCoupJoueur();
            /* retourne le dernier coup jou� par le joueur */
        UnCoup getCoupMachine();
            /* retourne le dernier coup jou� par le joueur */
        unsigned int getScoreJoueur();
            /* retourne le score du joueur */
        unsigned int getScoreMachine();
            /* retourne le score de la machine */
        char determinerGagnant();
            /* d�termine le gagnant 'J' pour joueur, 'M' pour machine, 'N' pour match nul
               en fonction du dernier coup jou� par chacun d'eux */

         ///* M�thodes utilitaires du Mod�le
    private :
        UnCoup genererUnCoup();
    /* retourne une valeur al�atoire = pierre, papier ou ciseau.
       Utilis�e pour faire jouer la machine */

        // Setters
    public:
        void setCoupJoueur(UnCoup p_coup);
            /* initialise l'attribut coupJoueur avec la valeur
               du param�tre p_coup */
        void setCoupMachine(UnCoup p_coup);
            /* initialise l'attribut coupmachine avec la valeur
               du param�tre p_coup */
        void setScoreJoueur(unsigned int p_score);
            /* initialise l'attribut scoreJoueur avec la valeur
               du param�tre p_score */
        void setScoreMachine(unsigned int p_score);
            /* initialise l'attribut coupMachine avec la valeur
               du param�tre p_score */

        // Autres modificateurs
        void majScores(char p_gagnant);
			/* Mise � jour des scores en fonction des r�gles de gestion actuelles :
				- 1 point pour le gagnant lorsqu'il y a un gagnant
				- 0 point en cas de match nul
			*/
        void initScores();
            /* initialise � 0 les attributs scoreJoueur et scoreMachine
               NON indispensable */
        void initCoups();
            /* initialise � rien les attributs coupJoueur et coupMachine
               NON indispensable */


         ///* Attributs du Mod�le
    private:
        unsigned int scoreJoueur;   // score actuel du joueur
        unsigned int scoreMachine;  // score actuel de la Machine
        UnCoup coupJoueur;          // dernier coup jou� par le joueur
        UnCoup coupMachine;         // dernier coup jou� par la machine
};

#endif // CHIFOUMI_H
