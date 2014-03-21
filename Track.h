#ifndef TRACK_H
#define TRACK_H

#include "TrackRecord.h"

class Track
{
private:
    string trackName;
    int distance;
    TrackRecord record[2];     //Two records, one for males, one for females
    string location;
    string description;
    int databaseId;
public:
    Track(string trackName, int distance, string location, string description, int databaseId = -1);
    virtual ~Track();
    string getTrackName() const;
    int getDistance() const;
    string getRecord(int gender) const;
    string getLocation() const;
    string getDescription() const;
    int getDatabaseId() const;
    void setTrackName(string trackName);
    void setDistance(int distance);
    void setTrackRecord(string recordHolder, int time, string date, string gender);
    void setLocation(string location);
    void setDescription(string description);
    void setDatabaseId(int databaseId);
    string toString() const;
    Track *clone() const;
    string toSqlSaveString() const;
};

#endif // TRACK_H
