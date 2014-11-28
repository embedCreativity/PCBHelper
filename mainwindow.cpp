#include "mainwindow.h"
#include "ui_mainwindow.h"


DatabaseEntry::DatabaseEntry(void)
{

}

DatabaseEntry::~DatabaseEntry(void)
{

}

/*
 * class DatabaseEntry
{
public:

    // class functions

    // data members
    int id;
    QString type;
    QString value;
    QString package;
    QString tolerance;
    QString partnum;
    QString comments;
};*/
// sqlite callback
int MainWindow::callback(void *db, int argc, char **argv, char **azColName){
    int i;
    QString ColName;
    QString Value;
    DatabaseEntry dbEntry;
    QList<DatabaseEntry> *pDbContents = (QList<DatabaseEntry>*)db;
    // db = QVector dbContents
    //fprintf(stderr, "%s: ", (const char*)data);

    for(i=0; i<argc; i++){
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        ColName = azColName[i];
        Value = argv[i] ? argv[i] : "NULL";

        if ( ColName == "id" )
        {
            dbEntry.id = Value.toInt();
        }
        else if ( ColName == "type" )
        {
            dbEntry.type = Value;
        }
        else if ( ColName == "value" )
        {
            dbEntry.value = Value;
        }
        else if ( ColName == "package" )
        {
            dbEntry.package = Value;
        }
        else if ( ColName == "tolerance" )
        {
            dbEntry.tolerance = Value;
        }
        else if ( ColName == "partnum" )
        {
            dbEntry.partnum = Value;
        }
        else if ( ColName == "comments" )
        {
            dbEntry.comments = Value;
        }
    } // end for

    pDbContents->push_back(dbEntry);
    return 0;
}

void MainWindow::setVisiblePrimaryBrowseTabItems(LabelVisibilty visibility)
{
    // primary items
    switch ( visibility ) {
        case(HELPER):
            ui->lbl_helper->setVisible(true);
            ui->lbl_comments->setVisible(false);
            ui->lbl_package->setVisible(false);
            ui->lbl_partnum->setVisible(false);
            ui->lbl_select->setVisible(false);
            ui->lbl_tolerance->setVisible(false);
            ui->lbl_type->setVisible(false);
            ui->lbl_value->setVisible(false);
            ui->comboBox_package->setVisible(false);
            ui->comboBox_partnum->setVisible(false);
            ui->comboBox_tolerance->setVisible(false);
            ui->comboBox_type->setVisible(false);
            ui->comboBox_value->setVisible(false);
            ui->txtComments->setVisible(false);
            break;
        case(TYPE):
            ui->lbl_helper->setVisible(false);
            ui->lbl_comments->setVisible(false);
            ui->lbl_package->setVisible(false);
            ui->lbl_partnum->setVisible(false);
            ui->lbl_select->setVisible(false);
            ui->lbl_tolerance->setVisible(false);
            ui->lbl_type->setVisible(true);
            ui->lbl_value->setVisible(false);
            ui->comboBox_package->setVisible(false);
            ui->comboBox_partnum->setVisible(false);
            ui->comboBox_tolerance->setVisible(false);
            ui->comboBox_type->setVisible(true);
            ui->comboBox_value->setVisible(false);
            ui->txtComments->setVisible(false);
            break;
        case(VALUE):
            ui->lbl_helper->setVisible(false);
            ui->lbl_comments->setVisible(false);
            ui->lbl_package->setVisible(false);
            ui->lbl_partnum->setVisible(false);
            ui->lbl_select->setVisible(false);
            ui->lbl_tolerance->setVisible(false);
            ui->lbl_type->setVisible(true);
            ui->lbl_value->setVisible(true);
            ui->comboBox_package->setVisible(false);
            ui->comboBox_partnum->setVisible(false);
            ui->comboBox_tolerance->setVisible(false);
            ui->comboBox_type->setVisible(true);
            ui->comboBox_value->setVisible(true);
            ui->txtComments->setVisible(false);
            break;
        case(PACKAGE):
            ui->lbl_helper->setVisible(false);
            ui->lbl_comments->setVisible(false);
            ui->lbl_package->setVisible(true);
            ui->lbl_partnum->setVisible(false);
            ui->lbl_select->setVisible(false);
            ui->lbl_tolerance->setVisible(false);
            ui->lbl_type->setVisible(true);
            ui->lbl_value->setVisible(true);
            ui->comboBox_package->setVisible(true);
            ui->comboBox_partnum->setVisible(false);
            ui->comboBox_tolerance->setVisible(false);
            ui->comboBox_type->setVisible(true);
            ui->comboBox_value->setVisible(true);
            ui->txtComments->setVisible(false);
            break;
        case(TOLERANCE):
            ui->lbl_helper->setVisible(false);
            ui->lbl_comments->setVisible(false);
            ui->lbl_package->setVisible(true);
            ui->lbl_partnum->setVisible(false);
            ui->lbl_select->setVisible(false);
            ui->lbl_tolerance->setVisible(true);
            ui->lbl_type->setVisible(true);
            ui->lbl_value->setVisible(true);
            ui->comboBox_package->setVisible(true);
            ui->comboBox_partnum->setVisible(false);
            ui->comboBox_tolerance->setVisible(true);
            ui->comboBox_type->setVisible(true);
            ui->comboBox_value->setVisible(true);
            ui->txtComments->setVisible(false);
            break;
        case(PARTNUM):
            ui->lbl_helper->setVisible(false);
            ui->lbl_comments->setVisible(true);
            ui->lbl_package->setVisible(true);
            ui->lbl_partnum->setVisible(true);
            ui->lbl_select->setVisible(false);
            ui->lbl_tolerance->setVisible(true);
            ui->lbl_type->setVisible(true);
            ui->lbl_value->setVisible(true);
            ui->comboBox_package->setVisible(true);
            ui->comboBox_partnum->setVisible(true);
            ui->comboBox_tolerance->setVisible(true);
            ui->comboBox_type->setVisible(true);
            ui->comboBox_value->setVisible(true);
            ui->txtComments->setVisible(true);
            break;
    } // end switch
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setVisiblePrimaryBrowseTabItems(HELPER);
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
    int rc;
    char *zErrMsg = NULL;

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
        if ( sqlReturn )
        {
            continue;
        }

        /* Execute SQL statement */
        rc = sqlite3_exec(connDB, "select * from parts", callback, &dbContents, &zErrMsg);
        if( rc != SQLITE_OK ){
            printf("SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(connDB);
            sqlReturn = 1; // force loop repeat
        }else{
            printf("Operation done successfully\n");
            break;
        }
    } while ( sqlReturn );

    QList<DatabaseEntry>::iterator i;
    for (i = dbContents.begin(); i != dbContents.end(); ++i) {
        ui->comboBox_type->addItem((*i).type);
    }
    // Enable all items in form window
    setVisiblePrimaryBrowseTabItems(TYPE);
}


/******************** EOF **************************/

