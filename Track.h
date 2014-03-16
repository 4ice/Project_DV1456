#ifndef TRACK_H
#define TRACK_H

#include "TrackRecord.h"

class Track
{
private:
    string trackName;
    int distance;
    TrackRecord record[2];     //We want two records, one for males, one for females
    string location;
    string description;
public:
    Track(string trackName, int distance, string location, string description);
    virtual ~Track();
    string getTrackName() const;
    int getDistance() const;
    string getRecord(int gender) const;
    string getLocation() const;
    string getDescription() const;
    void setTrackName(string trackName);
    void setDistance(int distance);
    void setTrackRecord(string recordHolder, int time, string date, string gender);
    void setLocation(string location);
    void setDescription(string description);
    string toString() const;
    Track *clone() const;
    string toSqlSaveString() const;
};

#endif // TRACK_H
