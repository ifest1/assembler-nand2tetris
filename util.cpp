#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> split(string s, string delimiter) 
{
    size_t pos_start = 0, pos_end;
    string token;
    vector<string> res;

    while (true) 
    {
        pos_end = s.find(delimiter, pos_start);
        token = s.substr(pos_start, pos_end - pos_start);
        res.push_back(token);
        pos_start = pos_end + delimiter.length();
        
        if (pos_end == string::npos) break;
    }

    return res;
}


void del_char(string &str, char c) 
{
   str.erase(remove(str.begin(), str.end(), c), str.end());
   str.erase(remove(str.begin(), str.end(), '\r'), str.end());
}