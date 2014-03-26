#include <ctime>
#include "DialogProgramStart.h"
#include "ui_DialogProgramStart.h"
#include "DialogNewContest.h"
#include "DialogError.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>



DialogProgramStart::DialogProgramStart(string prevContestName, int idOfContest, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProgramStart)
{
    ui->setupUi(this);
    this->contestName = prevContestName;
    this->idOfContest = idOfContest;

    this->capContestNameYear = 5;
    this->nrOfContestNameYear = 0;
    this->theContests = new ContestNameYear*[this->capContestNameYear];
    for(int i = 0; i < this->capContestNameYear; i++)
    {
        this->theContests[i] = nullptr;
    }

    loadDatabase();
}

DialogProgramStart::~DialogProgramStart()
{
    delete ui;

    for(int i = 0; i < this->nrOfContestNameYear; i++)
    {
        delete this->theContests[i];
    }
    delete [] this->theContests;
}
string DialogProgramStart::getContestName() const
{
    return this->contestName;
}
int DialogProgramStart::getIdOfContest() const
{
    return this->idOfContest;
}
void DialogProgramStart::loadDatabase()
{
    string url = "localhost";
    const string user = "root";
    const string pass = "1";
    const string database = "project_DV1456";
    int nrOfContests = 0;

    try
    {
        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        stmt->execute("SELECT * FROM project_DV1456.contests;");
        std::unique_ptr< sql::ResultSet > res;
        do
        {
            res.reset(stmt->getResultSet());
            while (res->next())
            {
                this->theContests[nrOfContests] = new ContestNameYear(res->getString("contest_name"), res->getInt("year_of_contest"));
                ui->LW_openList->addItem(QString::fromStdString(this->theContests[nrOfContests]->getContestName()));
                nrOfContests++;
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
int DialogProgramStart::getIdFromDatabase(int row) const
{
    int theId = 0;

    string url = "localhost";
    const string user = "root";
    const string pass = "1";
    const string database = "project_DV1456";

    try
    {
        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        stmt->execute("SELECT contest_id FROM project_DV1456.contests WHERE contest_name='"+this->theContests[row]->getContestName()+
                      "' AND year_of_contest='"+to_string(this->theContests[row]->getContestYear())+"';");
        std::unique_ptr< sql::ResultSet > res;
        res.reset(stmt->getResultSet());
        res->next();

        theId = res->getInt("contest_id");
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
    return theId;
}
void DialogProgramStart::deleteContestFromDb()
{
    string url = "localhost";
    const string user = "root";
    const string pass = "1";
    const string database = "project_DV1456";

    //this gets us the id of the contest that we want to delete.
    int contestIdToRemoveFrom = getIdFromDatabase(ui->LW_openList->currentRow());


    try
    {
        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        //1. remove the contestant
        stmt->execute("DELETE FROM `project_DV1456`.`contestant` WHERE `contests_contest_id`='"+to_string(contestIdToRemoveFrom)+"';");

        //2. remove the staff
        stmt->execute("DELETE FROM `project_DV1456`.`staff` WHERE `contests_contest_id`='"+to_string(contestIdToRemoveFrom)+"';");

        //3. remove the records
        //3.1. get the id of the track that the records are bound to
        string test = "SELECT track_id FROM project_DV1456.track WHERE contests_contest_id = '"+to_string(contestIdToRemoveFrom)+"';";
        stmt->execute("SELECT track_id FROM project_DV1456.track WHERE contests_contest_id = '"+to_string(contestIdToRemoveFrom)+"';");
        std::unique_ptr< sql::ResultSet > res;
        //3.2 remove the records for the track
        do  {
            res.reset(stmt->getResultSet());
            while (res->next()) {
                stmt->execute("DELETE FROM `project_DV1456`.`track_record` WHERE `track_track_id`='"+to_string(res->getInt("track_id"))+"';");
            }
        } while(stmt->getMoreResults());

        //4. remove the track
        stmt->execute("DELETE FROM `project_DV1456`.`track` WHERE `contests_contest_id`='"+to_string(contestIdToRemoveFrom)+"';");

        //5. remove the contest
        stmt->execute("DELETE FROM `project_DV1456`.`contests` WHERE `contest_id`='"+to_string(contestIdToRemoveFrom)+"';");

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
void DialogProgramStart::expandContestNameYearArray()
{
    this->capContestNameYear += 5;
    ContestNameYear **temp = new ContestNameYear*[this->capContestNameYear];
    for(int i = this->nrOfContestNameYear; i < this->capContestNameYear; i++)
    {
        temp[i] = nullptr;
    }
    for(int i = 0; i < this->nrOfContestNameYear; i++)
    {
        temp[i] = this->theContests[i];
    }
    delete [] this->theContests;
    this->theContests = temp;
    temp = nullptr;
}
int DialogProgramStart::currentYear()
{
    //Gets the current year, and saves it in the private variable 'year'
    time_t t = time(0);
    struct tm * now = localtime(&t);
    return now->tm_year + 1900;
}
void DialogProgramStart::on_BnCancel_clicked()
{
    close();
}
void DialogProgramStart::on_BnNew_clicked()
{
    bool okToAdd = true;
    DialogNewContest dialog;
    dialog.exec();

    for(int i = 0; i < ui->LW_openList->count(); i++)
    {
        if(dialog.getContestName() == ui->LW_openList->itemAt(i,0)->text().toStdString() //Lets not create same event twice in a year...
                && this->theContests[i]->getContestYear() == this->currentYear())
        {
            okToAdd = false;
        }
    }

    if(okToAdd)
    {
        this->contestName = dialog.getContestName();
        this->idOfContest = -1;
        close();
    }
    else
    {
        DialogError dialog("An contest with that name and year is already existing");
        dialog.exec();
    }
}
void DialogProgramStart::on_BnLoad_clicked()
{
    if(ui->LW_openList->currentRow() != -1)
    {
        this->contestName = ui->LW_openList->currentItem()->text().toStdString();
        this->idOfContest = getIdFromDatabase(ui->LW_openList->currentRow());
        close();
    }
    else
    {
        DialogError dialog("Please select the contest that you want to load.");
        dialog.exec();
    }
}

void DialogProgramStart::on_LW_openList_itemDoubleClicked(QListWidgetItem *item)
{
    this->contestName = item->text().toStdString();
    this->idOfContest = getIdFromDatabase(ui->LW_openList->currentRow());
    close();
}
void DialogProgramStart::on_BnDelete_clicked()
{
    if(ui->LW_openList->currentRow() != -1)
    {
        deleteContestFromDb();
        ui->LW_openList->clear();
        loadDatabase();
    }
    else
    {
        DialogError dialog("Please select the contest that you want to delete.");
        dialog.exec();
    }
}
