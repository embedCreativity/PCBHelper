#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <sqlite3.h>
#include <QList>

namespace Ui {
class DatabaseEntry;
class MainWindow;
}
// CREATE TABLE parts ( id integer primary key,
//  type text, value text, package text, tolerance text, partnum text, comments text);
class DatabaseEntry
{
public:

    // class functions
    DatabaseEntry();
    ~DatabaseEntry();

    // data members
    int id;
    QString type;
    QString value;
    QString package;
    QString tolerance;
    QString partnum;
    QString comments;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef enum {
        HELPER = 0,
        TYPE,
        VALUE,
        PACKAGE,
        TOLERANCE,
        PARTNUM
    } LabelVisibilty;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionSelect_Database_triggered();

    void on_comboBox_type_currentIndexChanged(const QString &arg1);

    void on_comboBox_value_currentIndexChanged(const QString &arg1);

    void on_comboBox_package_currentIndexChanged(const QString &arg1);

    void on_comboBox_tolerance_currentIndexChanged(const QString &arg1);

private:
    void setVisiblePrimaryBrowseTabItems(LabelVisibilty);
    Ui::MainWindow *ui;
    sqlite3 *connDB; // connection object to database
    QString pathToSqlDb;
    QList<DatabaseEntry> dbContents;

    // sqlite callback
    static int callback(void *data, int argc, char **argv, char **azColName);
};

#endif // MAINWINDOW_H
