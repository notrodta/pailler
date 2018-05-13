
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <fstream>
using namespace std;

//To compile use g++ t2.cpp -o t2 -std=c++11
//execute ./t2
int main()
{
    string line;
    string str;
    ifstream myfile ("commands.pal");
    
    if (!myfile) {
        cout << "unable to open file";
        return false;
    }
    
    while (getline (myfile, line))
    {
        str += line;
        str += " ";
    }
    
    cout << "line: " << str << endl;
    
    //string str = " maybe 3 * 6 2578*20+";
    
    // Tokens
    vector<pair <string, string>> v
    {
        {"[0-9]+" , "NUMBERS"} ,
        {"[a-z]+" , "IDENTIFIERS"},
        {"\\*|\\+", "OPERATORS"}
        //still need store and load
    };
    
    string reg;
    
    for(const auto x : v)
        reg += "(" + x.first + ")|";
    
    reg.pop_back();
    
    cout << "Tokens: " << reg << endl;
    
    regex re(reg);
    
    sregex_iterator words_begin = sregex_iterator(str.begin(), str.end(), re);
    sregex_iterator words_end = sregex_iterator();
    
    for(sregex_iterator i = words_begin; i != words_end; i++)
    {
        size_t index = 0;
        
        for(index = 0; index < i->size(); ++index)
            if(!i->str(index + 1).empty())
                break;
        
        cout << i->str() << " " << v[index].second << endl;
    }
    return 0;
}