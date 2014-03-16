#include "DialogDeletePerson.h"
#include "ui_DialogDeletePerson.h"

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


DialogDeletePerson::DialogDeletePerson(ContestHandler &ch, QWidget *parent) :
    QDialog(parent),
    loadedContest(ch),
    ui(new Ui::DialogDeletePerson)
{
    this->persons = new PersonNameSsn[this->loadedContest.getNrOfPpl()];
    this->ssn = "";
    this->nrOfCompetitors = 0;

    ui->setupUi(this);
    loadPeople();
}

DialogDeletePerson::~DialogDeletePerson()
{
    delete [] this->persons;
    delete ui;
}
string DialogDeletePerson::getSsn() const
{
    return this->ssn;
}
void DialogDeletePerson::loadPeople()
{
    int nrOfPersonsAdded = 0;
    ui->LW_Competitor->clear();
    ui->LW_Staff->clear();

    //Load the Competitors
    for(int i = 0; i < this->loadedContest.getNrOfPpl(); i++)
    {
        this->persons[nrOfPersonsAdded] = this->loadedContest.contestantInfo(i);

        if(this->persons[nrOfPersonsAdded].getName() != "")
        {   //Dynamic_cast for a Competitor was successful.
            ui->LW_Competitor->addItem(QString::fromStdString(this->persons[nrOfPersonsAdded++].getName()));
        }
    }
    this->nrOfCompetitors = nrOfPersonsAdded;

    //Load the Staff
    for(int i = 0; i < this->loadedContest.getNrOfPpl() && nrOfPersonsAdded < this->loadedContest.getNrOfPpl(); i++)
    {
        this->persons[nrOfPersonsAdded] = this->loadedContest.staffInfo(i);

        if(this->persons[nrOfPersonsAdded].getName() != "")
        {   //Dynamic_cast for a Staff was successful.
            ui->LW_Staff->addItem(QString::fromStdString(this->persons[nrOfPersonsAdded++].getName()));
        }
    }
}
void DialogDeletePerson::on_BnDelComp_clicked()
{
    this->ssn = this->persons[ui->LW_Competitor->currentRow()].getSsn();
    close();
}

void DialogDeletePerson::on_BnCancel_clicked()
{
    close();
}

void DialogDeletePerson::on_BnDelStaff_clicked()
{
    this->ssn = this->persons[ui->LW_Staff->currentRow()+this->nrOfCompetitors].getSsn();
    close();
}
void DialogDeletePerson::on_LW_Competitor_itemDoubleClicked()
{
    this->ssn = this->persons[ui->LW_Competitor->currentRow()].getSsn();
    close();
}

void DialogDeletePerson::on_LW_Staff_itemDoubleClicked()
{
    this->ssn = this->persons[ui->LW_Staff->currentRow()+this->nrOfCompetitors].getSsn();
    close();
}
