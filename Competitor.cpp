#include "Competitor.h"
#include <sstream>

Competitor::Competitor()
    :People("","","")
{
    this->gender="";
    this->startingNumber = -1;
    this->raceClass = "";
    this->timeResult = -1;
}

Competitor::Competitor(int databaseId, int currentYear, string name, string mail, string ssn, string gender, string track, int startingNumber, int timeResult)
    :People(name, mail, ssn, databaseId)
{
    this->gender = gender;
    this->startingNumber = startingNumber;
    this->track = track;
    this->raceClass = calculateRaceClass(this->age(std::stoi(this->getSsn().substr(0,4)), currentYear));
    this->timeResult = timeResult;
}
Competitor::~Competitor()
{
}
string Competitor::getGender() const
{
    return this->gender;
}
int Competitor::getStartingNumber() const
{
    return this->startingNumber;
}
int Competitor::getTimeResult() const
{
    return this->timeResult;
}
string Competitor::getRaceClass() const
{
    return this->raceClass;
}
string Competitor::getTrack() const
{
    return this->track;
}
void Competitor::setGender(string gender)
{
    this->gender = gender;
}
void Competitor::setStartingNumber(int startingNumber)
{
    this->startingNumber = startingNumber;
}
void Competitor::setTimeResult(int timeResult)
{
    this->timeResult = timeResult;
}
void Competitor::setRaceClass(string raceClass)
{
    this->raceClass = raceClass;
}
void Competitor::setTrack(string track)
{
    this->track = track;
}
int Competitor::age(int birthYear, int currentYear) const
{
    return currentYear-birthYear;
}
string Competitor::calculateRaceClass(int age)
{
    int theClassNumber = 0;
    string className = "";
    if(this->gender == "male" && age <= 16)      //Boys
    {
       className = "P";
    }
    else if(this->gender == "female" && age <= 16)   //Girl
    {
        className = "F";
    }
    theClassNumber = (age/2) * 2;
    className+=theClassNumber;
    //return className;
    return "P20";
}

string Competitor::toStringSpecific() const
{
    stringstream ss;
    ss << "Competing on track: " << this->getTrack() << "\nStarting number: " << this->startingNumber << endl;
    if (this->timeResult == -1)
    {
        ss << "Time result: Not finished!" << endl;
    }
    else
    {
        ss << "Time result: " << this->timeResult << endl;
    }
    return ss.str();
}
Competitor *Competitor::clone() const
{
    return new Competitor(*this);
}
string Competitor::toSqlSaveStringSpecific() const
{
    string result = "";

    if(this->getDatabaseId() == -1)
    {
        result = "INSERT IGNORE INTO `project_DV1456`.`contestant` (`name`, `mail`, `SSN`, `gender`, `track`, `startingNumber`, `timeResult`, `raceClass`, `contests_contest_id`) VALUES('"
                +this->getName()+"', '"+this->getMail()+"', '"+this->getSsn()+"', '"+this->gender+"', '"+this->getTrack()+"', '"
                +to_string(this->startingNumber)+"', '"+to_string(this->timeResult)+"', '"+this->raceClass+"', '";
    }
    else
    {
        result = "UPDATE `project_DV1456`.`contestant` SET SSN = "+ this->getSsn()+
                ", name = \""+ this->getName()+
                "\", mail = \""+ this->getMail()+
                "\", gender = \""+ this->gender+
                "\", startingNumber = \""+ this->getTrack()+
                "\", startingNumber = "+ to_string(this->startingNumber)+
                ", timeResult = "+ to_string(this->timeResult)+
                ", raceClass = \""+ this->raceClass+
                "\" WHERE contestant_id = "+ to_string(this->getDatabaseId())+";";
    }
    return result;
}
string Competitor::toSqlDeleteStringSpecific() const
{
    return "DELETE FROM `project_DV1456`.`contestant` WHERE `contestant_id`='";
}

//DELETE FROM `project_DV1456`.`contestant` WHERE `contestant_id`='30';
