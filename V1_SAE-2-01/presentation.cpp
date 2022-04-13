#include "presentation.h"
#include "mainWindow.h"
#include <QDebug>

Presentation::Presentation(Modele *m, QObject *parent)
    : QObject{parent}, _leModele(m)
{
    _leModele->eteindre();
}

Modele *Presentation::getModele()
{
    return _leModele;
}

mainWindow *Presentation::getVue()
{
    return _laVue;
}

void Presentation::setModele(Modele *m)
{
    _leModele = m;
}

void Presentation::setVue(mainWindow *v)
{
    _laVue = v;
}