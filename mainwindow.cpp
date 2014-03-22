#include "mainwindow.h"
#include "ui_mainwindow.h"

//The dialog-windows
#include "DialogProgramStart.h"
#include "DialogDeletePerson.h"
#include "DialogDeleteTrack.h"
#include "DialogError.h"

//To get the current year
#include <ctime>


//For the mySql connection
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->currentContest = nullptr;
    this->theCompetitors = nullptr;

    ui->setupUi(this);
    createMenus();  //Creates the menus at the top of the window

    setYear();
    ui->LYear->setText("Current year: "+QString::number(this->year));

    //Only accept numbers in the following Line_edit:
    ui->LE_SSN->setValidator(new QDoubleValidator(0, 9999999999, 0, this) );
    ui->LE_startingNr->setValidator(new QDoubleValidator(0, 9999999, 0, this));
    ui->LE_SSN_S->setValidator(new QDoubleValidator(0, 9999999999, 0, this) );
    ui->LE_phoneNr_S->setValidator(new QDoubleValidator(0, 9999999999, 0, this) );
    ui->LE_Distance->setValidator(new QDoubleValidator(0, 9999999999, 0, this) );
    ui->LE_timeResult->setValidator(new QDoubleValidator(0, 9999999999, 0, this) );

    //setup the combobox.
    ui->CB_gender->addItem("Male");
    ui->CB_gender->addItem("Female");

    startDialog();  //Open dialog for choosing contest
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] this->theCompetitors;
    if(this->currentContest != nullptr)   //If this is true, there was in contest created
    {
        delete this->currentContest;
    }
}
void MainWindow::startDialog()
{
    //Call startup window who ask if I want to go to an old competition, or start a new one
    DialogProgramStart *dialog = nullptr;

    if(this->currentContest == nullptr)
    {
        dialog = new DialogProgramStart();
    }
    else
    {
        dialog = new DialogProgramStart(this->currentContest->getContestName(), this->currentContest->getContestId());
    }
    dialog->exec();

    if(dialog->getContestName() != "")    //If this is true, then there was a new contest created...
    {
        if(this->currentContest != nullptr) //if true, there was another contest created earlier
        {
            delete this->currentContest;
        }
        this->currentContest = new ContestHandler(dialog->getContestName(), this->year);
        ui->LActiveContest->setText("Active contest: " + QString::fromStdString(this->currentContest->getContestName().c_str()));
        ui->LActiveContest_S->setText("Active contest: " + QString::fromStdString(this->currentContest->getContestName().c_str()));
        ui->BnAddCompetitor->setEnabled(true);
        ui->BnAddStaff->setEnabled(true);
        ui->BnAddTrack->setEnabled(true);
        ui->BnAddResult->setEnabled(true);
    }
    else if(dialog->getDatabaseContestName() != "") //If this is true, then we just loaded a contest
    {
        if(this->currentContest != nullptr) //if true, there was another contest created earlier
        {
            delete this->currentContest;
        }

        loadDatabaseToContestHandler(dialog->getDatabaseContestName(), to_string(dialog->getIdOfContest()));

        ui->LActiveContest->setText("Active contest: " + QString::fromStdString(this->currentContest->getContestName().c_str()));
        ui->LActiveContest_S->setText("Active contest: " + QString::fromStdString(this->currentContest->getContestName().c_str()));
        ui->BnAddCompetitor->setEnabled(true);
        ui->BnAddStaff->setEnabled(true);
        ui->BnAddTrack->setEnabled(true);
        ui->BnAddResult->setEnabled(true);
        ui->CB_track->clear();
        for(int i = 0; i < this->currentContest->getNrOfTracks(); i++)
        {
            ui->CB_track->addItem(QString::fromStdString(this->currentContest->trackName(i)));
        }
    }
    else    //No contest currently loaded...
    {
        ui->LActiveContest->setText("Active contest: No contest loaded");
        ui->LActiveContest_S->setText("Active contest: No contest loaded");
        ui->BnAddCompetitor->setEnabled(false);
        ui->BnAddStaff->setEnabled(false);
        ui->BnAddTrack->setEnabled(false);
        ui->BnAddResult->setEnabled(false);
    }
    delete dialog;

    if(this->currentContest != nullptr)
    {
        this->theCompetitors = new PersonNameSsn[this->currentContest->getNrOfPpl()];


    }
}
void MainWindow::saveToDb()
{
    if(this->currentContest != nullptr) //If there is no contest loaded, we should not try to save...
    {
        //INSERT INTO `project_DV1456`.`contestant` (`name`, `mail`, `birthDate`, `gender`, `startingNumber`, `timeResult`, `raceClass`, `CONTESTS_contest_id`)
        //                              VALUES ('Kalle', 'kalle@mail.com', '940512', 'male', '125', '100', 'P20', '2');
        string url = "localhost";
        const string user = "root";
        const string pass = "1";
        const string database = "project_DV1456";

        //Insert or Update the Contests-row
        try
        {
            sql::Driver* driver = get_driver_instance();
            std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
            con->setSchema(database);
            std::unique_ptr<sql::Statement> stmt(con->createStatement());

            if(this->currentContest->getContestId() != -1)  //row already exists, update it
            {
                stmt->execute("UPDATE project_DV1456.contests SET contest_name = \""+this->currentContest->getContestName() +
                              "\", year_of_contest = "+to_string(this->currentContest->getContestYear())+" WHERE contest_id = "
                              +to_string(this->currentContest->getContestId())+";");
            }
            else    //Row doesn't exist, insert new one
            {
                stmt->execute("INSERT INTO `project_DV1456`.`contests` (`contest_name`, `year_of_contest`) VALUES ('"+
                              this->currentContest->getContestName()+"', '"+to_string(this->currentContest->getContestYear())+"');");


                //retrieve the databaseId of the newly inserted contest.
                stmt->execute("SELECT contest_id FROM project_DV1456.contests WHERE contest_name = \""+this->currentContest->getContestName()+
                              "\" AND year_of_contest = "+to_string(this->currentContest->getContestYear())+";");
                std::unique_ptr< sql::ResultSet > res;
                res.reset(stmt->getResultSet());
                res->next();
                this->currentContest->setContestId(res->getInt("contest_id"));
            }
        }
        catch(sql::SQLException &e)
        {
            /*
            MySQL Connector/C++ throws three different exceptions:

            - sql::MethodNotImplementedException (derived from sql::SQLException)
            - sql::InvalidArgumentException (derived from sql::SQLException)
            - sql::SQLException (derived from std::runtime_error)
                    */
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            /* what() (derived from std::runtime_error) fetches error message */
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }

        //Insert or Update the people
        try
        {
            sql::Driver* driver = get_driver_instance();
            std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
            con->setSchema(database);
            std::unique_ptr<sql::Statement> stmt(con->createStatement());

            for(int i = 0; i < this->currentContest->getNrOfPpl(); i++)
            {
                //insert people into the database
                if(this->currentContest->peopleDatabaseId(i) != -1) //if the row does exist in the database, do the update:
                {
                    stmt->execute(this->currentContest->toSqlInsertString(i, "people"));

                }
                else    //Else; do the insert:
                {
                    stmt->execute(this->currentContest->toSqlSaveStringSpecific(i, "people")+to_string(this->currentContest->getContestId())+"');");
                }
            }
//            for(int i = 0; i < this->currentContest->getNrOfTracks(); i++)
//            {
//                //insert tracks into the database
//                stmt->execute(this->currentContest->toSqlSaveStringSpecific(i, "track")+to_string(this->currentContest->getContestId())+"');");

//            }
        }
        catch(sql::SQLException &e)
        {
            /*
            MySQL Connector/C++ throws three different exceptions:

            - sql::MethodNotImplementedException (derived from sql::SQLException)
            - sql::InvalidArgumentException (derived from sql::SQLException)
            - sql::SQLException (derived from std::runtime_error)
                    */
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            /* what() (derived from std::runtime_error) fetches error message */
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }

        //Insert or Update the tracks and the track_records
        try
        {
            sql::Driver* driver = get_driver_instance();
            std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
            con->setSchema(database);
            std::unique_ptr<sql::Statement> stmt(con->createStatement());

            for(int i = 0; i < this->currentContest->getNrOfTracks(); i++)
            {
                if(this->currentContest->trackDatabaseId(i) != -1)  //if the row does exist in the database, do the update:
                {
                    stmt->execute(this->currentContest->toSqlSaveStringSpecific(i, "track"));
                    for(int j = 0; j < 2; j++)
                    {

                        stmt->execute(this->currentContest->toSqlSaveStringSpecific(i, "trackRecord", j));
                    }
                }
                else
                {

                    stmt->execute(this->currentContest->toSqlInsertString(i, "track")+to_string(this->currentContest->getContestId())+"');");

                    //retrieve the databaseId of the newly inserted track.
                    stmt->execute("SELECT track_id FROM project_DV1456.track WHERE track_name = \""+this->currentContest->trackName(i)+
                                  "\" AND contests_contest_id = "+to_string(this->currentContest->getContestId())+";");
                    std::unique_ptr< sql::ResultSet > res;
                    res.reset(stmt->getResultSet());
                    res->next();
                    this->currentContest->setTrackDatabaseId(res->getInt("track_id"), i);

                    for(int j = 0; j < 2; j++)
                    {
                        string test = this->currentContest->toSqlSaveStringSpecific(i, "trackRecord", j)+to_string(this->currentContest->trackDatabaseId(i))+"');";
                        stmt->execute(this->currentContest->toSqlSaveStringSpecific(i, "trackRecord", j)+to_string(this->currentContest->trackDatabaseId(i))+"');");
                    }
                }
            }
        }
        catch(sql::SQLException &e)
        {
            /*
            MySQL Connector/C++ throws three different exceptions:

            - sql::MethodNotImplementedException (derived from sql::SQLException)
            - sql::InvalidArgumentException (derived from sql::SQLException)
            - sql::SQLException (derived from std::runtime_error)
                    */
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            /* what() (derived from std::runtime_error) fetches error message */
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    }
    else
    {
        DialogError dialog("No contest loaded, nothing saved...");
        dialog.exec();
    }
}
void MainWindow::delPersonDialog()
{
    DialogDeletePerson *dialog = new DialogDeletePerson(*this->currentContest);

    dialog->exec();

    if(dialog->getSsn() != "")
    {
        this->currentContest->removePerson(dialog->getSsn());
    }
    delete dialog;
}
void MainWindow::delTrackDialog()
{
    DialogDeleteTrack *dialog = new DialogDeleteTrack(*this->currentContest);

    dialog->exec();

    if(dialog->getTrackName() != "")
    {
        this->currentContest->removeTrack(dialog->getTrackName());
    }
    delete dialog;
}

void MainWindow::loadDatabaseToContestHandler(string databaseContestName, string idOfContest)
{
    //info about the database that we want to read from:
    string url = "localhost";
    const string user = "root";
    const string pass = "1";
    const string database = "project_DV1456";

    //Get contestname and year of the contest
    try
    {
        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        stmt->execute("SELECT * FROM project_DV1456.contests WHERE contest_name = '" + databaseContestName + "';");
        std::unique_ptr< sql::ResultSet > res;

        res.reset(stmt->getResultSet());
        res->next();

        this->currentContest = new ContestHandler(res->getString("contest_name"), res->getInt("year_of_contest"), res->getInt("contest_id"));
    }
    catch(sql::SQLException &e)
    {
        /*
              MySQL Connector/C++ throws three different exceptions:

              - sql::MethodNotImplementedException (derived from sql::SQLException)
              - sql::InvalidArgumentException (derived from sql::SQLException)
              - sql::SQLException (derived from std::runtime_error)
        */
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        /* what() (derived from std::runtime_error) fetches error message */
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }


    //Read the data from contestant and staff tables aswell as track and track_record tables
    try
    {
        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::Statement> stmt2(con->createStatement());

        //Contestants
        stmt->execute("SELECT * FROM project_DV1456.contestant WHERE contests_contest_id=\""+ idOfContest +"\";");
        std::unique_ptr< sql::ResultSet > res;
        std::unique_ptr< sql::ResultSet > res2;

        do  {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                this->currentContest->addPerson(this->year, res->getString("name"), res->getString("mail"), res->getString("ssn"),
                                                res->getString("gender"), res->getInt("startingNumber"), res->getInt("contestant_id"), res->getInt("timeResult"));
            }
        } while(stmt->getMoreResults());

        //Staff
        stmt->execute("SELECT * FROM project_DV1456.staff WHERE contests_contest_id=\""+ idOfContest +"\";");
        do  {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                this->currentContest->addPerson(res->getString("name"), res->getString("mail"), res->getString("ssn"),
                                                res->getString("task"), res->getString("phoneNr"), res->getInt("staff_id"));
            }
        } while(stmt->getMoreResults());

        //Track and records
        stmt->execute("SELECT * FROM project_DV1456.track WHERE contests_contest_id=\""+ idOfContest +"\";");
        do  {
            int nrOfTracks = 0;
            res.reset(stmt->getResultSet());
            while (res->next()) {

                this->currentContest->addTrack(res->getString("track_name"), res->getInt("distance"),
                                               res->getString("location"), res->getString("description"), res->getInt("track_id"));
                //TrackRecords
                stmt2->execute("SELECT * FROM project_DV1456.track_record WHERE track_track_id="+to_string(res->getInt("track_id"))+";");
                do  {
                    res2.reset(stmt2->getResultSet());
                    for(int i = 0; i < 2; i++)
                    {
                        res2->next();
                        this->currentContest->addRecordFromDb(nrOfTracks, res2->getString("recordHolder"), res2->getDouble("time"),
                                                              res2->getString("date"), i, res2->getString("raceClass"), res2->getInt("track_record_id"));
                    }
                } while(stmt2->getMoreResults());
                nrOfTracks++;
            }
        } while(stmt->getMoreResults());
    }
    catch(sql::SQLException &e)
    {
        /*
        MySQL Connector/C++ throws three different exceptions:

        - sql::MethodNotImplementedException (derived from sql::SQLException)
        - sql::InvalidArgumentException (derived from sql::SQLException)
        - sql::SQLException (derived from std::runtime_error)
                */
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        /* what() (derived from std::runtime_error) fetches error message */
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}
void MainWindow::setYear()
{
    //Gets the current year, and saves it in the private variable 'year'
    time_t t = time(0);
    struct tm * now = localtime(&t);
    this->year = now->tm_year + 1900;
}
int MainWindow::getYear() const
{
    return this->year;
}
string MainWindow::deletePerson(string ssn)
{
    this->currentContest->removePerson(ssn);
    return "ok";
}

void MainWindow::createMenus()
{
    QAction *delPersonAct;
    QAction *delTrackAct;


    fileMenu = menuBar()->addMenu("&File");
    editMenu = menuBar()->addMenu("&Edit");


    //File->Create new contest
    changeContestAct = new QAction("&Change active contest", this);
    fileMenu->addAction(changeContestAct);
    connect(changeContestAct, SIGNAL(triggered()), this, SLOT(startDialog()));

    //File->save
    saveAct = new QAction("&Save to database", this);
    fileMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveToDb()));

    //File->Exit
    exitAct = new QAction("&Exit", this);
    fileMenu->addAction(exitAct);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


    //Edit->Delete person
    delPersonAct= new QAction("&Delete person", this);
    editMenu->addAction(delPersonAct);
    connect(delPersonAct, SIGNAL(triggered()), this, SLOT(delPersonDialog()));

    //Edit->Delete track
    delTrackAct = new QAction("&Delete track", this);
    editMenu->addAction(delTrackAct);
    connect(delTrackAct, SIGNAL(triggered()), this, SLOT(delTrackDialog()));
}
void MainWindow::on_BnAddCompetitor_clicked()
{
    //name, mail, ssn, startingNumber
    if(ui->LE_name->text() != "" && ui->LE_mail->text() != "" && ui->LE_SSN->text() != "" && ui->LE_startingNr->text() != "")
    {
        //Add competitor
        this->currentContest->addPerson(this->year, ui->LE_name->text().toStdString(), ui->LE_mail->text().toStdString(),
                                        ui->LE_SSN->text().toStdString(), ui->CB_gender->currentText().toStdString(),
                                        ui->LE_startingNr->text().toInt(), -1);

        //Clear the input fields
        ui->LE_name->clear();
        ui->LE_mail->clear();
        ui->LE_SSN->clear();
        ui->LE_startingNr->clear();
    }
    else
    {
        DialogError dialog("Input missing in one/several of the fields.");
        dialog.exec();
    }
}
void MainWindow::on_BnAddStaff_clicked()
{
    if(ui->LE_name_S->text() != "" && ui->LE_mail_S->text() != "" && ui->LE_task_S->text() != "" && ui->LE_SSN_S->text() != "" && ui->LE_phoneNr_S->text() != "")
    {
        //Add staff
        this->currentContest->addPerson(ui->LE_name_S->text().toStdString(), ui->LE_mail_S->text().toStdString(), ui->LE_SSN_S->text().toStdString(),
                                            ui->LE_task_S->text().toStdString(), ui->LE_phoneNr_S->text().toStdString(), -1);

        //Clear the input fields
        ui->LE_name_S->clear();
        ui->LE_mail_S->clear();
        ui->LE_task_S->clear();
        ui->LE_SSN_S->clear();
        ui->LE_phoneNr_S->clear();
    }
    else
    {
        DialogError dialog("Input missing in one/several of the fields.");
        dialog.exec();
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->setText(QString::fromStdString(this->currentContest->toString("tracks")));
}

void MainWindow::on_BnShowPeople_clicked()
{
    ui->LW_people->clear();
    int nrOfCompetitors = 0;
    delete [] this->theCompetitors;
    theCompetitors = new PersonNameSsn[this->currentContest->getNrOfPpl()];
    for(int i = 0; i < this->currentContest->getNrOfPpl(); i++)
    {
        theCompetitors[nrOfCompetitors] = this->currentContest->contestantInfo(i);
        if(theCompetitors[nrOfCompetitors].getName() != "")
        {
            ui->LW_people->addItem(QString::fromStdString(theCompetitors[nrOfCompetitors++].getName()));
        }
    }
}
void MainWindow::on_BnAddResult_clicked()
{
    //Add the result to the proper person
    this->currentContest->addResult(this->theCompetitors[ui->LW_people->currentRow()].getSsn(), ui->LE_timeResult->text().toDouble(), ui->LW_Tracks->currentRow());
    ui->LE_timeResult->clear();


    //Also check if this is a track-record

}
void MainWindow::on_pushButton_3_clicked()
{
    ui->LB_People_info->setText(QString::fromStdString(this->currentContest->toString()));
}

void MainWindow::on_LW_people_itemClicked()
{
    ui->LW_Tracks->clear();
    ui->LW_Tracks->addItem(QString::fromStdString(this->currentContest->fetchTrackName(0)));
}

void MainWindow::on_BnAddTrack_clicked()
{
    if(ui->LE_TrackName->text() != "" && ui->LE_Distance->text() != "" && ui->LE_Location->text() != "" && ui->PTE_Description->toPlainText().toStdString() != "")
    {
        //Add
        this->currentContest->addTrack(ui->LE_TrackName->text().toStdString(), stoi(ui->LE_Distance->text().toStdString()), ui->LE_Location->text().toStdString(), ui->PTE_Description->toPlainText().toStdString(), -1);

        //Clear the input fields
        ui->LE_TrackName->clear();
        ui->LE_Distance->clear();
        ui->LE_Location->clear();
        ui->PTE_Description->clear();

        ui->CB_track->clear();
        for(int i = 0; i < this->currentContest->getNrOfTracks(); i++)
        {
            ui->CB_track->addItem(QString::fromStdString(this->currentContest->trackName(i)));
        }
    }
    else
    {
        DialogError dialog("Input missing in one/several of the fields.");
        dialog.exec();
    }
}
