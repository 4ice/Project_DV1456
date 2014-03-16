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
public:
    People(string name = "?", string mail = "?", string ssn="0");
    virtual ~People();
    string getName() const;
    string getMail() const;
    string getSsn() const;
    void setName(string name);
    void setMail(string mail);
    void setSsn(string ssn);
    string toString() const;
    virtual string toStringSpecific() const=0;
    virtual People *clone() const=0;
    virtual string toSqlSaveStringSpecific() const=0;
};
#endif
