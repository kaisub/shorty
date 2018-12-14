#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;


int main(int, char *argv[])
{
    ifstream myFile(argv[1]);

    int n{0}, q{0};
    myFile >> n >> q;
    myFile.ignore(numeric_limits<streamsize>::max(), '\n');

    map<string, string> lib{};

    string input{}, tag, value;
    for(int i(0); i < n; ++i)
    {
        getline(myFile, input);
        stringstream ss(input);
        string tmp{}, keyName{};
        while (ss >> tmp) {
            if (tmp[0] == '<') {
                if (tmp[1] == '/') {
                    string tagClose = tmp.substr(2, tmp.length() - 3);
                    int len = static_cast<int>(tag.length() - tagClose.length() - 1);
                    if (len < 0) {len = 0;}
                    tag.erase(static_cast<size_t>(len));
                }
                else {
                    if(!tag.empty()) {
                        tag += '.';
                    }
                    if (tmp[tmp.length() - 1] == '>') {
                        tag += tmp.substr(1, tmp.length() - 2);
                    }
                    else {
                        tag += tmp.substr(1);
                    }
                }
            }
            else if (tmp == "=") {
                continue;
            }
            else if (tmp[0] == '\"') {
                size_t cutEnd = 2;
                if (tmp[tmp.length() - 1] == '>') {
                    ++cutEnd;
                }
                lib[tag + '~' + keyName] = tmp.substr(1, tmp.length() - cutEnd);
            }
            else {
                keyName = tmp;
            }
        }
    }
    /*for (auto it = lib.begin(); it != lib.end(); ++it) {
        cout << it->first << ", " << it->second << '\n';
    }
    cout << endl;*/

    for(int i(0); i < q; ++i)
    {
        getline(myFile, input);
        if (input.rfind('~') == string::npos) {
            input[input.rfind('.')] = '~';
        }
        auto iter = lib.find(input);
        if (iter != lib.end()) {
            cout << iter->second << endl;
        }
        else {
            cout << "Not Found!" << endl;
        }
    }

    return 0;
}

