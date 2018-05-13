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
g++ -g -O2 pir_client.cpp paillier.cpp -o pir_client -lntl -lgmp -lm
 g++ -g -O2 pir_client.cpp paillier.cpp data.cpp -o pir_client -lntl -lgmp -lm
 g++ -std=c++11 -g -O2 pir_client.cpp paillier.cpp data.cpp utility.cpp -o pir_client -lntl -lgmp -lm

 ./pir_client
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <NTL/ZZ.h>
#include <assert.h>
#include "paillier.h"
#include "data.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

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

// share1, share lambda, input1, inputs
// creating share1 and share lambda into input types with value 0s. bits = vector of 512 0s and modulus = 0
void sendToServer(ZZ share1, ZZ lambda, vector<Input> inputs, Paillier p, const char *fileName)
{
    Paillier paillier = p;
    
    ofstream myfile;
    myfile.open (fileName);
    
    //writing share of 1
    myfile << "{ ";
    myfile << share1 << " ";
    myfile << "0 ";
    for (int i = 0; i < 512; i++)
    {
        myfile << "0 ";
    }
    myfile << "}" << '\n';
    
    //writing share of lambda
    myfile << "{ ";
    myfile << lambda << " ";
    myfile << "0 ";
    for (int i = 0; i < 512; i++)
    {
        myfile << "0 ";
    }
    myfile << "}" << '\n';
    
    //writing input1
    ZZ value = paillier.encrypt(ZZ(1));
    ZZ modulus = p.getModulus();
    vector<ZZ> bits = paillier.encryptBits(value);
    
    myfile << "{ ";
    myfile << value << " ";
    myfile << modulus << " ";
    
    for (int i = 0; i < bits.size(); i++)
    {
        myfile << bits[i] << " ";
    }
    
    myfile << "}" << '\n';
    
    //writing inputs
    for(int i = 0; i < inputs.size(); i++)
    {
        myfile << "{ ";
        myfile << paillier.encrypt(inputs[i].value) << " ";
        myfile << inputs[i].modulus << " ";
        
        vector<ZZ> eb = paillier.encryptBits(ZZ(inputs[i].value));
        
        for (int x  = 0; x < eb.size(); x++)
        {
            myfile << eb[x] << " ";
        }
        myfile << "}" << '\n';
    }
    
    myfile.close();
}

//creates a textfile containing share1 of 1
void sendShare1(ZZ share)
{
    ofstream myfile;
    myfile.open ("share1.txt");
    myfile << share;
    myfile.close();
}

//creates a textfile containing share2 of 1
void sendShare2(ZZ share)
{
    ofstream myfile;
    myfile.open ("share2.txt");
    myfile << share;
    myfile.close();
}

//creates a textfile containing share1 of lambda
void sendLambda1(ZZ share)
{
    ofstream myfile;
    myfile.open ("lambda1.txt");
    myfile << share;
    myfile.close();
}

//creates a textfile containing share2 of lambda
void sendLambda2(ZZ share)
{
    ofstream myfile;
    myfile.open ("lambda2.txt");
    myfile << share;
    myfile.close();
}


//create text file to send an input object of value 1
void sendInput1(Paillier p)
{
    Paillier paillier = p;
    
    ZZ value = paillier.encrypt(ZZ(1));
    ZZ modulus = p.getModulus();
    vector<ZZ> bits = paillier.encryptBits(value);
    
    ofstream myfile;
    myfile.open ("input1.txt");
    myfile << "{ ";
    myfile << value << " ";
    myfile << modulus << " ";
    
    for (int i = 0; i < bits.size(); i++)
    {
        myfile << bits[i] << " ";
    }
    
    myfile << "}";
    
    myfile.close();
}

//create a text file to store inputs
void sendInputs(vector<Input> inputs)
{
    ofstream myfile;
    myfile.open ("inputs.txt");
    
    Paillier paillier(512);
    
    for(int i = 0; i < inputs.size(); i++)
    {
        myfile << "{ ";
        myfile << paillier.encrypt(inputs[i].value) << " ";
        myfile << inputs[i].modulus << " ";
        
        vector<ZZ> eb = paillier.encryptBits(ZZ(inputs[i].value));
        
        for (int x  = 0; x < eb.size(); x++)
        {
            myfile << eb[x] << " ";
        }
        myfile << "}" << '\n';
    }
    myfile.close();
}

// create shares of one
vector<ZZ> createSharesOfOne(ZZ lambda)
{
    vector<ZZ> shares;
    
    srand(time(0));  // Initialize random number generator.
    ZZ share1 = RandomBnd(lambda);
    ZZ share2 = ZZ(1-share1);
    shares.push_back(share1);
    shares.push_back(share2);
    return shares;
}

// creates shares of lambda
vector<ZZ> createSharesOfLambda(ZZ lambda)
{
    vector<ZZ> shares;
    
    srand(time(0));  // Initialize random number generator.
    ZZ share1 = RandomBnd(lambda);
    ZZ share2 = ZZ(lambda-share1);
    shares.push_back(share1);
    shares.push_back(share2);
    return shares;
}

////ADAM FUNCTION
vector<bool> _ZZToBits_(ZZ number) {
    long numBytes = NumBytes(number);
    unsigned long numBits = numBytes * 8;
    vector<bool> bits;

    unsigned char * bytes = new unsigned char[numBytes];
    BytesFromZZ(bytes, number, numBytes);
    unsigned char * bytesEnd = bytes + numBytes;
    for (unsigned char * byte = bytes; byte != bytesEnd; byte++) {
        for (int i = 0; i < 8; i++) {
            bits.push_back(((*byte) >> i) & 1);
        }
    }
    delete bytes;
    return bits;
}

// convert client index into binary
vector<bool> convert_index_to_binary(ZZ client_index)
{
    return _ZZToBits_(client_index);
}

// creates a vector of inputs from client index binary
vector<Input> createInputs(vector<bool> index_binary, Paillier p)
{
    vector<bool> b = index_binary;
    vector<Input> inputs;

    Paillier paillier = p;

    for(int i = 0; i < b.size(); i++)
    {
        vector<ZZ> z = paillier.encryptBits(ZZ(b[i]));
        inputs.push_back(Input(ZZ(b[i]), z, paillier.getModulus()));
    }
    
    
    return inputs;
}


int main (int argc, char** argv) {
    
//    int i;
//    cout << "Please Enter Client Index: ";
//    cin >> i;
//
//    while (cin.fail()) {
//        cout << "Error Has Occurred. Please Enter Client Index: ";
//        cin.clear();
//        cin.ignore(256,'\n');
//        cin >> i;
//    }
//
//    cout << "You have entered: " << i << endl;
//    cout << "Please Wait..." << endl;
//
//
//    ZZ client_index = ZZ(i);
    

    Paillier p = Paillier(512);
    
    
    
    vector<Input> inputs = createInputs(convert_index_to_binary(ZZ(4)), p);
    //sendInputs(createInputs(convert_index_to_binary(ZZ(client_index)), p));
    
    vector<ZZ> oneShare = createSharesOfOne(p.getLambda());
    vector<ZZ> lambdaShare = createSharesOfLambda(p.getLambda());

    sendToServer(oneShare[0], lambdaShare[0], inputs, p, "server1.txt");
    sendToServer(oneShare[1], lambdaShare[1], inputs, p, "server2.txt");
    
    cout << "Fin" <<endl;
    
    return 0;
}









