#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <map>

using namespace std;

using stringMap = map<string, int>;

void printMap(const stringMap& p_map)
{
    for (auto & s : p_map)
    {
        cout << s.first << " " << s.second << endl;
    }
}

int main()
{
    string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit by Bob";
    string banned = "hit";

    istringstream iss(paragraph);

    stringMap read {};
    string key;
    while (iss >> key)
    {
        if (key != banned)
        {
            ++read[key];
        }
    }
    int max = 0;
    for (const auto & item : read)
    {
        if (item.second > max)
        {
            key = item.first;
            max = item.second;
        }
    }
    printMap(read);
    cout << "max : " << key << "(" << read[key] << ")" << endl;

    return 0;
}

