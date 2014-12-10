#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QHash>

#include "sqlite3.h"

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
    DatabaseEntry() {};
    ~DatabaseEntry() {};

    // data members
    int id;
    QString type;
    QString value;
    QString package;
    QString tolerance;
    QString partnum;
    QString comments;
    QString prefix;
};

class SqlCallbackContainer
{
public:

    // class functions
    SqlCallbackContainer() {};
    ~SqlCallbackContainer() {};

    // data members
    QList<DatabaseEntry> *pDbContents;
    QHash<QString,QString> *pPrefixLookup;
};

class EaglePart
{
public:
    EaglePart() {};
    ~EaglePart() {};

    int identifier;
    QString prefix;
    QString value;
    QString package;
};

class DigikeyPartAndTolerance
{
public:
    DigikeyPartAndTolerance() {};
    DigikeyPartAndTolerance(const DigikeyPartAndTolerance &rh)
    {
        valueList = rh.valueList;
        toleranceList = rh.toleranceList;
        digiKeyPartNumberList = rh.digiKeyPartNumberList;
    };

    ~DigikeyPartAndTolerance() {};

    QList<QString> valueList;
    QList<QString> toleranceList;
    QList<QString> digiKeyPartNumberList;
};

class DigikeyBOMPart
{
public:

    DigikeyBOMPart() {};
    DigikeyBOMPart (const DigikeyBOMPart &rh)
    {
        partName = rh.partName;
        partNumToleranceList = rh.partNumToleranceList;
    };

    ~DigikeyBOMPart() {};

    bool operator == (const DigikeyBOMPart &rh)
    {
        return (rh.partName == partName);
    };

    bool operator != (const DigikeyBOMPart &rh)
    {
        return !(rh.partName == partName);
    };

    QString partName;
     // tolerance and part numbers are paired
    DigikeyPartAndTolerance partNumToleranceList;
};

class uniquePartListEntry
{
public:
    uniquePartListEntry() {};
    uniquePartListEntry(const uniquePartListEntry &rh)
    {
          count = rh.count;
          part = rh.part;
    };
    ~uniquePartListEntry() {};

    int count;
    DigikeyBOMPart part;
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

    void on_toolBtnDelete_clicked();

    void on_btn_add_component_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_actionImport_BOM_triggered();

    void on_comboBox_add_type_activated(const QString &arg1);

    void on_edit_new_type_editingFinished();

    void on_actionCreate_New_Database_triggered();

private:
    void setVisiblePrimaryBrowseTabItems(LabelVisibilty);
    Ui::MainWindow *ui;
    sqlite3 *connDB; // connection object to database
    QString pathToSqlDb;
    QString pathToEagleBom;
    QList<DatabaseEntry> dbContents;
    QHash<QString,QString> PrefixLookup;
    SqlCallbackContainer sqlContainer;
    QList<EaglePart> eaglePartsList;

    // sqlite callback
    static int callback(void *data, int argc, char **argv, char **azColName);

    bool UpdateDataFromDb(QString path);
};

#endif // MAINWINDOW_H
