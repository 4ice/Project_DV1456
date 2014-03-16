//#include "DialogProgramStart.h"
//#include "DialogNewContest.h"

//#include <QtWidgets>

//#include "mysql_connection.h"

//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>

//DialogProgramStart::DialogProgramStart(string prevContestName, int idOfContest, QWidget *parent)
//    :QDialog(parent)
//{
//    this->contestName = "";
//    this->databaseContestName = prevContestName;
//    this->idOfContest = idOfContest;

//    infoLabel = new QLabel("Please choose to open an existing Contest, or create a new one");
//    openList = new QListWidget;
//    openButton = new QPushButton("Open");
//    newButton = new QPushButton("New");
//    cancelButton = new QPushButton("Cancel");

//    QGridLayout *gLayout = new QGridLayout;
//    gLayout->setColumnStretch(2,3);
//    gLayout->addWidget(infoLabel,0,1,1,2);
//    gLayout->addWidget(openList,1,1,1,2);

//    QHBoxLayout *buttonLayout = new QHBoxLayout;
//    buttonLayout->addWidget(cancelButton);
//    buttonLayout->addWidget(openButton);
//    buttonLayout->addWidget(newButton);

//    gLayout->addLayout(buttonLayout,3,1,1,2);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(gLayout);
//    setLayout(mainLayout);

//    loadDatabase();

//    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
//    connect(newButton, SIGNAL(clicked()), this, SLOT(newContest()));
//    connect(openButton, SIGNAL(clicked()), this, SLOT(initContest()));

//    setWindowTitle("Choose contest");


//}
//string DialogProgramStart::getContestName() const
//{
//    return this->contestName;
//}
//string DialogProgramStart::getDatabaseContestName() const
//{
//    return this->databaseContestName;
//}
//int DialogProgramStart::getIdOfContest() const
//{
//    return this->idOfContest;
//}
//void DialogProgramStart::loadDatabase()
//{
//    string url = "localhost";
//    const string user = "root";
//    const string pass = "1";
//    const string database = "project_DV1456";

//    try
//    {
//        sql::Driver* driver = get_driver_instance();
//        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
//        con->setSchema(database);
//        std::unique_ptr<sql::Statement> stmt(con->createStatement());

//        stmt->execute("SELECT contest_name FROM project_DV1456.contests;");
//        std::unique_ptr< sql::ResultSet > res;
//        do
//        {
//            res.reset(stmt->getResultSet());
//            while (res->next())
//            {
//                openList->addItem(QString::fromStdString(res->getString("contest_name")));
//            }
//        } while(stmt->getMoreResults());
//    }
//    catch(sql::SQLException &e)
//    {
//        /*
//              MySQL Connector/C++ throws three different exceptions:

//              - sql::MethodNotImplementedException (derived from sql::SQLException)
//              - sql::InvalidArgumentException (derived from sql::SQLException)
//              - sql::SQLException (derived from std::runtime_error)
//        */
//        cout << "# ERR: SQLException in " << __FILE__;
//        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
//        /* what() (derived from std::runtime_error) fetches error message */
//        cout << "# ERR: " << e.what();
//        cout << " (MySQL error code: " << e.getErrorCode();
//        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
//    }
//}
//void DialogProgramStart::newContest()
//{
//    DialogNewContest dialog;
//    if(dialog.exec())
//    {
//        this->databaseContestName = "";
//        this->contestName = dialog.nameText->text().toStdString();
//    }
//    close();
//}
//int DialogProgramStart::getIdFromDatabase(string contestName) const
//{
//    int theId = 0;

//    string url = "localhost";
//    const string user = "root";
//    const string pass = "1";
//    const string database = "project_DV1456";

//    try
//    {
//        sql::Driver* driver = get_driver_instance();
//        std::unique_ptr<sql::Connection> con(driver->connect(url, user, pass));
//        con->setSchema(database);
//        std::unique_ptr<sql::Statement> stmt(con->createStatement());

//        stmt->execute("SELECT contest_id FROM project_DV1456.contests WHERE contest_name='"+contestName+"';");
//        std::unique_ptr< sql::ResultSet > res;
//        res.reset(stmt->getResultSet());
//        res->next();

//        theId = res->getInt("contest_id");
//    }
//    catch(sql::SQLException &e)
//    {
//        /*
//              MySQL Connector/C++ throws three different exceptions:

//              - sql::MethodNotImplementedException (derived from sql::SQLException)
//              - sql::InvalidArgumentException (derived from sql::SQLException)
//              - sql::SQLException (derived from std::runtime_error)
//        */
//        cout << "# ERR: SQLException in " << __FILE__;
//        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
//        /* what() (derived from std::runtime_error) fetches error message */
//        cout << "# ERR: " << e.what();
//        cout << " (MySQL error code: " << e.getErrorCode();
//        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
//    }
//    return theId;
//}
//void DialogProgramStart::initContest()
//{
//    this->contestName = "";
//    this->databaseContestName = openList->currentItem()->text().toStdString();
//    this->idOfContest = getIdFromDatabase(this->databaseContestName);
//    close();
//}
