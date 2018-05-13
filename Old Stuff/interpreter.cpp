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
            cout << tokens[i][j] << " ";
        //cout << endl;
    }
    cout << endl;
  

	return 0;
}



/*TODO:
 
 RMS:
 • Load an input into memory: (id, yˆj ← wˆi).
 • Add values in memory: (id, yˆk ← yˆi + yˆj ).
 • Multiply value in memory by an input value: (id, yˆk ← wˆi · yˆj ). 
 • Output value from memory, as element of Zβ: (id,β,Oˆj ← yˆi).
 
 
 if current token read is add or multiply:
 read next two token, check that it is a positive integer
 call the actual function in paillier script
 
 if current token read is save or load:
 read only the next token, check that the value is a positive integer
 
 
 
 save number
 add number1 number2
 mul number 1 number 2
 load number
 
 
 */


