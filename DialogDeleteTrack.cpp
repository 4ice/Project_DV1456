#include "DialogDeleteTrack.h"
#include "ui_DialogDeleteTrack.h"

DialogDeleteTrack::DialogDeleteTrack(ContestHandler &ch, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDeleteTrack),
    loadedContest(ch)
{
    this->trackName = "";

    ui->setupUi(this);

    for(int i = 0; i < this->loadedContest.getNrOfTracks(); i++)
    {
        ui->LWTracks->addItem(QString::fromStdString(this->loadedContest.fetchTrackName(i)));
    }
}
DialogDeleteTrack::~DialogDeleteTrack()
{
    delete ui;
}
string DialogDeleteTrack::getTrackName() const
{
    return this->trackName;
}
void DialogDeleteTrack::on_BnCancel_clicked()
{
    close();
}

void DialogDeleteTrack::on_BnOk_clicked()
{
    if(ui->LWTracks->currentRow() != -1)
    {
        this->trackName = this->loadedContest.fetchTrackName(ui->LWTracks->currentRow());

        close();
    }
    else
    {
        DialogError dialog("Select a track that you want to remove.");
        dialog.exec();
    }
}

void DialogDeleteTrack::on_LWTracks_itemDoubleClicked()
{
    this->trackName = this->loadedContest.fetchTrackName(ui->LWTracks->currentRow());
    close();
}
