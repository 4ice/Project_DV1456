#include "ContestHandler.h"


ContestHandler::ContestHandler(string contestName, int contestYear, int contestId)
{
    this->contestName = contestName;
    this->contestYear = contestYear;
    this->contestId = contestId;

    this->capPpl = 50;
    this->nrOfPpl = 0;
    this->thePeople = new People*[this->capPpl];
    for(int i = 0; i < this->capPpl; i++)
    {
        this->thePeople[i] = nullptr;
    }

    this->capTrack = 3;
    this->nrOfTrack = 0;
    this->theTracks = new Track*[this->capTrack];
    for(int i = 0; i < this->capTrack; i++)
    {
        this->theTracks[i] = nullptr;
    }
    //Track**
}
void ContestHandler::freeMemory()
{
    //People
    for(int i = 0; i<this->nrOfPpl; i++)
    {
        delete this->thePeople[i];
    }
    delete [] this->thePeople;

    //Tracks
    for(int i = 0; i< this->nrOfTrack; i++)
    {
        delete this->theTracks[i];
    }
    delete [] this->theTracks;
}
void ContestHandler::copyHelper(const ContestHandler &origObj)
{
    this->contestName = origObj.contestName;
    this->contestYear = origObj.contestYear;

    this->capPpl = origObj.capPpl;
    this->nrOfPpl = origObj.nrOfPpl;

    //People
    this->thePeople = new People*[origObj.capPpl];
    for(int i = origObj.nrOfPpl; i<origObj.capPpl; i++)
    {
        this->thePeople[i] = nullptr;
    }
    for(int i = 0; i < origObj.nrOfPpl; i++)
    {
        this->thePeople[i] = origObj.thePeople[i]->clone();
    }

    //Tracks
    this->theTracks = new Track*[origObj.capTrack];
    for(int i = origObj.nrOfTrack; i < origObj.capTrack; i++)
    {
        this->theTracks[i] = nullptr;
    }
    for(int i = 0; i < origObj.nrOfPpl; i++)
    {
        this->theTracks[i] = origObj.theTracks[i]->clone();
    }
}
ContestHandler::~ContestHandler()
{
    freeMemory();
}
ContestHandler::ContestHandler(const ContestHandler &origObj)
{
    copyHelper(origObj);
}
void ContestHandler::operator =(const ContestHandler &origObj)
{
    freeMemory();
    copyHelper(origObj);
}
int ContestHandler::getContestId() const
{
    return this->contestId;
}
string ContestHandler::getContestName() const
{
    return this->contestName;
}
int ContestHandler::getContestYear() const
{
    return this->contestYear;
}
void ContestHandler::setContestName(string contestName)
{
    this->contestName = contestName;
}
int ContestHandler::getNrOfPpl() const
{
    return this->nrOfPpl;
}
int ContestHandler::getNrOfTracks() const
{
    return this->nrOfTrack;
}
void ContestHandler::setContestId(int contestId)
{
    this->contestId = contestId;
}
void ContestHandler::setContestYear(int contestYear)
{
    this->contestYear = contestYear;
}
void ContestHandler::addPerson(int contestYear, string name, string mail, string ssn, string gender, string track, int startingNumber, int databaseId, int timeResult)
{
    if(this->nrOfPpl == this->capPpl)
    {
        this->capPpl+=10;
        People **temp = new People*[this->capPpl];
        for(int i = this->nrOfPpl; i < this->capPpl; i++)
        {
            temp[i] = nullptr;
        }
        for(int i = 0; i < this->nrOfPpl; i++)
        {
            temp[i] = this->thePeople[i];
        }
        delete [] this->thePeople;
        this->thePeople = temp;
        temp = nullptr;
    }
    this->thePeople[this->nrOfPpl++] = new Competitor(databaseId, contestYear, name, mail, ssn, gender, track, startingNumber, timeResult);
}
void ContestHandler::addPerson(string name, string mail, string ssn, string task, string phoneNr, int databaseId)
{
    if(this->nrOfPpl == this->capPpl)
    {
        this->capPpl+=10;
        People **temp = new People*[this->capPpl];
        for(int i = this->nrOfPpl; i < this->capPpl; i++)
        {
            temp[i] = nullptr;
        }
        for(int i = 0; i < this->nrOfPpl; i++)
        {
            temp[i] = this->thePeople[i];
        }
        delete [] this->thePeople;
        this->thePeople = temp;
        temp = nullptr;
    }
    this->thePeople[this->nrOfPpl] = new Staff(databaseId, name, mail, ssn, task, phoneNr);
    this->nrOfPpl++;
}
bool ContestHandler::removePerson(string ssn)
{
    bool personFound = false;

    for(int i = 0; i < this->nrOfPpl && personFound == false; i++)
    {
        if(this->thePeople[i]->getSsn() == ssn)
        {
            personFound = true;
            delete this->thePeople[i];
            this->thePeople[i] = this->thePeople[--this->nrOfPpl];
            this->thePeople[this->nrOfPpl] = nullptr;
        }
    }
    return personFound;
}
string ContestHandler::trackName(int index) const
{
    return this->theTracks[index]->getTrackName();
}
PersonNameSsn ContestHandler::contestantInfo(int index) const
{
    PersonNameSsn result;

    Competitor *aCompetitor = dynamic_cast<Competitor *>(this->thePeople[index]);
    if(aCompetitor != nullptr)
    {
        result.setName(aCompetitor->getName());
        result.setSsn(aCompetitor->getSsn());
    }
    return result;
}
PersonNameSsn ContestHandler::staffInfo(int index) const
{
    PersonNameSsn result;

    Staff *aStaff = dynamic_cast<Staff *>(this->thePeople[index]);
    if(aStaff != nullptr)
    {
        result.setName(aStaff->getName());
        result.setSsn(aStaff->getSsn());
    }
    return result;
}
void ContestHandler::addTrack(string trackName, int distance, string location, string description, int databaseId)
{
    if(this->nrOfTrack == this->capTrack)
    {
        this->capTrack += 10;
        Track **temp = new Track*[this->capTrack];
        for(int i = this->nrOfTrack; i < this->capTrack; i++)
        {
            temp[i] = nullptr;
        }
        for(int i = 0; i < this->nrOfTrack; i++)
        {
            temp[i] = this->theTracks[i];
        }
        delete [] this->theTracks;
        this->theTracks = temp;
        temp = nullptr;
    }
    this->theTracks[this->nrOfTrack++] = new Track(trackName, distance, location, description, databaseId);
}
bool ContestHandler::removeTrack(string trackName)
{
    bool trackFound = false;

    for(int i = 0; i < this->nrOfTrack && trackFound == false; i++)
    {
        if(this->theTracks[i]->getTrackName() == trackName)
        {
            trackFound = true;
            delete this->theTracks[i];
            this->theTracks[i] = this->theTracks[--this->nrOfTrack];
            this->theTracks[this->nrOfTrack] = nullptr;
        }
    }
    return trackFound;
}

string ContestHandler::fetchTrackName(int index)
{
    return this->theTracks[index]->getTrackName();
}

int ContestHandler::posOfSsn(string ssn) const
{
    int pos = -1;

    for(int i = 0; i < this->nrOfPpl && pos == -1; i++)
    {
        if(this->thePeople[i]->getSsn()==ssn)
        {
            pos = i;
        }
    }
    return pos;
}
int ContestHandler::posOfTrack(string trackName)
{
    int trackPos = -1;

    for(int i = 0; i < this->nrOfTrack && trackPos == -1; i++)
    {
        if(this->theTracks[i]->getTrackName() == trackName)
        {
            trackPos = i;
        }
    }

    return trackPos;
}
bool ContestHandler::addResult(string ssn, double result, int trackPos)
{
    bool newRecord = false;
    //add the result to the person
    Competitor *aCompetitor = dynamic_cast<Competitor *>(this->thePeople[this->posOfSsn(ssn)]);
    if(aCompetitor != nullptr)
    {
        aCompetitor->setTimeResult(result);
        if(aCompetitor->getGender() == "Male")
        {                                                   //the zero means that it's a male
            newRecord = this->theTracks[trackPos]->checkRecord(this->nrOfPpl, 0, aCompetitor->getTimeResult(), aCompetitor->getName(), aCompetitor->getRaceClass());
        }
        else
        {                                                    //the one means that it's a female
            newRecord = this->theTracks[trackPos]->checkRecord(this->nrOfPpl, 1, aCompetitor->getTimeResult(), aCompetitor->getName(), aCompetitor->getRaceClass());
        }
    }
    return newRecord;
}
void ContestHandler::addRecordFromDb(int posOfTrack, string recordHolder, double time, string date, int gender, string raceClass, int databaseId)
{
    this->theTracks[posOfTrack]->setTrackRecord(recordHolder, time, date, gender, raceClass, databaseId);
}
int ContestHandler::peopleDatabaseId(int index) const
{
    return this->thePeople[index]->getDatabaseId();
}
int ContestHandler::trackDatabaseId(int index) const
{
    return this->theTracks[index]->getDatabaseId();
}
void ContestHandler::setTrackDatabaseId(int databaseId, int index)
{
    this->theTracks[index]->setDatabaseId(databaseId);
}
string ContestHandler::toString(string what) const
{
    string result = "";

    if(what == "people")
    {
        for(int i = 0; i < this->nrOfPpl; i++)
        {
            result += this->thePeople[i]->toString() + "\n";
        }
    }
    else if(what == "competitor")
    {
        Competitor *aCompetitor = nullptr;
        for(int i = 0; i < this->nrOfPpl; i++)
        {
            aCompetitor = dynamic_cast<Competitor *>(this->thePeople[i]);
            if(aCompetitor != nullptr)
            {
                result += this->thePeople[i]->toString() + "\n";
            }
        }
    }
    else if(what == "staff")
    {
        Staff *aStaff = nullptr;
        for(int i = 0; i < this->nrOfPpl; i++)
        {
            aStaff = dynamic_cast<Staff *>(this->thePeople[i]);
            if(aStaff != nullptr)
            {
                result += this->thePeople[i]->toString() + "\n";
            }
        }

    }
    else if(what == "tracks")
    {
        for(int i = 0; i < this->nrOfTrack; i++)
        {
            result += this->theTracks[i]->toString() + "\n";
        }
    }
    return result;
}
string ContestHandler::toSqlSaveStringSpecific(int index, string what, int gender) const
{
    string result = "";
    if(what == "people")
    {
        result = this->thePeople[index]->toSqlSaveStringSpecific();
    }
    if(what == "track")
    {
        result = this->theTracks[index]->toSqlSaveString();
    }
    if(what == "trackRecord")
    {
        result = this->theTracks[index]->toSqlSaveStringRecords(gender);
    }
    return result;
}
string ContestHandler::toSqlInsertString(int index, string what) const
{
    string result = "";
    if(what == "people")
    {
        result = this->thePeople[index]->toSqlSaveStringSpecific();
    }
    else if(what == "track")
    {
        result = this->theTracks[index]->toSqlSaveString();
    }
    return result;
}
void ContestHandler::recordInserted(int index, int gender, int recordDatabaseId)
{
    this->theTracks[index]->editRecordDatabaseId(gender, recordDatabaseId);
}
string ContestHandler::competitorsTrack(string ssn)
{
    string trackName = "";

    Competitor *aCompetitor = dynamic_cast<Competitor *>(this->thePeople[posOfSsn(ssn)]);
    if(aCompetitor != nullptr)
    {
        trackName = aCompetitor->getTrack();
    }
    return trackName;
}
string ContestHandler::toSqlDeleteString(int index) const
{
    return this->thePeople[index]->toSqlDeleteStringSpecific();
}
