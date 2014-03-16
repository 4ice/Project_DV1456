#include "Track.h"
#include <sstream>

Track::Track(string trackName, int distance, string location, string description)
{
    this->trackName = trackName;
    this->distance = distance;
    this->location = location;
    this->description = description;
}
Track::~Track()
{
}
string Track::getTrackName() const
{
    return this->trackName;
}
int Track::getDistance() const
{
    return this->distance;
}
string Track::getRecord(int gender) const   //gender=0 -> male, gender=1 -> female
{
    return this->record[gender].toString();
}
string Track::getLocation() const
{
    return this->location;
}
string Track::getDescription() const
{
    return this->description;
}
void Track::setTrackName(string trackName)
{
    this->trackName = trackName;
}
void Track::setDistance(int distance)
{
    this->distance = distance;
}
void Track::setTrackRecord(string recordHolder, int time, string date, string gender)
{
    if(gender == "male")
    {
        this->record[0] = TrackRecord(recordHolder, time, date);
    }
    else    //Female
    {
        this->record[1] = TrackRecord(recordHolder, time, date);
    }
}
void Track::setLocation(string location)
{
    this->location = location;
}
void Track::setDescription(string description)
{
    this->description = description;
}
string Track::toString() const
{
    stringstream ss;

    ss << "Track name: " << this->trackName << "\nDistance: " << this->distance;
    if(this->record[0].getTime() != -1) //if there is an record on this track for a male, then do the following
    {
        ss << "\nRecord for males: " << this->record[0].toString() << this->distance;
    }
    if(this->record[1].getTime() != -1) //if there is an record on this track for a female, then do the following
    {
        ss << "\nRecord for females: " << this->record[1].toString();
    }
    ss << "\nLocation: " << this->location << "\nDescription: "
       << this->description << endl;

    return ss.str();
}
Track *Track::clone() const
{
    return new Track(*this);
}
string Track::toSqlSaveString() const
{
    return "INSERT IGNORE INTO `project_DV1456`.`TRACK` (`track_name`, `distance`, `location`, `description`, `CONTESTS_contest_id`) VALUES ('"
            +this->trackName+"', '"+to_string(this->distance)+"', '"+this->location+"', '"+this->description+"', '";
}
