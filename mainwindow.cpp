#include "mainwindow.h"
#include "ui_mainwindow.h"


DatabaseEntry::DatabaseEntry(void)
{

}

DatabaseEntry::~DatabaseEntry(void)
{

}

// sqlite callback
int MainWindow::callback(void *db, int argc, char **argv, char **azColName){
    int i;
    QString ColName;
    QString Value;
    DatabaseEntry dbEntry;
    QList<DatabaseEntry> *pDbContents = (QList<DatabaseEntry>*)db;

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
            ui->toolBtnDelete->setVisible(false);
            ui->tabWidget->setTabEnabled(1, false);
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
            ui->toolBtnDelete->setVisible(false);
            ui->tabWidget->setTabEnabled(1, true);
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
            ui->toolBtnDelete->setVisible(false);
            ui->tabWidget->setTabEnabled(1, true);
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
            ui->toolBtnDelete->setVisible(false);
            ui->tabWidget->setTabEnabled(1, true);
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
            ui->toolBtnDelete->setVisible(false);
            ui->tabWidget->setTabEnabled(1, true);
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
            ui->toolBtnDelete->setVisible(true);
            ui->tabWidget->setTabEnabled(1, true);
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

bool MainWindow::UpdateDataFromDb(QString path)
{
    int sqlReturn;
    int rc;
    char *zErrMsg = NULL;

    if ( path == NULL )
    {
        return false;
    }

    // set up handle to the sqlite database
    sqlite3_close(connDB);
    sqlReturn = sqlite3_open(path.toStdString().c_str(), &connDB);
    if ( sqlReturn )
    {
        return false;
    }

    /* Execute SQL statement */
    rc = sqlite3_exec(connDB, "select * from parts", callback, &dbContents, &zErrMsg);
    if( rc != SQLITE_OK ){
        printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(connDB);
        return false;
    }

    // clean the boxes
    int i;
    for ( i = 0; ui->comboBox_type->count(); i++ ) {
        ui->comboBox_type->removeItem(0);
    }
    for ( i = 0; ui->comboBox_add_type->count(); i++ ) {
        ui->comboBox_add_type->removeItem(0);
    }
    for ( i = 0; ui->comboBox_add_package->count(); i++ ) {
        ui->comboBox_add_package->removeItem(0);
    }

    QList<DatabaseEntry>::iterator iter;
    ui->comboBox_type->addItem("");
    ui->comboBox_add_type->addItem(""); // in add tab
    ui->comboBox_add_package->addItem(""); // in add tab
    int typeIterator;
    int packageIterator; // add tab
    bool typeFound = false;
    bool packageFound = false; // add tab

    // for each database entry
    for (iter = dbContents.begin(); iter != dbContents.end(); ++iter) {

        // look through current contents of comboBox
        // type - only insert unique
        typeFound = false; // init
        for ( typeIterator = 0; typeIterator < ui->comboBox_type->count(); typeIterator++ ) {
            if ( (*iter).type == ui->comboBox_type->itemText(typeIterator)) {
                typeFound = true;
            }
        }
        if ( ! typeFound ) {
            ui->comboBox_type->addItem((*iter).type);
            ui->comboBox_add_type->addItem((*iter).type);
        }
        // package - only insert unique
        packageFound = false; // init
        for ( packageIterator = 0; packageIterator < ui->comboBox_add_package->count(); packageIterator++ ) {
            if ( (*iter).package == ui->comboBox_add_package->itemText(packageIterator)) {
                packageFound = true;
            }
        }
        if ( ! packageFound ) {
            ui->comboBox_add_package->addItem((*iter).package);
        }
    }
    // Enable all items in form window
    setVisiblePrimaryBrowseTabItems(TYPE);

    return true;
}

void MainWindow::on_actionSelect_Database_triggered()
{
    do
    {
        pathToSqlDb = QFileDialog::getOpenFileName(this, tr("Select Digikey Database"), "/home",
           tr("Databases (*.sl3)"));
    } while ( !UpdateDataFromDb(pathToSqlDb) );
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
        if ( (*iter).type != type ) {
            continue;
        }

        // only insert unique
        found = false; // init
        for ( valueIterator = 0; valueIterator < ui->comboBox_value->count(); valueIterator++ ) {
            if ( (*iter).value == ui->comboBox_value->itemText(valueIterator) ) {
                found = true;
            }
        }
        if ( ! found ) {
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
        if ( ((*iter).type != ui->comboBox_type->currentText()) || ((*iter).value != value) ) {
            continue;
        }

        // only insert unique
        found = false; // init
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
             ((*iter).package != package) )
        {
            continue;
        }

        // only insert unique
        found = false; // init
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
             ((*iter).tolerance != tolerance) )
        {
            continue;
        }

        // only insert unique
        found = false; // init
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

void MainWindow::on_toolBtnDelete_clicked()
{

}

void MainWindow::on_btn_add_component_clicked()
{
    DatabaseEntry newPart = DatabaseEntry();

    // Get type
    if ( ui->comboBox_add_type->currentText() != "" ) {
        newPart.type = ui->comboBox_add_type->currentText();
    } else if ( ui->edit_new_type->text() == "" ) { // error check
        return;
    } else {
        newPart.type = ui->edit_new_type->text();
    }
    // Get package
    if ( ui->comboBox_add_package->currentText() != "" ) {
        newPart.package = ui->comboBox_add_package->currentText();
    } else if ( ui->edit_new_package->text() == "" ) { // error check
        return;
    } else {
        newPart.package = ui->edit_new_package->text();
    }
    // Get value
    if ( ui->edit_value->text() == "" ) { // error check
        return;
    } else {
        newPart.value = ui->edit_value->text();
    }
    // Get tolerance
    if ( ui->edit_tolerance->text() == "" ) { // error check
        return;
    } else {
        newPart.tolerance = ui->edit_tolerance->text();
    }
    // Get partnum
    if ( ui->edit_partnum->text() == "" ) { // error check
        return;
    } else {
        newPart.partnum = ui->edit_partnum->text();
    }
    // Get comments
    newPart.comments = ui->edit_comments->toPlainText();

    int sqlReturn;
    int rc;
    char *zErrMsg = NULL;

    sqlReturn = sqlite3_open(pathToSqlDb.toStdString().c_str(), &connDB);
    if ( sqlReturn )
    {
        return;
    }

    /* Execute SQL statement */
    QString sqlCmd = "insert into parts (type, value, package, tolerance, partnum, comments) values (\"" +
            newPart.type + "\", \"" + newPart.value + "\", \"" + newPart.package + "\", \"" + newPart.tolerance +
            "\", \"" + newPart.partnum + "\", \"" + newPart.comments + "\");";
    if ( SQLITE_OK != sqlite3_exec (connDB, "BEGIN", NULL, NULL, NULL) ) {
        return;
    }
    rc = sqlite3_exec(connDB, sqlCmd.toStdString().c_str(), NULL, NULL, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(connDB);
        sqlReturn = 1; // force loop repeat
    }
    if ( SQLITE_OK != sqlite3_exec (connDB, "COMMIT", NULL, NULL, NULL) ) {
        return;
    }
    sqlite3_close(connDB);

    UpdateDataFromDb(pathToSqlDb);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if ( index == 1 ) { // Add tab
        ui->edit_new_package->clear();
        ui->edit_new_type->clear();
        ui->edit_comments->clear();
        ui->edit_partnum->clear();
        ui->edit_tolerance->clear();
        ui->edit_value->clear();
        ui->comboBox_add_package->setCurrentIndex(0);
        ui->comboBox_add_type->setCurrentIndex(0);
    }
}

void MainWindow::on_actionImport_BOM_triggered()
{
    pathToEagleBom = QFileDialog::getOpenFileName(this, tr("Select Eagle BOM File"), "/home",
       tr("Databases (*.bom)"));

    // open file and process it

/*  Go from this format.......
    Part Value                           Device                          Package           Description
    C1   0.33uF                          CAP-S0402S                      C0402S            Capacitor
    C2   10uF                            CAP-S0805S                      C0805S            Capacitor
    C3   220nF                           CAP-S0402S                      C0402S            Capacitor
    C4   18pF                            CAP-S0402P                      C0402P            Capacitor
    C5   18pF                            CAP-S0402P                      C0402P            Capacitor

    To this format.............
1,445-8019-1-ND,C1
1,445-5984-1-ND,C2
1,445-7363-1-ND,C3
1,445-5587-1-ND,C4
1,445-5587-1-ND,C5
1,490-4762-1-ND,C6
1,718-1362-1-ND,C7
1,445-5984-1-ND,C8
*/

}
