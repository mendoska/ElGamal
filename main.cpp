#include <iostream>
#include <string>
#include <bitset>
#include <random>
#include <vector>
using namespace std;

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



int main()
{
    int bits = 0;
    string plainText = "";

    //plaintxt
    cout << "Please enter your plaintext message";
    getline(cin,plainText);

    //bits
    cout<<"Please enter the number of bits you would like to use \n";
    cin >>bits;



    return 0;
}
