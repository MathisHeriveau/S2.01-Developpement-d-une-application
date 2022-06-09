#ifndef DIALOGRESULTAT_H
#define DIALOGRESULTAT_H

#include <QDialog>
#include "database.h"

namespace Ui {
class DialogResultat;
}

class DialogResultat : public QDialog
{
    Q_OBJECT

public:
    explicit DialogResultat(QWidget *parent = nullptr);
    ~DialogResultat();
    /**
     * @brief Fonction qui permet d'actualiser le tableau des resultats
     * 
     */
    void actualisation();

private:
    Ui::DialogResultat *ui; //!< UI de la fenêtre
    DataBase* db;           //!< Base de données
};

#endif // DIALOGRESULTAT_H
