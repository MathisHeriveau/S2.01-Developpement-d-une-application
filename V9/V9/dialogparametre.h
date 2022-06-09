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

    /**
     * @brief Get the Nom object
     * 
     * @return QString le nom du joueur
     */
    QString getNom();

    /**
     * @brief Get the Nb Pts Max object
     * 
     * @return int le nombre maximum de point
     */
    int getNbPtsMax();

    /**
     * @brief Get the Tps Max object
     * 
     * @return int le temps maximum
     */
    int getTpsMax();

    /**
     * @brief Get the Enregistrer object
     * 
     * @return true si le joueur a enregistré
     * @return false si le joueur n'a pas enregistré
     */
    bool getEnregistrer();

private slots:
    /**
     * @brief Slot pour le bouton enregistrer qui permet de sauvegarder les paramètres
     */
    void enregistrer();

private:
    Ui::DialogParametre *ui; //!< UI de la fenêtre
    bool estEnregistrer;     //!< booléen qui permet de savoir si le joueur a enregistré
};

#endif // DIALOGPARAMETRE_H
