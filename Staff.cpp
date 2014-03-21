#include "Staff.h"
#include <sstream>

Staff::Staff(int databaseId, string name, string mail, string ssn, string task, string phoneNr)
    :People(name, mail, ssn, databaseId)
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
    string result = "";

    if(this->getDatabaseId() == -1)  //databaseId -1 means that the member isn't existing in the database at this moment, therefore we need to do INSERT instead of update.
    {
        result = "INSERT IGNORE INTO `project_DV1456`.`staff`  (`SSN`, `name`, `mail`, `task`, `phoneNr`, `contests_contest_id`) VALUES ('"
                +this->getSsn()+"', '"+this->getName()+"', '"+this->getMail()+"', '"+this->task+"', '"+this->phoneNr+"', '";
    }
    else    //If databaseId != from -1, the member is already existing in the database, and therefore we only update the row.
    {
        result = "UPDATE `project_DV1456`.`staff` SET SSN = "+ this->getSsn()+
                ", name = \""+ this->getName()+
                "\", mail = \""+ this->getMail()+
                "\", task = \""+ this->task+
                "\", phoneNr = \""+ this->phoneNr+
                "\" WHERE staff_id = "+ to_string(this->getDatabaseId())+";";
    }
    return result;
}
