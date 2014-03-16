#ifndef DIALOGNEWCONTEST_H
#define DIALOGNEWCONTEST_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class DialogNewContest;
}

class DialogNewContest : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewContest(QWidget *parent = 0);
    ~DialogNewContest();
    string getContestName() const;

private slots:
    void on_BnAdd_clicked();

private:
    Ui::DialogNewContest *ui;
    string contestName;
};

#endif // DIALOGNEWCONTEST_H
