#ifndef CONTESTHANDLER_H
#define CONTESTHANDLER_H

#include "Competitor.h"
#include "Staff.h"
#include "Track.h"
#include "PersonNameSsn.h"



class ContestHandler
{
private:
    string contestName;
    int capPpl;
    int nrOfPpl;
    People **thePeople;
    int capTrack;       //Add
    int nrOfTrack;      //Add
    Track **theTracks;  //Add
    int currentYear;    //Format yyyy
    void freeMemory();
    void copyHelper(const ContestHandler &origObj);
public:
    ContestHandler(string contestName, int currentYear);
    virtual ~ContestHandler();
    ContestHandler(const ContestHandler &origObj);
    void operator=(const ContestHandler &origObj);
    string getContestName() const;
    int getNrOfPpl() const;
    int getNrOfTracks() const;
    int getYear() const;
    void setContestName(string contestName);
    void setCurrentYear(int currentYear);
    void addPerson(int currentYear, string name, string mail, string ssn, string gender, int startingNumber, int timeResult = -1);    //Competitor
    void addPerson(string name, string mail, string ssn, string task, string phoneNr);    //Staff
    bool removePerson(string ssn);  //number is specific for a person
    PersonNameSsn contestantInfo(int index) const;
    PersonNameSsn staffInfo(int index) const;
    void addTrack(string trackName, int distance, string location, string description);

    int posOfSsn(string ssn) const;
    void addResult(string ssn, int result);
    string toString(string what = "") const;
    string toSqlSaveString(int index, string what) const;
};
#endif
