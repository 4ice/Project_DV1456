#ifndef TRACKRECORD_H
#define TRACKRECORD_H

#include <string>

using namespace std;

class TrackRecord
{
private:
    string recordHolder;
    int time;
    string date;
    string raceClass;
public:
    TrackRecord(string recordHolder="Unknown", int time = -1, string date = "000000");
    virtual ~TrackRecord();
    string getRecordHolder() const;
    int getTime() const;
    string getDate() const;
    void setRecordHolder(string recordHolder);
    void setTime(int time);
    void setDate(string date);
    string toString() const;
};

#endif // TRACKRECORD_H
