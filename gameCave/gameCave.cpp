#include <QString>
#include <QTextStream>
#include <time.h>
#include <vector>

using namespace std;

namespace {

QTextStream cout(stdout);
QTextStream cerr(stderr);
QTextStream cin(stdin);

const int MIN_SIZE_FIELDS = 3;
const int MAX_SIZE_FIELDS = 12;
const int OFFSET_TARGET = 4;

} // namespace

int askUserForFieldsCount()
{
    QString info = {};
    QTextStream strbuf(&info);
    strbuf << "Give fields count: (" << MIN_SIZE_FIELDS << " - " << MAX_SIZE_FIELDS <<"):";
    int val = 0;
    cout << info << endl;
    do {
        cin >> val;
        if (val >= MIN_SIZE_FIELDS && val <= MAX_SIZE_FIELDS) {
            break;
        }
        else {
            cout << info << endl;
        }
    }
    while (true);
    return val;
}

void printResults(vector<int> & p_vect)
{
}

int getRandVal(int p_fieldsCount)
{
    return (rand() % (p_fieldsCount - OFFSET_TARGET)) + rand() % p_fieldsCount;
}

int main()
{
    srand(time(0)); // randomize seed

    int fieldsCount = askUserForFieldsCount();;
    int target = getRandVal(fieldsCount);
    int cave = getRandVal(fieldsCount);
    if (target == cave) {
        cave--;
    }
    cout << "target: " << target << " cave: " << cave << endl;

//    vector<int> results = vector<int>(ROUND_SIZE);

    return 0;
}

