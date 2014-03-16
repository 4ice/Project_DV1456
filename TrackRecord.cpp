#include "TrackRecord.h"
#include <sstream>

TrackRecord::TrackRecord(string recordHolder, int time, string date)
{
    this->recordHolder = recordHolder;
    this->time = time;
    this->date = date;
}
TrackRecord::~TrackRecord()
{
}
string TrackRecord::getRecordHolder() const
{
    return this->recordHolder;
}
int TrackRecord::getTime() const
{
    return this->time;
}
string TrackRecord::getDate() const
{
    return this->date;
}
void TrackRecord::setRecordHolder(string recordHolder)
{
    this->recordHolder = recordHolder;
}
void TrackRecord::setTime(int time)
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
