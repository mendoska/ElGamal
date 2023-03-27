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
//    while(binary.length()<4){
//        binary = "0" + binary;
//    }
    return binary;
}

//needed for indexing in algorithm for SSM
void reverseStr(string& str)
{
    int n = str.length();

    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++){
        swap(str[i], str[n - i - 1]);
    }
}


int randNumGen(int lower_bound, int upper_bound){
      // create a random number generator using the Mersenne Twister algorithm
       std::mt19937 rng(std::random_device{}());

       // create a uniform integer distribution object with the given bounds
       std::uniform_int_distribution<int> dist(lower_bound, upper_bound);

       // generate a random number within the given bounds
       return dist(rng);
}



//a - base k - power n- for mod
//output: a^k mod n

int SSM(int a, int k, int n){

    int b = 0;
    int t = 4;  //using 4 as t for the sake of implementation
//#1
    if (k == 0) {
        b=1;
        return b;
    }

//converting k to binary
    string binK = decimalToBinary(k);
    reverseStr(binK);

//#2
    int capA = a;
//#3
//issue found -> need to go to the end of the array due to algorithm having k_0 be the last digit
//solved by reversing string

    if (binK[0] == '1'){
        b = a;
    }
//#4 for loop
    for (int i = 1; i<=t; i++){
        //4.1
        capA = (capA * capA)%n;
        //4.2
        if (binK[i] == '1'){
            b = (capA *b)%n;
        }
    }
//#5
    return b;
}


//issue with  79
//Miller_Rabin Probabilistic Primality Test
string millerRabin(int n, int t){
    string composite = "composite";
    string prime = "prime";

    //instances that are always prime numbers
    if (n == 1 || n == 2 || n == 3){
      return prime;
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
        break;
    }
  }
  nMinus1 = n-1;
  int nMinus2 = n -2;
  //returning
  //for loop
  for (int i =1; i <= t; i++){
    int j;
    //2.1 2<=a<=n-2
       int a = randNumGen(2, nMinus2);
    //2.2 y = a^r (mod n) using SSM
       int y = SSM(a,r,n);
    //2.3
       if (y != 1 && y != nMinus1){
          j =1;
           while (j <= s-1 && y != nMinus1){
                  y = ((y*y)%n);
                  if (y ==1){
                      return composite;
                  }
                  j++;
            }
           if(y!= nMinus1){
               return composite;
           }
       }
  }
    //#3
    return prime;
}



//implementation of elGamal
void elGamal (){


   //PRIVATE KEY
   // 1. GENERATE A LARGE RANDOM PRIME "p"

   //note: you will put place holder values for random num gen
   // but you will change these numbers based on bit size from user

   string test = "";
   int p;

   //create random number until prime is found

   while(test != "prime"){
    p = randNumGen(0,1000);
    test = millerRabin(p,4);
    }

   //for now i will be providing a generator variable of 2
   //link either crypto ++ or hardcoded function to find generator alpha
   int alpha =2;

   //1<=a<=p-2
   int a = randNumGen(1,p-2);

   //alpha ^a mod p using SSM

   int alphaPowA = SSM(alpha,a,p);

 //*****************
 //start encryption
 //*****************

    //1a
    //public keys
    cout<<"Your public keys are as follows: " << "p: "<< p << "alpha: " <<alpha
    << "alpha ^a mod p:" <<alphaPowA<<endl;
    cout<< "Private key (a): "<< a;

    //1b
    //represent message "m" as an integer

    //for implementation v.1 I will set a value for message
    //later i will create method to get integer value

    int m =235;

    //1c
    //select random integer
    int k = randNumGen (1,p-2);


    //1d
    //compute gamma = alpa^k mod p
    int gamma = SSM(alpha,k,p);

    //compute delta = m * (alpha^a)^k mod p

    int delta = m *(SSM(alphaPowA,k,p)%p);

    //send ciphertext

    cout<<"The ciphertext is: "<<gamma<< " "<<delta;

  //*****************
 //start decryption
 //*****************


    //2a use the private-key a to computer gamma ^ p-1-a mod p

    //declare p-1-a

    int pMinus1A = ((p-1) -a);

    int gammaPMinus1A = SSM(gamma,pMinus1A,p);

    //2b recovering "m" private key gamma^-a * delta mod p

    //getting message again
    int decMessage = (gammaPMinus1A *delta)%p;

    cout<<"Your original message"<<m<<endl;
    cout<<"Decrypted message (original message)"<<decMessage;

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


    string str = millerRabin(7919,4);
   cout << str<<endl;


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
