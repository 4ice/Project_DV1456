#ifndef DIALOGDELETEPERSON_H
#define DIALOGDELETEPERSON_H

#include <QDialog>
#include <QListWidgetItem>
#include "ContestHandler.h"

namespace Ui {
class DialogDeletePerson;
}

class DialogDeletePerson : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDeletePerson(ContestHandler &ch, QWidget *parent = 0);
    ~DialogDeletePerson();
    string getSsn() const;

private slots:
    void loadPeople();
    //void loadStaff();

    void on_BnDelComp_clicked();

    void on_BnCancel_clicked();

    void on_BnDelStaff_clicked();

    void on_LW_Competitor_itemDoubleClicked();

    void on_LW_Staff_itemDoubleClicked();

private:
    PersonNameSsn *persons;
    //ssn is read from mainWindow to know which person that we want to delete.
    string ssn;
    //This is used to calculate the pos of the correct ssn if it's an staff member (staff is after the competitors in the array of persons)
    int nrOfCompetitors;
    ContestHandler &loadedContest;

    Ui::DialogDeletePerson *ui;
};

#endif // DIALOGDELETEPERSON_H
