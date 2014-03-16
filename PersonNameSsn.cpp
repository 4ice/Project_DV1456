#include "PersonNameSsn.h"

PersonNameSsn::PersonNameSsn(string name, string ssn)
{
    this->name = name;
    this->ssn = ssn;
}
PersonNameSsn::~PersonNameSsn()
{
}
string PersonNameSsn::getName() const
{
    return this->name;
}
string PersonNameSsn::getSsn() const
{
    return this->ssn;
}
void PersonNameSsn::setName(string name)
{
    this->name = name;
}
void PersonNameSsn::setSsn(string ssn)
{
    this->ssn = ssn;
}
