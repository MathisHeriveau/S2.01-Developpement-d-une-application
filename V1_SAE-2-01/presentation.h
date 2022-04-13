#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"
class mainWindow;
class Presentation : public QObject
{
    Q_OBJECT
public:
    explicit Presentation(Modele *m, QObject *parent = nullptr);
public:
    Modele* getModele();
    mainWindow* getVue();
    void setModele(Modele *m);
    void setVue(mainWindow *v);
signals:
public slots:   // déclenchés par la vue
    
private:
    Modele *_leModele;
    mainWindow *_laVue;
};

#endif // PRESENTATION_H