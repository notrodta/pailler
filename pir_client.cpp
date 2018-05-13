// g++ pir_client.cpp -o pir_client
// ./pir_client z1.txt z2.txt

/*
 How to run:
 open 3 terminals:
 
 terminal 1:
 g++ pir_server.cpp -o pir_server
 ./pir_server share1.txt z1.txt 100
 
 terminal 2:
 ./pir_server share2.txt z2.txt 200
 
 terminal 3:
 g++ pir_client.cpp -o pir_client
 ./pir_client z1.txt z2.txt
*/

/*
 using ntl:
 g++ -g -O2 pir_client.cpp -o pir_client -lntl -lgmp -lm
 ./pir_client
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <NTL/ZZ.h>
#include <assert.h>
#include <NTL/RR.h>

using namespace std;
using namespace NTL;


//check to see if a certain file exists
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

//get the z1 and z2 value from textfiles z1.txt and z2.txt
int get_z(const char *fileName)
{
    int z = 0;
    int x;
    while (1)
    {
        if (is_file_exist(fileName))
        {
            ifstream inFile;
            inFile.open(fileName);
            if (!inFile) {
                cout << "Unable to open file";
                exit(1); // terminate with error
            }
            
            while (inFile >> x){ z = x; }
            
            break;
        }
    }
    
    if( remove( fileName ) != 0 )
        perror( "Error deleting file" );
    else
        puts( "File successfully deleted" );
    
    return z;
}


//z = z1 + z2
int getAnswer(int z1, int z2)
{
    cout << "z1: " << z1 << endl;
    cout << "z2: " << z2 << endl;
    return z1 + z2;
}

//write share1 to share1.txt
void createShare1(string share)
{
    ofstream myfile;
    myfile.open ("share1.txt");
    myfile << share;
    myfile.close();
}

//write share2 to share2.txt
void createShare2(string share)
{
    ofstream myfile;
    myfile.open ("share2.txt");
    myfile << share;
    myfile.close();
}

// convert client index into binary
string convert_index_to_binary(int client_index)
{
    string bin = "";
    int num = client_index;
    int rem;
    
    while (num != 0)
    {
        rem = num % 2;
        num /= 2;
        cout << rem << endl;
        bin = to_string(rem) + bin;
        //bin.set(i,rem);
    }
    return bin;
}

string encrypt_client_index_binary()
{
    
    
}


int main (int argc, char** argv) {
//    g++ pir_client.cpp -o pir_client
//    ./pir_client
    cout << convert_index_to_binary(6)<<endl;

    
//------------------------------------------
    // Test with hardcoded values:
//    createShare1("-1");
//    createShare2("2");
//
//    cout << getAnswer(get_z(argv[1]), get_z(argv[2])) << endl;
//
    return 0;
}
//TODO: add in encryption of client index

/*
1. convert index i into binary
2. convert sk into binary
 
 */




