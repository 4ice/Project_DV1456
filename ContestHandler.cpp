#include "ContestHandler.h"


ContestHandler::ContestHandler(string contestName, int currentYear)
{
    this->contestName = contestName;
    this->currentYear = currentYear;

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
    this->currentYear = origObj.currentYear;

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
string ContestHandler::getContestName() const
{
    return this->contestName;
}
int ContestHandler::getYear() const
{
    return this->currentYear;
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
void ContestHandler::setCurrentYear(int currentYear)
{
    this->currentYear = currentYear;
}
void ContestHandler::addPerson(int currentYear, string name, string mail, string ssn, string gender, int startingNumber, int timeResult)
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
    this->thePeople[this->nrOfPpl++] = new Competitor(currentYear, name, mail, ssn, gender, startingNumber, timeResult);
}
void ContestHandler::addPerson(string name, string mail, string ssn, string task, string phoneNr)
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
    this->thePeople[this->nrOfPpl] = new Staff(name, mail, ssn, task, phoneNr);
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
void ContestHandler::addTrack(string trackName, int distance, string location, string description)
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
    this->theTracks[this->nrOfTrack++] = new Track(trackName, distance, location, description);
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
void ContestHandler::addResult(string ssn, int result)
{
    Competitor *aCompetitor = dynamic_cast<Competitor *>(this->thePeople[this->posOfSsn(ssn)]);
    if(aCompetitor != nullptr)
    {
        aCompetitor->setTimeResult(result);
    }
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
string ContestHandler::toSqlSaveString(int index, string what) const
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
    return result;
}
