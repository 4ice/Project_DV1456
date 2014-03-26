#include "DialogMakeHtml.h"
#include "ui_DialogMakeHtml.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

DialogMakeHtml::DialogMakeHtml(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMakeHtml)
{
    ui->setupUi(this);
    this->nameOfContest = "";


    this->capContestNameYear = 5;
    this->nrOfContestNameYear = 0;
    this->theContests = new ContestNameYear*[this->capContestNameYear];
    for(int i = 0; i < this->capContestNameYear; i++)
    {
        this->theContests[i] = nullptr;
    }


    loadDatabase();
}

DialogMakeHtml::~DialogMakeHtml()
{
    delete ui;

    for(int i = 0; i < this->nrOfContestNameYear; i++)
    {
        delete this->theContests[i];
    }
    delete [] this->theContests;
}
string DialogMakeHtml::getNameOfContest() const
{
    return this->nameOfContest;
}
int DialogMakeHtml::getIdOfContest() const
{
    return this->idOfContest;
}
void DialogMakeHtml::loadDatabase()
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

        stmt->execute("SELECT * FROM project_DV1456.contests;");
        std::unique_ptr< sql::ResultSet > res;
        do
        {
            res.reset(stmt->getResultSet());
            while (res->next())
            {
                if(this->capContestNameYear == this->nrOfContestNameYear)
                {
                    this->expandContestNameYearArray();
                }
                this->theContests[this->nrOfContestNameYear] = new ContestNameYear(res->getString("contest_name"), res->getInt("year_of_contest"));
                ui->LW_contests->addItem(QString::fromStdString(this->theContests[nrOfContestNameYear]->getContestName()));
                this->nrOfContestNameYear++;
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
int DialogMakeHtml::getIdFromDatabase(int row) const
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

        string test = "SELECT contest_id FROM project_DV1456.contests WHERE contest_name='"+this->theContests[row]->getContestName()+
                "' AND year_of_contest='"+to_string(this->theContests[row]->getContestYear())+"';";

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
void DialogMakeHtml::expandContestNameYearArray()
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
void DialogMakeHtml::on_BnCancel_clicked()
{
    close();
}

void DialogMakeHtml::on_BnOk_clicked()
{
    if(ui->LW_contests->currentRow() != -1)
    {
        this->nameOfContest = ui->LW_contests->currentItem()->text().toStdString();
        this->idOfContest = getIdFromDatabase(ui->LW_contests->currentRow());
        close();
    }
    else
    {
        DialogError dialog("Please choose a contest that you want to use.");
        dialog.exec();
    }
}
