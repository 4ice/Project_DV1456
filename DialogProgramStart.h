#ifndef DIALOGPROGRAMSTART_H
#define DIALOGPROGRAMSTART_H

#include <QDialog>
#include <QListWidgetItem>
#include <string>
#include "ContestHandler.h"

namespace Ui {
class DialogProgramStart;
}

class DialogProgramStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProgramStart(std::string prevContestName = "", int idOfContest = -1, QWidget *parent = 0);
    ~DialogProgramStart();
    std::string getContestName() const;
    std::string getDatabaseContestName() const;
    int getIdOfContest() const;

private slots:
    void loadDatabase();
    int getIdFromDatabase(string contestName) const;

    void on_BnCancel_clicked();

    void on_BnNew_clicked();

    void on_BnLoad_clicked();

    void on_LW_openList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::DialogProgramStart *ui;
    std::string contestName;
    std::string databaseContestName;
    int idOfContest;
};

#endif // DIALOGPROGRAMSTART_H
