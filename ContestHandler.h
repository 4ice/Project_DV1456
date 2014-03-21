#ifndef CONTESTHANDLER_H
#define CONTESTHANDLER_H

#include "Competitor.h"
#include "Staff.h"
#include "Track.h"
#include "PersonNameSsn.h"



class ContestHandler
{
private:
    int contestId;
    string contestName;
    int capPpl;
    int nrOfPpl;
    People **thePeople;
    int capTrack;       //Add
    int nrOfTrack;      //Add
    Track **theTracks;  //Add
    int contestYear;    //Format yyyy
    void freeMemory();
    void copyHelper(const ContestHandler &origObj);
public:
    //If contestId equals -1, that means that the contest was not read from a database,
    //and therefore we should insert a new contest in the database instead of trying to update an exsisting one.
    ContestHandler(string contestName, int currentYear, int contestId = -1);
    virtual ~ContestHandler();
    ContestHandler(const ContestHandler &origObj);
    void operator=(const ContestHandler &origObj);
    int getContestId() const;
    string getContestName() const;
    int getNrOfPpl() const;
    int getNrOfTracks() const;
    int getContestYear() const;
    void setContestId(int contestId);
    void setContestName(string contestName);
    void setContestYear(int contestYear);
    void addPerson(int currentYear, string name, string mail, string ssn, string gender, int startingNumber, int databaseId, int timeResult = -1);    //Competitor
    void addPerson(string name, string mail, string ssn, string task, string phoneNr, int databaseId);    //Staff
    bool removePerson(string ssn);  //number is specific for a person
    PersonNameSsn contestantInfo(int index) const;
    PersonNameSsn staffInfo(int index) const;
    void addTrack(string trackName, int distance, string location, string description, int databaseId);
    bool removeTrack(string trackName);
    string fetchTrackName(int index);
    int posOfSsn(string ssn) const;
    void addResult(string ssn, int result);
    int peopleDatabaseId(int index) const;
    int trackDatabaseId(int index) const;
    string toString(string what = "people") const;
    string toSqlSaveStringSpecific(int index, string what) const;
    string toSqlInsertString(int index, string what) const;
};
#endif
