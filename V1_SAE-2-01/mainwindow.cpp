#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->iconFeuille, SIGNAL(clicked()), this, SLOT(boutonFeuille()));
    connect(ui->iconCiseau, SIGNAL(clicked()), this, SLOT(boutonCiseau()));
    connect(ui->iconPierre, SIGNAL(clicked()), this, SLOT(boutonPierre()));
    connect(ui->NvllPartie, SIGNAL(clicked()), this, SLOT(boutonNvllPartie()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::boutonPierre(){
    qDebug() << "yeh";
}
void MainWindow::boutonFeuille(){
    qDebug() << "yea";
}
void MainWindow::boutonCiseau(){
    qDebug() << "yer";
}
void MainWindow::boutonNvllPartie(){
    qDebug() << "yes";
}
