#include <boost/assign.hpp>

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <unordered_map>

void UserSaidA(std::vector<int>& vec)
{
    using namespace boost::assign;
    vec += 1, 3, 5;
}

void UserSaidB(std::vector<int>& vec)
{
    using namespace boost::assign;
    vec += 2, 4, 6;
}

void Print(const std::vector<int>& vec)
{
    for (int i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main()
{
    using namespace boost::assign;

    std::vector<int> ints;
    ints += 0, 100;

    std::cout << "What do you want (A, B, X) : ";
    char user;
    std::cin >> user;

    bool isA = user == 'A' || user == 'X';
    bool isB = user == 'B' || user == 'X';
    if (isA) UserSaidA(ints);
    if (isB) UserSaidB(ints);

    std::sort(ints.begin(), ints.end());
    Print(ints);

    std::unordered_map<int, std::string> lookupMonthsToString;
    insert(lookupMonthsToString)
        (1, "JAN")(2, "FEB")(3, "MRZ")(4, "APR")
        (5, "MAY")(6, "JUN")
        ;
    std::cout << "The Month: ";
    int month;
    std::cin >> month;
    std::cout << "The " << month << "'st month is " << lookupMonthsToString[month] << std::endl;
}
