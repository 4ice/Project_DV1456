#include "DialogProgramStart.h"
#include "ui_DialogProgramStart.h"
#include "DialogNewContest.h"

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
    this->contestName = "";
    this->databaseContestName = prevContestName;
    this->idOfContest = idOfContest;

    loadDatabase();
}

DialogProgramStart::~DialogProgramStart()
{
    delete ui;
}
string DialogProgramStart::getContestName() const
{
    return this->contestName;
}
string DialogProgramStart::getDatabaseContestName() const
{
    return this->databaseContestName;
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

    try
    {
        sql::Driver* driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        stmt->execute("SELECT contest_name FROM project_DV1456.contests;");
        std::unique_ptr< sql::ResultSet > res;
        do
        {
            res.reset(stmt->getResultSet());
            while (res->next())
            {
                ui->LW_openList->addItem(QString::fromStdString(res->getString("contest_name")));
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
int DialogProgramStart::getIdFromDatabase(string contestName) const
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

        stmt->execute("SELECT contest_id FROM project_DV1456.contests WHERE contest_name='"+contestName+"';");
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
void DialogProgramStart::on_BnCancel_clicked()
{
    close();
}
void DialogProgramStart::on_BnNew_clicked()
{
    DialogNewContest dialog;
    dialog.exec();

    this->databaseContestName = "";
    this->contestName = dialog.getContestName();

    close();
}
void DialogProgramStart::on_BnLoad_clicked()
{
    this->contestName = "";
    this->databaseContestName = ui->LW_openList->currentItem()->text().toStdString();
    this->idOfContest = getIdFromDatabase(this->databaseContestName);
    close();
}

void DialogProgramStart::on_LW_openList_itemDoubleClicked(QListWidgetItem *item)
{
    this->contestName = "";
    this->databaseContestName = item->text().toStdString();
    this->idOfContest = getIdFromDatabase(this->databaseContestName);
    close();
}
