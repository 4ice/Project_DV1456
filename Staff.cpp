#include "Staff.h"
#include <sstream>

Staff::Staff(string name, string mail, string ssn, string task, string phoneNr)
    :People(name, mail, ssn)
{
    this->task = task;
    this->phoneNr = phoneNr;
}
Staff::~Staff()
{
}
string Staff::getTask() const
{
    return this->task;
}
string Staff::getPhoneNr() const
{
    return this->phoneNr;
}
void Staff::setTask(string task)
{
    this->task = task;
}
void Staff::setPhoneNr(string phoneNr)
{
    this->phoneNr = phoneNr;
}
string Staff::toStringSpecific() const
{
    stringstream ss;
    ss << "Task: " << this->task << "\nPhone Number: " << this->phoneNr << endl;
    return ss.str();
}
Staff *Staff::clone() const
{
    return new Staff(*this);
}
string Staff::toSqlSaveStringSpecific() const
{
    return "INSERT IGNORE INTO `project_DV1456`.`staff`  (`ssn`, `name`, `mail`, `task`, `phoneNr`, `contests_contest_id`) VALUES ('"
            +this->getSsn()+"', '"+this->getName()+"', '"+this->getMail()+"', '"+this->task+"', '"+this->phoneNr+"', '";
}
