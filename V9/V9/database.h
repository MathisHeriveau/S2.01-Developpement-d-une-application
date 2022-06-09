#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QVariantList>

#define DATABASE_NAME "BD_NodenitBd1_Lakartxela" // nom de la base de données
#define CONNECT_TYPE "QODBC" // type de connexion


class DataBase
{
public:
    DataBase();
    /**
     * @brief Fonction permettant de se connecter à la base de données
     * 
     * @return true Si la connexion a réussi
     * @return false si la connexion a échoué
     */
    bool openDataBase();

    /**
     * @brief Fonction permettant de se deconnecter de la base de données
     * 
     */
    void clseDataBase();

    /**
     * @brief Fonction permettant de initialiser la base de données
     * 
     * @return true 
     * @return false 
     */
    bool restorDataBase();

    /**
     * @brief Fonction permettant d'inserer un nouveau joueur dans la base de données
     * 
     * @return true si l'insertion a réussi
     * @return false si l'insertion a échoué
     */
    bool insertJoueur();

    /**
     * @brief Fonction permettant d'inserer un nouveau score de jeu dans la base de données
     * 
     * @param idJ id du joueur
     * @param nomJ nom du joueur
     * @param scoreJ score du joueur
     * @param scoreM score de la machine
     * @return true si l'insertion a réussi
     * @return false si l'insertion a échoué
     */
    bool insertScore(int idJ,QString nomJ,int scoreJ, int scoreM);
private:

    QSqlDatabase mydb; // variable de connexion à la base de données
};

#endif // DATABASE_H
