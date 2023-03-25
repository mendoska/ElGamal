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

string decimalToBinary(int dec){
   string binary;
    while (dec!=0 ){
        binary =(dec % 2 == 0 ? "0":"1") +binary;
        dec = dec/2;
    }
    while(binary.length()<4){
        binary = "0" + binary;
    }
    return binary;
}



//Miller_Rabin Probabilistic Primality Test
int millerRabin(int n, int t){

    //instances that are always prime numbers
    if (n == 1 || n == 2 || n == 3){
      return true;
    }
//#1
//note: maybe store n-1 & n-2 in their own variable to keep n
   //temp variable to keep original n

    int nMinus1 = n-1;
    //exponent of 2
   int s = 0;
   //odd number multiplied by 2^s
   int r = 0;

  while (nMinus1 != 0){
   //if n is divisible by 2
   //increment s
    if (nMinus1%2 == 0){
        nMinus1 = nMinus1/2;
        s++;
    }
    //when is n no longer divisible by 2 that means it will be r
    else {
        r= nMinus1;
    }
  }

  int nMinus2 = n -2;
  //returning
  //for loop
  for (int i =1; i <= t; i++){
    //2.1
    //choose a random int a,
      // Create a random number generator using the Mersenne Twister algorithm
       std::mt19937 rng(std::random_device{}());
   // 2<=a<=n-2
       int lower_bound = 2;
       int upper_bound = nMinus2 ;

       // Create a uniform integer distribution object with the given bounds
       std::uniform_int_distribution<int> dist(lower_bound, upper_bound);

       // Generate a random number within the given bounds
       int a = dist(rng);

       return 0;

  }

    return n;
}


int SSM(int a, int k, int n){
    int b = 0;
    //using 4 as t for the sake of implementation
    int t = 4;
//#1
    if (k == 0) {
        b=1;
        return b;
    }

//converting k to binary
    string binK = decimalToBinary(k);
//#2
    int capA = a;
//#3
    if (binK[0] == '1'){
        b = a;
    }
//#4 for loop
    for (int i = 1; i<=t; i++){
        //4.1
        capA = ((capA * capA) % n);
        //4.2
        if (binK[i] == '1'){
            b = ((capA *b)%n);
        }
    }
//#5
    return b;
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




////test my miller-rabin
//    //exponent of 2
//    int s = 0;
//    //odd number multiplied by 2^s
//    int r = 0;
//    int n = 887;

//    n = n-1; //16

//    while (n != 0){
//     //if n is divisible by 2
//    //increment s
//     if (n%2 == 0){
//         n = n/2;
//         s++;
//     }
//     //when is n no longer divisible by 2 that means r will be n's left over
//     else {
//         r = n;
//         break;
//     }
//    }
