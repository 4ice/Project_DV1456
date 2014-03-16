#include "DialogNewContest.h"
#include "ui_DialogNewContest.h"

DialogNewContest::DialogNewContest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewContest)
{
    ui->setupUi(this);
    this->contestName = "";
}

DialogNewContest::~DialogNewContest()
{
    delete ui;
}
string DialogNewContest::getContestName() const
{
    return this->contestName;
}
void DialogNewContest::on_BnAdd_clicked()
{
    this->contestName = ui->LE_contestName->text().toStdString();
    accept();
}
