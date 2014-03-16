#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ContestHandler.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setYear();
    int getYear() const;
    void loadDatabaseToContestHandler(string databaseContestName, string idOfContest);
    string deletePerson(string ssn);

private slots:
    void startDialog();
    void saveToDb();
    void delPersonDialog();

    void on_BnAddCompetitor_clicked();

    void on_BnAddStaff_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_BnShowPeople_clicked();

    void on_BnAddResult_clicked();

private:
    void createMenus();

    Ui::MainWindow *ui;
    int year;
    ContestHandler *currentContest;
    int idOfContest;
    PersonNameSsn *theCompetitors;

    //Bar menu and actions
    QMenu *fileMenu;
    QAction *changeContestAct;
    QAction *exitAct;
    QAction *saveAct;

    QMenu *editMenu;
    QAction *delPersonAct;
    QAction *delTrackAct;
};
#endif
