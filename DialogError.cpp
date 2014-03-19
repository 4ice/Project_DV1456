#include "DialogError.h"

#include <QtWidgets>

DialogError::DialogError(string error, QWidget *parent)
    :QDialog(parent)
{
    this->LInfo = new QLabel(QString::fromStdString(error));
    this->BnOk = new QPushButton("OK");

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1,2);
    gLayout->addWidget(LInfo, 0, 0);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(BnOk);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(BnOk, SIGNAL(clicked()), this, SLOT(close()));

    setWindowTitle("Error");
}
