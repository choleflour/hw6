#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = {0};
        int length = k.length();
        int *digit = new int[length];

        for (int i = 0; i < length; ++i ) {
            digit[i] = letterDigitToNumber(k[i]);
        }

        int i = 4 - (length-1)/6;
        int curr = 1;

        w[i] = digit[0];
        while (curr < length) {
            i = 4 - (length-1 - curr)/6;
            // std::cout <<  i << "    " << w[i] << std::endl;
            w[i] = w[i] * 36 + digit[curr];
            ++curr;
            
        }
        
        delete [] digit;

        // for (int i = 0; i < 5; ++i) {
        //     std::cout << "w[" << i << "] = " << w[i] << std::endl;
        // }

        return rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4];


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        // convert upper to lower case
        if (std::isalpha(letter)) {
            if (std::isupper(letter)) {
                letter = std::tolower(letter);
                // std::cout << letter << std::endl;
            }
            return letter - 'a';

        } else {
            return letter - '0' + 26;
        }
        
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
