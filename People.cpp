#include "People.h"
#include <sstream>

People::People(string name, string mail, string ssn)
{
    this->name = name;
    this->mail = mail;
    this->ssn = ssn;
}
People::~People()
{
}
string People::getName() const
{
    return this->name;
}
string People::getMail() const
{
    return this->mail;
}
string People::getSsn() const
{
    return this->ssn;
}
void People::setName(string name)
{
    this->name = name;
}
void People::setMail(string mail)
{
    this->mail = mail;
}
void People::setSsn(string ssn)
{
    this->ssn = ssn;
}
string People::toString() const
{
    stringstream ss;
    ss << "Name: " << this->name << "\nMail: " << this->mail << "\n" << toStringSpecific() << "Ssn: " << this->ssn << endl;
    return ss.str();
}
