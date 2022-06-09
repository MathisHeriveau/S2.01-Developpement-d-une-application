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

    /**
     * @brief Get the Est Connecter object
     * 
     * @return true si le joueur est connecté
     * @return false si le joueur n'est pas connecté
     */
    bool getEstConnecter();

    /**
     * @brief Get the Quitter object
     * 
     * @return true si le joueur a quitté
     * @return false si le joueur n'a pas quitté
     */

    bool getQuitter();

    /**
     * @brief Get the Id object
     * 
     * @return int id du joueur
     */

    int getId();

    /**
     * @brief Get the Log object
     * 
     * @return QString log du joueur
     */
    QString getLog();

private slots:
    /**
     * @brief Slot pour le bouton connexion qui permet de se connecter
     * et verifie si le login et le mot de passe sont corrects
     * et recupere les données du joueur
     */
    void demandeConnexion();

    /**
     * @brief Slot pour le bouton quitter qui permet de quitter le jeu
     * et de fermer la fenetre
     */

    void demandeQuitter();

private:
    Ui::DialogConnexion *ui; // UI de la fenetre de connexion
    DataBase *db;               // Base de données
    bool estConnecter;  // booléen pour savoir si le joueur est connecté
    bool quitter;       // booléen pour savoir si le joueur a quitté
    int id_joueur;      // id du joueur
    QString log;        // login du joueur
};

#endif // DIALOGCONNEXION_H
