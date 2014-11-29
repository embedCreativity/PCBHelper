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
            ui->lbl_select->setVisible(true);
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
            ui->lbl_select->setVisible(true);
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
            ui->lbl_select->setVisible(true);
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
            ui->lbl_select->setVisible(true);
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
    ui->comboBox_type->addItem("");
    int typeIterator;
    bool found = false;
    for (i = dbContents.begin(); i != dbContents.end(); ++i) {
        // only insert unique
        for ( typeIterator = 0; typeIterator < ui->comboBox_type->count(); typeIterator++ ) {
            if ( (*i).type == ui->comboBox_type->itemText(typeIterator)) {
                found = true;
            }
        }
        if ( ! found ) {
            ui->comboBox_type->addItem((*i).type);
        }
    }
    // Enable all items in form window
    setVisiblePrimaryBrowseTabItems(TYPE);
}

void MainWindow::on_comboBox_type_currentIndexChanged(const QString &type)
{
    int i;

    // clean value box
    for ( i = 0; ui->comboBox_value->count(); i++ ) {
        ui->comboBox_value->removeItem(0);
    }

    // populate value box
    ui->comboBox_value->addItem("");
    QList<DatabaseEntry>::iterator iter;
    int valueIterator;
    bool found = false;
    for (iter = dbContents.begin(); iter != dbContents.end(); iter++) {
        if ( (*iter).type != ui->comboBox_type->currentText() ) {
            fprintf(stderr, "%s - type: %s != box: %s\n", __FUNCTION__,
                    (*iter).type.toStdString().c_str(),
                    ui->comboBox_type->currentText().toStdString().c_str());
            continue;
        }

        fprintf(stderr, "%s - type: %s == box: %s\n", __FUNCTION__,
                (*iter).type.toStdString().c_str(),
                ui->comboBox_type->currentText().toStdString().c_str());

        // only insert unique
        for ( valueIterator = 0; valueIterator < ui->comboBox_value->count(); valueIterator++ ) {
            if ( (*iter).value == ui->comboBox_value->itemText(valueIterator) ) {
                found = true;
            }
        }
        if ( ! found ) {
            //
            ui->comboBox_value->addItem((*iter).value);
        }
    }

    // Enable all items in form window
    setVisiblePrimaryBrowseTabItems(VALUE);
}

void MainWindow::on_comboBox_value_currentIndexChanged(const QString &value)
{
    int i;

    // clean package box
    for ( i = 0; ui->comboBox_package->count(); i++ ) {
        ui->comboBox_package->removeItem(0);
    }

    // populate package box
    ui->comboBox_package->addItem("");
    QList<DatabaseEntry>::iterator iter;
    int packageIterator;
    bool found = false;
    for (iter = dbContents.begin(); iter != dbContents.end(); iter++) {
        if ( ((*iter).type != ui->comboBox_type->currentText()) || ((*iter).value != ui->comboBox_value->currentText()) ) {
            continue;
        }

        // only insert unique
        for ( packageIterator = 0; packageIterator < ui->comboBox_package->count(); packageIterator++ ) {
            if ( (*iter).package == ui->comboBox_package->itemText(packageIterator)) {
                found = true;
            }
        }
        if ( ! found ) {
            ui->comboBox_package->addItem((*iter).package);
        }
    }

    // Enable all items in form window
    setVisiblePrimaryBrowseTabItems(PACKAGE);
}

void MainWindow::on_comboBox_package_currentIndexChanged(const QString &package)
{
    int i;

    // clean tolerance box
    for ( i = 0; ui->comboBox_tolerance->count(); i++ ) {
        ui->comboBox_tolerance->removeItem(0);
    }

    // populate tolerance box
    ui->comboBox_tolerance->addItem("");
    QList<DatabaseEntry>::iterator iter;
    int toleranceIterator;
    bool found = false;
    for (iter = dbContents.begin(); iter != dbContents.end(); iter++) {
        if ( ((*iter).type != ui->comboBox_type->currentText()) ||
             ((*iter).value != ui->comboBox_value->currentText()) ||
             ((*iter).package != ui->comboBox_package->currentText()) )
        {
            continue;
        }

        // only insert unique
        for ( toleranceIterator = 0; toleranceIterator < ui->comboBox_tolerance->count(); toleranceIterator++ ) {
            if ( (*iter).tolerance == ui->comboBox_tolerance->itemText(toleranceIterator)) {
                found = true;
            }
        }
        if ( ! found ) {
            ui->comboBox_tolerance->addItem((*iter).tolerance);
        }
    }

    // Enable all items in form window
    setVisiblePrimaryBrowseTabItems(TOLERANCE);
}

void MainWindow::on_comboBox_tolerance_currentIndexChanged(const QString &tolerance)
{
    int i;

    // clean partnum box
    for ( i = 0; ui->comboBox_partnum->count(); i++ ) {
        ui->comboBox_partnum->removeItem(0);
    }

    // populate partnum box
    QList<DatabaseEntry>::iterator iter;
    int partnumIterator;
    bool found = false;
    for (iter = dbContents.begin(); iter != dbContents.end(); iter++) {
        if ( ((*iter).type != ui->comboBox_type->currentText()) ||
             ((*iter).value != ui->comboBox_value->currentText()) ||
             ((*iter).package != ui->comboBox_package->currentText()) ||
             ((*iter).tolerance != ui->comboBox_tolerance->currentText()) )
        {
            continue;
        }

        // only insert unique
        for ( partnumIterator = 0; partnumIterator < ui->comboBox_partnum->count(); partnumIterator++ ) {
            if ( (*iter).partnum == ui->comboBox_partnum->itemText(partnumIterator)) {
                found = true;
            }
        }
        if ( ! found ) {
            ui->comboBox_partnum->addItem((*iter).partnum);
        }
        ui->txtComments->setText((*iter).comments);
    }

    // Enable all items in form window
    setVisiblePrimaryBrowseTabItems(PARTNUM);
}
