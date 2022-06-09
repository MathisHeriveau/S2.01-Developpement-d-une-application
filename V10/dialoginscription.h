#ifndef DIALOGINSCRIPTION_H
#define DIALOGINSCRIPTION_H

#include <QDialog>
#include "database.h"

namespace Ui {
class DialogInscription;
}

class DialogInscription : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInscription(QWidget *parent = nullptr);
    ~DialogInscription();

public slots :
    /**
     * @brief Slot pour le bouton inscription qui permet d'inscrire un nouveau joueur
     */
    void demandeCreer();

private:
    Ui::DialogInscription *ui;
    DataBase* db;
};

#endif // DIALOGINSCRIPTION_H
