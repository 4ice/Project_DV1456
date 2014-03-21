#ifndef STAFF_H
#define STAFF_H
#include "People.h"

class Staff : public People
{
private:
    string task;
    string phoneNr;
public:
    Staff(int databaseId, string name = "?", string mail = "?", string ssn="", string task = "?", string phoneNr = "?");
    virtual ~Staff();
    string getTask() const;
    string getPhoneNr() const;
    void setTask(string task);
    void setPhoneNr(string phoneNr);
    void setSsn(string ssn);
    string toStringSpecific() const;
    Staff *clone() const;
    string toSqlSaveStringSpecific() const;
};
#endif
