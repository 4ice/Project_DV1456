#ifndef DIALOGPROGRAMSTART_H
#define DIALOGPROGRAMSTART_H

#include <QDialog>
#include <QListWidgetItem>
#include <string>
#include "ContestHandler.h"
#include "ContestNameYear.h"
#include "ContestNameYear.h"

using namespace std;

namespace Ui {
class DialogProgramStart;
}

class DialogProgramStart : public QDialog
{
    Q_OBJECT

public:
    DialogProgramStart(string prevContestName = "", int idOfContest = -1, QWidget *parent = 0);
    ~DialogProgramStart();
    string getContestName() const;
    string getDatabaseContestName() const;
    int getIdOfContest() const;


private slots:
    void on_BnLoad_clicked();

    void on_BnNew_clicked();

    void on_BnCancel_clicked();

    void on_BnDelete_clicked();

    void on_LW_openList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::DialogProgramStart *ui;

    string contestName;
    int idOfContest;    //If this is -1, we haven't loaded a contest.
    ContestNameYear **theContests;  //to have a connection between contestName and yearOfcontest
    int capContestNameYear;
    int nrOfContestNameYear;

    void deleteContestFromDb();
    void expandContestNameYearArray();
    int currentYear();
    void loadDatabase();
    int getIdFromDatabase(int row) const;
};

#endif // DIALOGPROGRAMSTART_H
