#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

namespace {

const int ROUND_SIZE = 6;

} // namespace

void singleDiceTossPrint(vector<int> & p_vect)
{
    int randVal_1 = rand() % ROUND_SIZE;
    int randVal_2 = rand() % ROUND_SIZE;
    randVal_1++, randVal_2++;

    p_vect[randVal_1 - 1]++;
    p_vect[randVal_2 - 1]++;
}

void printResults(vector<int> & p_vect)
{
    cout << "results:" << endl;
    for (int i = 0; i < ROUND_SIZE; i++)
    {
        cout << i + 1 << " : " << p_vect[i] << endl;
    }
}

int main(int argc,char* argv[])
{
    srand(time(0)); // randomize seed

    vector<int> results = vector<int>(ROUND_SIZE);

    for (int i = 0; i < 10; i++)
    {
        singleDiceTossPrint(results);
    }

    printResults(results);

    return 0;
}

