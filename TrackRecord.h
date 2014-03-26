#ifndef TRACKRECORD_H
#define TRACKRECORD_H

#include <string>

using namespace std;

class TrackRecord
{
private:
    string recordHolder;
    double time;
    string date;
    string raceClass;
    int databaseId;
public:
    TrackRecord(string recordHolder="", double time = -1, string date = "-", string raceClass = "", int databaseId = -1);
    virtual ~TrackRecord();
    string getRecordHolder() const;
    double getTime() const;
    string getDate() const;
    int getDatabaseId() const;
    void setRecordHolder(string recordHolder);
    void setTime(double time);
    void setDate(string date);
    void setDatabaseId(int databaseId);
    string toString() const;
    string toSqlSaveString(int gender) const;
};

#endif // TRACKRECORD_H
