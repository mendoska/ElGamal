/*
Alexander Mendoza
Z23435963
https://github.com/mendoska/ElGamal
CIS5371 Cryptography
ASSIGNMENT #3 EL GAMAL ALGORITHM
 */


#include <iostream>
#include <string>
#include <bitset>
#include <random>
#include <vector>
using namespace std;

//Miller_Rabin Probabilistic Primality Test
int millerRabin(int n, int t){

    //instances that are always prime numbers
    if (n == 1 || n == 2 || n == 3){
      return true;
    }
//#1
   //exponent of 2
   int s;
   //odd number multiplied by 2^s
   int r = 0;

   n = n-1;

    //if n is divisible by 2
   //increment s
    if (n%2 == 0){
        n = n/2;
        s++;
    }
    //when is n no longer divisible by 2 that means it will be r
    else {
        n = r;
    }


    return n;
}




int main()
{
//    int keySize = 0;
//    string plainText = "";

//    //plaintxt
//    cout << "Please enter your plaintext message";
//    getline(cin,plainText);

//    //bits
//    cout<<"Please enter your keysize by number of bits you would like to use \n";
//    cin >>keySize;

//test my miller-rabin
    //exponent of 2
    int s = 0;
    //odd number multiplied by 2^s
    int r = 0;
    int n = 887;

    n = n-1; //16

    while (n != 0){
     //if n is divisible by 2
    //increment s
     if (n%2 == 0){
         n = n/2;
         s++;
     }
     //when is n no longer divisible by 2 that means r will be n's left over
     else {
         r = n;
         break;
     }
    }

     cout<<"Break";


    return 0;
}



////turns decimal to binary
//std::string decimalToBinary(int dec){
//    std::string binary;

//    while (dec!=0 ){
//        binary =(dec % 2 == 0 ? "0":"1") +binary;
//        dec = dec/2;
//    }
//    while(binary.length()<4){
//        binary = "0" + binary;
//    }
//    return binary;
//}

//int binaryToDecimal(std::string binary){
//    int decimal = 0;
//    int counter = 0;
//    int size = binary.length();

//    for (int i = size-1; i>=0; i--){
//        if (binary[i] == '1'){
//            decimal += pow(2,counter);
//        }
//        counter++;
//    }
//    return decimal;
//}
