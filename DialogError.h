#ifndef DIALOGDERROR_H
#define DIALOGDERROR_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

#include <string>

using namespace std;

class DialogError : public QDialog
{
    Q_OBJECT

private:
    QLabel *LInfo;
    QPushButton *BnOk;
public:
    DialogError(string error, QWidget *parent = 0);
};

#endif // DIALOGDERROR_H
