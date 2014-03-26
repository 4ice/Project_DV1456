#include "ContestNameYear.h"

ContestNameYear::ContestNameYear(string contestName, int contestYear)
{
    this->contestName = contestName;
    this->contestYear = contestYear;
}
ContestNameYear::~ContestNameYear()
{
}
string ContestNameYear::getContestName() const
{
    return this->contestName;
}
int ContestNameYear::getContestYear() const
{
    return this->contestYear;
}
void ContestNameYear::setContestName(string contestName)
{
    this->contestName = contestName;
}
void ContestNameYear::setContestYear(int contestYear)
{
    this->contestYear = contestYear;
}
