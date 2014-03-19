#ifndef COMPETITOR_H
#define COMPETITOR_H
#include "People.h"

class Competitor : public People
{
private:
    string gender;
    int startingNumber;
    int timeResult;
    string raceClass;
public:
    Competitor();
    Competitor(int currentYear, string name, string mail, string ssn, string gender, int startingNumber = 1, int timeResult=-1);
    virtual ~Competitor();
    int getBirthDate() const;
    string getGender() const;
    int getStartingNumber() const;
    int getTimeResult() const;
    string getRaceClass() const;
    void setGender(string gender);
    void setStartingNumber(int startingNumber);
    void setTimeResult(int timeResult);
    void setRaceClass(string raceClass);
    int age(int birthYear, int currentDate) const;
    string calculateRaceClass(int age); //Calculates the race class from the given age of the contestant
    string toStringSpecific() const;
    Competitor *clone() const;
    string toSqlSaveStringSpecific() const;
};
#endif