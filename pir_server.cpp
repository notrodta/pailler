// g++ pir_server.cpp -o pir_server
// ./pir_server share1.txt z1.txt 100
// ./pir_server share2.txt z2.txt 200

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

//check to see if a certain file exists
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

//read from the file "share1" to get share
int getShare(const char *fileName)
{
    int share = 0;
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
            
            while (inFile >> x){ share = x; }
            
            break;
        }
    }
    
    if( remove( fileName ) != 0 )
        perror( "Error deleting file" );
//    else
//        puts( "File successfully deleted" );
    return share;
}

// returns the number of bits needed for the number x
int getNumOfBitsForNum(int x)
{
    return floor(log2(x)) + 1;
}

//THIS IS WRONG! REDO
//returns true if the databse index is the client's index
//clientIndex needs to be encryted
bool isClientIndex(int clientIndex, int databaseIndex, int share)
{
    int client_size = getNumOfBitsForNum(clientIndex);
    int db_size = getNumOfBitsForNum(databaseIndex);
    
    if (client_size != db_size){return false;}

    std::bitset<64> client(clientIndex);
    std::bitset<64> db(databaseIndex);
    int n = 1;

    for (int i = 0; i < client_size; i++)
    {
        if (db[i] == 0) {n = n * (share-client[i]);}
        else { n *= client[i];}
    }
    return n == 1;
}

//calculating z1 or z2 to send back to client
int calculate_z()
{
    
}

//write z1 or z2 to textfile
void submitZ(const char *fileName, int z)
{
    ofstream myfile;
    myfile.open (fileName);
    myfile << z;
    myfile.close();
}

//write z1 or z2 to textfile, uses command line arguements for both parameters
void submitZtest(const char *fileName, const char *z)
{
    ofstream myfile;
    myfile.open (fileName);
    myfile << z;
    myfile.close();
}


//bool getValueFromDB(int arr[], int arrSize)
//{
//    int n = 0;
//
//    for (int i = arrSize - 1; i >= 0; i--)
//    {
//        cout << arr[i] << endl;
//    }
//    return false;
//}


// g++ pir_server.cpp -o pir_server
// ./pir_server share1.txt z1.txt 100
// ./pir_server share2.txt z2.txt 200

int main (int argc, char** argv) {
//    int balance[5] = {1,0,0,1,1};
//    int len = sizeof(balance)/sizeof(balance[0]);
//    cout << len <<endl;
//    getValueFromDB(balance,len);

    cout << getShare(argv[1]) << endl;
    submitZtest(argv[2], argv[3]);
    
    
    
    cout << "___________" <<endl;
//
//    cout << isClientIndex(3,3,1) <<endl;
//    cout << isClientIndex(3,4,1) <<endl;
//    cout << getNumOfBitsForNum(10) << endl;

	return 0;
}




