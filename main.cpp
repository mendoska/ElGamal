/*
Alexander Mendoza
Z23435963
https://github.com/mendoska/ElGamal
CIS5371 Cryptography
ASSIGNMENT #3 EL GAMAL ALGORITHM
 */


#include <iostream>
#include <string>
#include <random>



using namespace std;

string decimalToBinary(long long dec){
   string binary;
    while (dec!=0 ){
        binary =(dec % 2 == 0 ? "0":"1") +binary;
        dec = dec/2;
    }
    return binary;
}

string generateBinary (int numBits){
    string binaryStr;

    for (int i = 0; i<numBits; i++){
        binaryStr += ((rand()%2 == 0 ) ? '0':'1');
    }
    return binaryStr;
}
//makes binary string based on number of bits
string intToBinary(int n, int numBits) {
    string binaryStr;
    for (int i = numBits - 1; i >= 0; i--) {
        ///<< left bit shift 1<<i, shifts binary representation of 1 to the left by i positions
        binaryStr += ((n & (1 << i)) ? '1' : '0');
    }
    return binaryStr;
}

long long binaryToDecimal(string binary){
    long long decimal = 0;
    long long counter = 0;
    long long size = binary.length();

    for (long long i = size-1; i>=0; i--){
        if (binary[i] == '1'){
            decimal += pow(2,counter);
        }
        counter++;
    }
    return decimal;
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


long long randNumGen(long long lower_bound, long long upper_bound){
      // create a random number generator using the Mersenne Twister algorithm
       std::mt19937 rng(std::random_device{}());

       // create a uniform integer distribution object with the given bounds
       std::uniform_int_distribution<long long> dist(lower_bound, upper_bound);

       // generate a random number within the given bounds
       return dist(rng);
}




//a - base
//k - power
//n- for mod
//output: a^k mod n

long long SSM(long long a, long long k, long long n){

    long long b = 1;
    int t = 4;  //using 4 as t for the sake of implementation
//#1
    if (k == 0) {
        return b;
    }

//converting k to binary
    string binK = decimalToBinary(k);
    reverseStr(binK);

//#2
    long long capA = a;
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


//issue with  #79 and a few other numbers
//Miller_Rabin Probabilistic Primality Test
string millerRabin(long long n, int t){
    string composite = "composite";
    string prime = "prime";

    //instances that are always prime numbers
    if (n == 1 || n == 2 || n == 3){
      return prime;
    }
//#1
//note: maybe store n-1 & n-2 in their own variable to keep n
//temp variable to keep original n

    long long nMinus1 = n-1;
    //exponent of 2
    long long s = 0;
   //odd number multiplied by 2^s
    long long r = 0;

  while (nMinus1 != 0){
   //if n is divisible by 2
   //increment s
    if (nMinus1%2 == 0){
        nMinus1 = (nMinus1)/2;
        s++;
    }
    //when is n no longer divisible by 2 that means it will be r
    else {
        r= nMinus1;
        break;
    }
  }
  nMinus1 = n-1;
long long nMinus2 = n -2;
  //returning
  //for loop
  for (int i =1; i <= t; i++){
    int j;
    //2.1 2<=a<=n-2
      long long a = randNumGen(2, nMinus2);
    //2.2 y = a^r (mod n) using SSM
      long long y = SSM(a,r,n);
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
void elGamal (int bits, string plainText){


   //PRIVATE KEY
   // 1. GENERATE A LARGE RANDOM PRIME "p"

   //note: you will put place holder values for random num gen
   // but you will change these numbers based on bit size from user


   //create random number until prime is found

   //declaring variables
   string test = "";
    long long p;
   string binP;

  while(test != "prime"){
   //generates binary from bits size input
    binP= generateBinary(bits);

   //turns binary to decimal
   p = binaryToDecimal(binP);

   //test if prime is found
   test = millerRabin(p,4);
  }


   //for now i will be providing a generator variable of 2
   //link either crypto ++ or hardcoded function to find generator alpha
    long long alpha =2;

   //1<=a<=p-2
    long long a = randNumGen(1,p-2);

   //alpha ^a mod p using SSM

    long long alphaPowA = SSM(alpha,a,p);

 //*****************
 //start encryption
 //*****************

    //1a
    //public keys
    cout<<"Your public keys are as follows: \n" << "p: "<< p << " \nalpha: " <<alpha
    << " \nalpha ^a mod p:" <<alphaPowA<<endl;

    cout<< "\n Private key (a): "<< a<<endl;

    //1b
    //represent message "m" as an integer

    //create an m variable that will represent the message in an integer in the range of {0,p-1}

    long long m = randNumGen(0, p-1);
    cout<< "\nYour plaintext " <<plainText<<", will be represented by this m = "<<m<<endl;



    //1c
    //select random integer
    long long k = randNumGen (1,p-2);


    //1d
    //compute gamma = alpa^k mod p
    long long gamma = SSM(alpha,k,p);

    //compute delta = m * (alpha^a)^k mod p

    long long delta = m *(SSM(alphaPowA,k,p)%p);

    //send ciphertext

    cout<<"\nThe ciphertext is: "<<gamma<< " and "<<delta;

  //*****************
 //start decryption
 //*****************


    //2a use the private-key a to computer gamma ^ p-1-a mod p

    //declare p-1-a

    long long pMinus1A = ((p-1) -a);

    long long gammaPMinus1A = SSM(gamma,pMinus1A,p);

    //2b recovering "m" private key gamma^-a * delta mod p

    //getting message again
    long long decMessage = (gammaPMinus1A *delta)%p;

    cout<<"\nYour original message: "<<m<<endl;
    cout<<"Decrypted message (original message): "<<decMessage<<endl;

}


int main()
{
    int keySize = 0;
    string plainText = "";

    //bits
    cout<<"Please enter your keysize, this will determine how large your prime # will be: ";
    cin >>keySize;

    cout << "\nPlease enter your plaintext message: ";
    getline(cin, plainText);


    elGamal(keySize,plainText);


    return 0;
}




/*
SCRATCH CODE / TESTING LINES

*/




//converting string to int
// int plainTextInt = stoi(plainText);

//    string str = millerRabin(7919,4);
//   cout << str<<endl;



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
