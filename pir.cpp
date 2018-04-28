// g++ pir.cpp -o pir
// ./pir

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;


// returns the number of bits needed for the number x
int getNumOfBitsForNum(int x)
{
    return floor(log2(x)) + 1;
}

//returns true if the databse index is the client's index
bool isClientIndex(int clientIndex, int databaseIndex)
{
    int client_size = getNumOfBitsForNum(clientIndex);
    int db_size = getNumOfBitsForNum(databaseIndex);
    
    if (client_size != db_size){return false;}

    std::bitset<64> client(clientIndex);
    std::bitset<64> db(databaseIndex);
    int n = 1;

    for (int i = 0; i < client_size; i++)
    {
        if (db[i] == 0) {n = n * (1-client[i]);}
        else { n *= client[i];}
    }
    return n == 1;
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


int main () {
//    int balance[5] = {1,0,0,1,1};
//    int len = sizeof(balance)/sizeof(balance[0]);
//    cout << len <<endl;
//    getValueFromDB(balance,len);
    
    cout << "___________" <<endl;
    
    cout << isClientIndex(3,3) <<endl;
    cout << isClientIndex(3,4) <<endl;
    cout << getNumOfBitsForNum(10) << endl;

	return 0;
}




