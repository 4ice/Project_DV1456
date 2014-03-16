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

Competitor::Competitor(int currentYear, string name, string mail, string ssn, string gender, int startingNumber, int timeResult)
    :People(name, mail, ssn)
{
    this->gender = gender;
    this->startingNumber = startingNumber;
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
    ss << "\nStarting number: " << this->startingNumber << endl;
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
    return "INSERT IGNORE INTO `project_DV1456`.`contestant` (`name`, `mail`, `SSN`, `gender`, `startingNumber`, `timeResult`, `raceClass`, `contests_contest_id`) VALUES('"
            +this->getName()+"', '"+this->getMail()+"', '"+this->getSsn()+"', '"+this->gender+"', '"
            +to_string(this->startingNumber)+"', '"+to_string(this->timeResult)+"', '"+this->raceClass+"', '";
}
