// g++ interpreter.cpp -o a
// ./a

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

/*
	create a new vector that stores each word/num in myLine
*/


int main () {

	vector<string> commands;
	commands.push_back("add");
	commands.push_back("multiply");
	commands.push_back("load");
	commands.push_back("save");

	string line;
	ifstream myfile ("commands.pal");
  
	vector<string> myLine;
  
  
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			line += " ";
			myLine.push_back(line);
		}
    myfile.close();
	}
	else cout << "Unable to open file"; 
	
	/*
	for(int i = 0; i<myLine.size(); i++)
	{
		cout<<myLine[i]<<endl;
	}*/
	
	
	vector<vector<string> > tokens;
	for(int i = 0; i<myLine.size(); i++)
	{
		string s = "";
		for(int j = 0; j<myLine[i].size(); j++)
		{
			//cout<<myLine[i][j]<<endl;
			if (myLine[i][j] != ' ')
			{
				s += myLine[i][j];
				//cout<< "found a space" << endl;
			}
			else
			{
				vector<string> word;
				word.push_back(s);
				tokens.push_back(word);
				s = "";
			}
		}
	}
	
	
	// Read token from tokens list
    for(int i = 0; i < tokens.size(); ++i)
    {
        for(int j = 0; j < tokens[i].size(); ++j)
            cout << tokens[i][j];
        cout << endl;
    }	
  

	return 0;
}