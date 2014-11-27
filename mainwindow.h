#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <sqlite3.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionSelect_Database_triggered();

private:
    Ui::MainWindow *ui;
    sqlite3 *connDB; // connection object to database
    QString pathToSqlDb;
};

#endif // MAINWINDOW_H
