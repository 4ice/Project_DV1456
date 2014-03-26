#ifndef DIALOGDELETETRACK_H
#define DIALOGDELETETRACK_H

#include <QDialog>
#include <QListWidgetItem>
#include <string>
#include "ContestHandler.h"
#include "DialogError.h"

namespace Ui {
class DialogDeleteTrack;
}

class DialogDeleteTrack : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDeleteTrack(ContestHandler &ch, QWidget *parent = 0);
    ~DialogDeleteTrack();
    string getTrackName() const;

private slots:
    void on_BnCancel_clicked();

    void on_BnOk_clicked();

    void on_LWTracks_itemDoubleClicked();

private:
    Ui::DialogDeleteTrack *ui;

    string trackName;
    ContestHandler &loadedContest;
};

#endif // DIALOGDELETETRACK_H
