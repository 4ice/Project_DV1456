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
public:
    TrackRecord(string recordHolder="", int time = -1, string date = "-");
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
