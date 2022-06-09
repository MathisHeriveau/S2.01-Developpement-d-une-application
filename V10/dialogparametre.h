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
    explicit DialogParametre(QWidget *parent = nullptr, QString = "Vous", int=5,int=30,bool=false);
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

    /**
     * @brief Get the Dark object
     * 
     * @return true si le joueur a choisi le mode noir
     * @return false si le joueur a choisi le mode blanc
     */
    bool getDark();

private slots:
    /**
     * @brief Slot pour le bouton enregistrer qui permet de sauvegarder les paramètres
     */
    void enregistrer();

private:
    Ui::DialogParametre *ui;   //interface graphique
    bool estEnregistrer;        //booléen pour savoir si le joueur a enregistré
    bool isDark;                //booléen pour savoir si le joueur a choisi le mode noir
};

#endif // DIALOGPARAMETRE_H
