#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>

using namespace std;

class People
{
private:
    string name;
    string mail;
    string ssn;
    int databaseId;
public:
    People(string name = "?", string mail = "?", string ssn="0", int databaseId=-1);
    virtual ~People();
    string getName() const;
    string getMail() const;
    string getSsn() const;
    int getDatabaseId() const;
    void setName(string name);
    void setMail(string mail);
    void setSsn(string ssn);
    void setDatabaseId(int databaseId);
    string toString() const;
    virtual string toStringSpecific() const=0;
    virtual People *clone() const=0;
    virtual string toSqlSaveStringSpecific() const=0;
    virtual string toSqlDeleteStringSpecific() const=0;
};
#endif
