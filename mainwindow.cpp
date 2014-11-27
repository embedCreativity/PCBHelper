#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    // Clean up before exit
    sqlite3_close(connDB);

    exit(0);
}

void MainWindow::on_actionSelect_Database_triggered()
{
    int sqlReturn;

    do
    {
        pathToSqlDb = QFileDialog::getOpenFileName(this, tr("Select Digikey Database"), "/home",
           tr("Databases (*.sl3)"));

        if ( pathToSqlDb == NULL )
        {
            break;
        }

        // set up handle to the sqlite database
        sqlite3_close(connDB);
        sqlReturn = sqlite3_open(pathToSqlDb.toStdString().c_str(), &connDB);
        if (sqlReturn) {
            exit(0);
        }
    } while ( sqlReturn );

}
