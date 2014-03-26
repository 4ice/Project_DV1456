#ifndef DIALOGMAKEHTML_H
#define DIALOGMAKEHTML_H

#include <QDialog>
#include <QListWidgetItem>
#include <string>
#include "DialogError.h"
#include "ContestNameYear.h"

using namespace std;

namespace Ui {
class DialogMakeHtml;
}

class DialogMakeHtml : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMakeHtml(QWidget *parent = 0);
    ~DialogMakeHtml();
    string getNameOfContest() const;
    int getIdOfContest() const;

private slots:
    void on_BnCancel_clicked();

    void on_BnOk_clicked();

private:
    Ui::DialogMakeHtml *ui;
    string nameOfContest;
    int idOfContest;

    ContestNameYear **theContests;  //to have a connection between contestName and yearOfcontest
    int capContestNameYear;
    int nrOfContestNameYear;
    void expandContestNameYearArray();

    void loadDatabase();
    int getIdFromDatabase(int row) const;
};

#endif // DIALOGMAKEHTML_H
