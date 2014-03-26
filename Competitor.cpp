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
    this->raceClass = calculateRaceClass(this->age(std::stoi(this->getSsn().substr(0,2)), currentYear));
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
    //if this is true, the person is born year 2000 or later
    if(birthYear < currentYear-2000)
    {
        birthYear += 2000;
    }
    else
    {
        birthYear += 1900;
    }
    return currentYear-birthYear;
}
string Competitor::calculateRaceClass(int age)
{
    int theClassNumber = 0;
    string className = "";
    if(this->gender == "Male" && age <= 16)      //Pojkar
    {
       className = "P";
    }
    else if(this->gender == "Female" && age <= 16)   //Flickor
    {
        className = "F";
    }
    if(this->gender == "Male" && age > 16)      //Herrar
    {
        className = "H";
    }
    else if(this->gender == "Female" && age > 16)   //Damer
    {
        className = "D";
    }
    theClassNumber = (age/2) * 2;
    className+=to_string(theClassNumber);
    return className;
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
