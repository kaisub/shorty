/**
Read from file, sort words, write to other file.
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>

using namespace::std;

const string DEF_FILENAME_INPUT = "fileIn.txt";
const string DEF_FILENAME_OUTPUT = "fileOut.txt";

struct Settings
{
    string fileNameIn {DEF_FILENAME_INPUT};
    string fileNameOut {DEF_FILENAME_OUTPUT};
    
    Settings() {
        cout << "Settings constructor" << endl;
    };
    Settings(const Settings & p_in) {
        cout << "Settings copy constructor" << endl;
        Settings set {};
        set.fileNameIn = p_in.fileNameIn;
        set.fileNameOut = p_in.fileNameOut;
    }
};

string getFileName(const string & p_defName)
{
    string name {};
    getline(cin, name);
    auto pos = name.find(' ');
    if (pos != string::npos)
    {
        name.erase(pos);
    }
    if (name.empty())
    {
        return p_defName;
    }
    return name;
}

Settings assignFilesName()
{
    Settings inSet {};

    cout << "Write input file name (def=" << DEF_FILENAME_INPUT << ") : " << endl;
    inSet.fileNameIn = getFileName(DEF_FILENAME_INPUT);
    cout << "Selected input name: " << inSet.fileNameIn << endl;

    cout << "Write output file name (def=" << DEF_FILENAME_OUTPUT << ") : " << endl;
    inSet.fileNameOut = getFileName(DEF_FILENAME_OUTPUT);
    cout << "Selected input name: " << inSet.fileNameOut << endl;

    return inSet;
}

void createTestInFile(const string & p_fileName)
{
    ofstream os {p_fileName};
    ostream_iterator<string> oi {os, "\n"};
    *oi = "woz";
    *oi = "nos";
    *oi = "abra";
    *oi = "cepelia";
    *oi = "dupa";
    *oi = "slonik";
    *oi = "zaba";
    *oi = "misio";
    *oi = "balonik";
}

int main()
{
    Settings settings = assignFilesName();
    createTestInFile(settings.fileNameIn);
 
    ifstream is {settings.fileNameIn};
    istream_iterator<string> ii {is};
    istream_iterator<string> ieos {};

    ofstream os {settings.fileNameOut};
    ostream_iterator<string> oi {os, "\n"};  // put \n after each output

    vector<string> vect {ii, ieos};
    sort(vect.begin(), vect.end());

    copy(vect.begin(), vect.end(), oi);

    return !is.eof() || !os;
}


