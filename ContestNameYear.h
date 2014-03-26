#ifndef CONTESTNAMEYEAR_H
#define CONTESTNAMEYEAR_H

#include <string>

using namespace std;

//A class to hold a contest name and contest year connected.
class ContestNameYear
{
private:
    string contestName;
    int contestYear;
public:
    ContestNameYear(string contestName = "", int contestYear = 0);
    ~ContestNameYear();
    string getContestName() const;
    int getContestYear() const;
    void setContestName(string contestName);
    void setContestYear(int contestYear);
};

#endif // CONTESTNAMEYEAR_H
