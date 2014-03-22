#include "TrackRecord.h"
#include <sstream>

TrackRecord::TrackRecord(string recordHolder, double time, string date, string raceClass, int databaseId)
{
    this->recordHolder = recordHolder;
    this->time = time;
    this->date = date;
    this->raceClass = raceClass;
    this->databaseId = databaseId;
}
TrackRecord::~TrackRecord()
{
}
string TrackRecord::getRecordHolder() const
{
    return this->recordHolder;
}
double TrackRecord::getTime() const
{
    return this->time;
}
string TrackRecord::getDate() const
{
    return this->date;
}
int TrackRecord::getDatabaseId() const
{
    return this->databaseId;
}
void TrackRecord::setRecordHolder(string recordHolder)
{
    this->recordHolder = recordHolder;
}
void TrackRecord::setTime(double time)
{
    this->time = time;
}
void TrackRecord::setDate(string date)
{
    this->date = date;
}
string TrackRecord::toString() const
{
    stringstream ss;
    ss << this->time << "\nRecord holder: " << this->recordHolder
       << "\nDate of the record: " << this->date << endl;
    return ss.str();
}
string TrackRecord::toSqlSaveString() const
{
    string result = "";
    if(this->databaseId != -1)
    {
        result = "UPDATE `project_DV1456`.`track_record` SET recordHolder = \""+ this->recordHolder+
                "\", time = "+to_string(this->time)+
                ", date = \""+this->date+
                "\", raceClass = \""+this->raceClass+
                "\" WHERE track_record_id = "+to_string(this->databaseId)+";";
    }
    else
    {
        result = "INSERT INTO `project_DV1456`.`track_record` (`recordHolder`, `time`, `date`, `raceClass`, `track_track_id`) VALUES ('"+
                this->recordHolder+"', '"+to_string(this->time)+"', '"+this->date+"', '"+this->raceClass+"', '";
    }
    return result;
}
