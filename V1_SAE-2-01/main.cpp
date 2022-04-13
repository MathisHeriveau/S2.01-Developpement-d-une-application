#include "mainWindow.h"
#include "presentation.h"
#include "modele.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // créer le modèle
    Modele *m = new Modele();
    // créer la présentation et lui associer le modèle
    Presentation *p = new Presentation(m);
    // créer la vue
    mainWindow w;
    // associer la vue à la présentation
    p->setVue(&w);
    // initialiser la vue en conformité avec l'état initial du modèle
    p->getVue()->majInterface(m->getEtat());
    // connexion des signaux de la vue avec les slots de la présentation
    w.nvlleConnexion(p);

    // afficher la vue et démarrer la boucle d'attente des messages
    w.show();
    return a.exec();
}
