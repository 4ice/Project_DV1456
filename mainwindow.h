#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ContestHandler.h"
#include <QMainWindow>
#include <QListWidgetItem>

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
    void makeHtml();

private slots:
    void startDialog();
    void saveToDb();
    void delPersonDialog();
    void delTrackDialog();

    void on_BnAddCompetitor_clicked();

    void on_BnAddStaff_clicked();

    void on_BnAddResult_clicked();

    void on_LW_people_itemClicked();

    void on_BnAddTrack_clicked();

private:
    void createMenus();

    Ui::MainWindow *ui;
    int year;
    ContestHandler *currentContest;
    PersonNameSsn *theCompetitors;

    //Bar menu and actions
    QMenu *fileMenu;
    QAction *changeContestAct;
    QAction *exitAct;
    QAction *saveAct;
    QAction *makeHtmlAct;

    QMenu *editMenu;
    QAction *delPersonAct;
    QAction *delTrackAct;
};
#endif
