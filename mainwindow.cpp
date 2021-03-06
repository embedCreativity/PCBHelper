#include "mainwindow.h"
#include "ui_mainwindow.h"

// sqlite callback
int MainWindow::callback(void *container, int argc, char **argv, char **azColName){
    int i;
    QString ColName;
    QString Value;
    DatabaseEntry dbEntry;
    QList<DatabaseEntry> *pDbContents = ((SqlCallbackContainer *)container)->pDbContents;
    QHash<QString,QString> *pPrefixLookup = ((SqlCallbackContainer *)container)->pPrefixLookup;

    if ( argc == 0 )
    {
        printf("in callback. argc = %d. Bailing\n", argc);
    }

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
        else if ( ColName == "prefix" )
        {
            dbEntry.prefix= Value;
        }
    } // end for

    // Check for uniqueness of eagle prefix per type
    if (  pPrefixLookup->contains(dbEntry.type) )
    {
        if (dbEntry.prefix != pPrefixLookup->value(dbEntry.type))
        {
            // oh shit!  What to do?
            printf("oh shit. %s type with prefix %s does not match expected prefix of %s\n", dbEntry.type.toStdString().c_str(),
                   dbEntry.prefix.toStdString().c_str(), pPrefixLookup->value(dbEntry.type).toStdString().c_str());
        }
    }
    else // dictionary not populated with value for given type yet. Let's add it
    {
        (*pPrefixLookup)[dbEntry.type] = dbEntry.prefix;
    }

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
            ui->lbl_disp_eagle_prefix->setVisible(false);
            ui->lbl_eagle_prefix->setVisible(false);
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
            ui->lbl_disp_eagle_prefix->setVisible(false);
            ui->lbl_eagle_prefix->setVisible(false);
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
            ui->lbl_disp_eagle_prefix->setVisible(false);
            ui->lbl_eagle_prefix->setVisible(false);
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
            ui->lbl_disp_eagle_prefix->setVisible(false);
            ui->lbl_eagle_prefix->setVisible(false);
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
            ui->lbl_disp_eagle_prefix->setVisible(false);
            ui->lbl_eagle_prefix->setVisible(false);
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
            ui->lbl_disp_eagle_prefix->setVisible(true);
            ui->lbl_eagle_prefix->setVisible(true);
            break;
    } // end switch
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setVisiblePrimaryBrowseTabItems(HELPER);
    ui->actionImport_BOM->setDisabled(true);

    sqlContainer.pDbContents = &dbContents;
    sqlContainer.pPrefixLookup = &PrefixLookup;
    connDB = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    // Clean up before exit
    if ( NULL != connDB )
    {
        sqlite3_close(connDB);
        connDB = NULL;
    }

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
    if ( NULL != connDB )
    {
        sqlite3_close(connDB);
        connDB = NULL;
    }
    sqlReturn = sqlite3_open(path.toStdString().c_str(), &connDB);
    if ( sqlReturn )
    {
        return false;
    }

    /* Execute SQL statement */
    rc = sqlite3_exec(connDB, "select * from parts", callback, &sqlContainer, &zErrMsg);
    if( rc != SQLITE_OK ){
        printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        if ( NULL != connDB )
        {
            sqlite3_close(connDB);
            connDB = NULL;
        }
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
        if (pathToSqlDb == NULL) // user hit "Cancel" button
        {
            return;
        }
    } while ( !UpdateDataFromDb(pathToSqlDb) );
    ui->actionSelect_Database->setDisabled(true);
    ui->actionImport_BOM->setEnabled(true);
    ui->actionSelect_Database->setDisabled(true);
    ui->actionCreate_New_Database->setDisabled(true);
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
        ui->lbl_eagle_prefix->setText((*iter).prefix);
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

    // Get prefix
    if ( (ui->edit_prefix->text() == "") && (!PrefixLookup.contains(newPart.type)) ) { // error check
        return;
    } else if ( PrefixLookup.contains(newPart.type) ) {  // get prefix from dictionary
        newPart.prefix = PrefixLookup.value(newPart.type);
    } else {                                            // get prefix from line edit box
        newPart.prefix = ui->edit_prefix->text();
    }

    int sqlReturn;
    int rc;
    char *zErrMsg = NULL;

    sqlReturn = sqlite3_open(pathToSqlDb.toStdString().c_str(), &connDB);
    if ( sqlReturn )
    {
        return;
    }

    /* Execute SQL statement */
    QString sqlCmd = "insert into parts (type, value, package, tolerance, partnum, comments, prefix) values (\"" +
            newPart.type + "\", \"" + newPart.value + "\", \"" + newPart.package + "\", \"" + newPart.tolerance +
            "\", \"" + newPart.partnum + "\", \"" + newPart.comments + "\", \"" + newPart.prefix + "\");";
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

    dbContents.clear(); // blow away as it will be repopulated in a sec
    UpdateDataFromDb(pathToSqlDb);

    ui->edit_new_package->clear();
    ui->edit_new_type->clear();
    ui->edit_prefix->clear();
    ui->edit_value->clear();
    ui->edit_tolerance->clear();
    ui->edit_partnum->clear();
    ui->edit_comments->clear();
    ui->comboBox_add_package->setCurrentIndex(0);
    ui->comboBox_add_package->setCurrentIndex(0);
    ui->edit_prefix->setVisible(false);
    ui->lbl_disp_new_eagle_prefix->setVisible(false);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if ( index == 1 ) { // Add tab
        ui->edit_new_package->clear();
        ui->edit_new_type->clear();
        ui->edit_comments->clear();
        ui->edit_prefix->clear();
        ui->edit_partnum->clear();
        ui->edit_tolerance->clear();
        ui->edit_value->clear();
        ui->lbl_disp_new_eagle_prefix->setVisible(false);
        ui->edit_prefix->setVisible(false);
        ui->comboBox_add_package->setCurrentIndex(0);
        ui->comboBox_add_type->setCurrentIndex(0);
    }
}

void MainWindow::on_actionImport_BOM_triggered()
{
    pathToEagleBom = QFileDialog::getOpenFileName(this, tr("Select Eagle BOM File"), "/home",
       tr("Eagle BOM (*.bom)"));

    // open file and process it
    QFile file(pathToEagleBom);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    char part[64];
    char value[64];
    char device[64]; // we won't use this
    char package[64];
    char strPartNumber[64];
    int partNumber;
    char prefix[64];
    QString qvalue;
    QString qpackage;
    int i;
    int j;
    int k;

    while (!file.atEnd())
    {
        QString line = file.readLine();
        char *cLine = strdup(line.toStdString().c_str()); // copy QString to c string
        // for each line in BOM...

        if ( 4 != sscanf(cLine, "%s %s %s %s", part, value, device, package)) { // error check
            printf("error - sscanf\n");
            free(cLine);
            continue;
        }

        free(cLine);

        // fill strings with NULL
        memset(strPartNumber, 0, 64);
        memset(prefix, 0, 64);

        for (i = 0, j = 0, k = 0; part[i] != '\0'; i++ )
        {
            if ( (('a' <= part[i]) && (part[i] <= 'z')) || (('A' <= part[i]) && (part[i] <= 'Z')) || part[i] == '\0' ) // pull part type out of name
            {
                prefix[j] = part[i];
                j += 1;
            } else if ( ('1' <= part[i]) || (part[i] <= '9') ) // pull part number out of name
            {
                strPartNumber[k] = part[i];
                k += 1;
            }
        }

        if ( 1 != sscanf(strPartNumber, "%d", &partNumber) )
        {
            continue;
        }

        // stick the part into our list
        EaglePart eaglePart;
        eaglePart.identifier = partNumber;
        eaglePart.prefix = prefix;
        eaglePart.value = value;
        eaglePart.package = package;
        eaglePartsList.append(eaglePart);
    } // end while

    QList<DatabaseEntry>::iterator dbIterator;
    QList<EaglePart>::iterator eagleIterator;
    bool reject;
    QList<uniquePartListEntry> partList;
    QList<uniquePartListEntry>::iterator partListIter;
    QString fileOutput = "";
    char buf[16] = "";

    for (eagleIterator = eaglePartsList.begin(); eagleIterator != eaglePartsList.end(); ++eagleIterator ) // for each part we found
    {
        DigikeyBOMPart digiBomPart; // one for each part we found
        char partName[64]; // prep a handy name
        snprintf(partName, 64, "%s%d", eagleIterator->prefix.toStdString().c_str(), eagleIterator->identifier);
        reject = true;  // init

        //printf("looking up part for %s\n", partName);

        for ( dbIterator = dbContents.begin(); dbIterator != dbContents.end(); ++dbIterator ) // look in our database for a match
        {
            //printf(" is %s/%s a match?\n", dbIterator->type.toStdString().c_str(), dbIterator->value.toStdString().c_str());

            if ( eagleIterator->prefix.toUpper() == dbIterator->prefix.toUpper() ) // must be exact match
            {
                //printf("  prefix %s matches %s\n", eagleIterator->prefix.toStdString().c_str(),
                //       dbIterator->prefix.toStdString().c_str());

                if ( eagleIterator->package.toUpper().contains(dbIterator->package.toUpper()) ) // match contains...
                {
                    //printf("   package %s matches %s\n", eagleIterator->package.toStdString().c_str(),
                    //       dbIterator->package.toStdString().c_str());

                    if ( eagleIterator->value.toUpper() == dbIterator->value.toUpper() ) // must be exact match
                    {
                        //printf("    value %s matches %s\n", eagleIterator->value.toStdString().c_str(),
                        //       dbIterator->value.toStdString().c_str());

                        reject = false;
                        digiBomPart.partName = partName;  // if multiple parts, this will get reset but maintain correctness
                        digiBomPart.partNumToleranceList.valueList.append(dbIterator->value); // add value to list
                        digiBomPart.partNumToleranceList.digiKeyPartNumberList.append(dbIterator->partnum); // add new partnumber to list
                        digiBomPart.partNumToleranceList.toleranceList.append(dbIterator->tolerance); // add corresponding tolerance description
                    }
                }
            }
        } // done looking though database for matching part description for this part

        if ( reject ) // No match in database. Print string indicating we need to manually go get a part number
        {
            // For parts that do not match, prep the line for the digikey file, but replace the digikey part number with the value found earlier (e.g., XTAL3-CSM-12)
            snprintf(buf, 16, "%d", eagleIterator->identifier);
            fileOutput = fileOutput + "1, ," + eagleIterator->prefix + buf + " | value: " + eagleIterator->value +
                   ", package: " + eagleIterator->package + " | Please find a digikey P\\N for this part!\n";
        }
        else // part info found from our database for this part. Put in our aggregate list.
        {
            uniquePartListEntry uniquePart;
            if ( partList.isEmpty()) { // first part from Eagle BOM
                //printf("     appending part to empty part list\n");
                uniquePart.count = 1;
                uniquePart.part = digiBomPart;
                partList.append(uniquePart);
            }
            else // not first part from Eagle BOM
            {
                bool uniqueFound = true;
                // not empty, go search for matching part info
                for ( partListIter = partList.begin(); partListIter != partList.end(); ++partListIter )
                {
                    if ( digiBomPart.partNumToleranceList.digiKeyPartNumberList == partListIter->part.partNumToleranceList.digiKeyPartNumberList )
                    {
                        partListIter->count += 1; // increment count of parts
                        partListIter->part.partName += "." + digiBomPart.partName; // append to aggregate part name
                        uniqueFound = false;
                        continue;
                    }
                }
                if ( uniqueFound ) { // matching part not found, add to list
                    uniquePart.count = 1;
                    uniquePart.part = digiBomPart;
                    partList.append(uniquePart);
                }
            }
        } // done placing part info into our aggregate list
    } // end for each eagle part in bom...
    file.close();

    fileOutput = fileOutput + "\n\n"; // separate good data from warnings above

    // print out summary of parts found
    for ( partListIter = partList.begin(); partListIter != partList.end(); ++partListIter )
    {
        if ( partListIter->part.partNumToleranceList.digiKeyPartNumberList.length() != 1 ) // multiple part warning
        {
            snprintf(buf, 16, "%d", partListIter->part.partNumToleranceList.digiKeyPartNumberList.length());
            fileOutput = fileOutput + "WARNING: Multiple parts [" + buf +
                   "] found for part(s): " + partListIter->part.partName + "\n";
            // TODO: take code from below and move up here
            QList<QString>::iterator partNumIter;
            QList<QString>::iterator toleranceIter;
            QList<QString>::iterator valueIter;
            for ( partNumIter = partListIter->part.partNumToleranceList.digiKeyPartNumberList.begin(),
                  toleranceIter = partListIter->part.partNumToleranceList.toleranceList.begin(),
                  valueIter = partListIter->part.partNumToleranceList.valueList.begin();
                  partNumIter != partListIter->part.partNumToleranceList.digiKeyPartNumberList.end() &&
                  toleranceIter != partListIter->part.partNumToleranceList.toleranceList.end() &&
                  valueIter != partListIter->part.partNumToleranceList.valueList.end();
                  ++partNumIter, ++toleranceIter, ++valueIter )
            {
                fileOutput = fileOutput + "\t\tValue: " + valueIter->toStdString().c_str() + ", Tolerance: " + toleranceIter->toStdString().c_str() +
                        ", Digikey P\\N: " + partNumIter->toStdString().c_str() + "\n";
            } // end for

        } // end if
        else // unique part found
        {
            snprintf(buf, 16, "%d", partListIter->count);
            fileOutput = fileOutput + buf + "," + partListIter->part.partNumToleranceList.digiKeyPartNumberList.first() +
                    "," + partListIter->part.partName + "\n";
        }

    } //end for

    //printf("%s", fileOutput.toStdString().c_str());

    QFileInfo getDir(pathToEagleBom);

    QString outputFileName = QFileDialog::getSaveFileName(this, tr("Output Digikey File"),
                            getDir.absolutePath(), tr("Digikey Parts File (*.digi)"));
    if (!outputFileName.endsWith(".digi"))
    {
        outputFileName = outputFileName + ".digi";
    }

    // Write data out to file
    QFile outputFile(outputFileName);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outputFile);
    out << fileOutput;
    outputFile.close();

    printf("Done processing file...\n");
}

void MainWindow::on_edit_new_type_editingFinished()
{
    ui->lbl_disp_new_eagle_prefix->setVisible(true);
    ui->edit_prefix->setVisible(true);
    ui->comboBox_add_type->setCurrentIndex(0);

}

void MainWindow::on_comboBox_add_type_activated(const QString &foo)
{
    (void)foo; // silence warning about unused param
    ui->edit_prefix->clear();
    ui->lbl_disp_new_eagle_prefix->setVisible(false);
    ui->edit_prefix->setVisible(false);
    ui->edit_new_type->clear();
}


void MainWindow::on_actionCreate_New_Database_triggered()
{
    QString newDbName = QFileDialog::getSaveFileName(this, tr("New Database"),
                            "/home", tr("Sqlite3 database (*.sl3)"));
    if (!newDbName.endsWith(".sl3"))
    {
        newDbName = newDbName + ".sl3";
    }

    int sqlReturn;
    int rc;
    char *zErrMsg = NULL;
    sqlite3 *newDbConn;
    QString createCmd = "CREATE TABLE parts (id integer primary key, type text, value text, package text, tolerance text, partnum text, comments text, prefix text);";

    sqlReturn = sqlite3_open_v2(newDbName.toStdString().c_str(), &newDbConn, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    if ( sqlReturn )
    {
        printf("sqlite3_open returned failure\n");
        return;
    }

    /* Execute SQL statement */
    rc = sqlite3_exec(newDbConn, createCmd.toStdString().c_str(), NULL, &sqlContainer, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        printf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(newDbConn);
}
