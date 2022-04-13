#include "modele.h"

Modele::Modele(UnEtat e, QObject *parent)
    : QObject{parent}, _etat(e)
{
}
