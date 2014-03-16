#ifndef PERSONNAMESSN_H
#define PERSONNAMESSN_H

#include <string>

using namespace std;

class PersonNameSsn
{
private:
    string name;
    string ssn;
public:
    PersonNameSsn(string name = "", string ssn = "");
    virtual ~PersonNameSsn();
    string getName() const;
    string getSsn() const;
    void setName(string name);
    void setSsn(string ssn);
};

#endif // PERSONNAMESSN_H
