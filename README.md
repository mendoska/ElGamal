# Cryptography Assignment #3
# Implementation of El Gamal Public Key Enc 

Created with C++

This program ask for user input of a desired key size, that will be determine how many bits the prime number will be.

*PLEASE NOTE / ISSUES*
I had issues with the implementation of this and I could only get it to work with at max about 20ish bits, it starts to fail around 25 bits.

I think this had to do with my implementation of Miller Rabin.

I followed the algorithm as provided by lecture but there was inconsistencies with numbers returning composite. 
For example, I ran the number 79 (an obvious prime #) and kept getting composite

Also was having an issue with getline(Cin), I had to limit input to only one worded messages

Despite this.....

I got the flow of the program working with Miller Rabin Primality test, SSM as helper functions to the main elGamal .

This function outputs public keys, the message, the integer saved for m, the message encrypted and finally the decrypted message that should match the original message.

I have a few self-explanatory helper functions and comments to help explain or keep track of the flow of the program.

If you have any questions or helpful tips for future implementation I'll be happy to hear it.



