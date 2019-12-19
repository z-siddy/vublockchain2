//
// Created by zygsi on 9/13/2019.
//

#ifndef VUBLOCKCHAIN_HASH_H
#define VUBLOCKCHAIN_HASH_H

#include "main.h"
#include <vector>
#include <random>
#include <sstream>

namespace hash {

    class Hash {
    private:
        string _hashedValue;
        string _inputValue;
        std::vector<int> hashVec;
        void divideToBlocks(string in) {
            for(auto i = in.begin(); i != in.end(); ++i) {
                hashVec.push_back((*i)^hashVec.size());
            }
            _inputValue = in;
        };
        void getHashedValue() {
            long long int seed = std::accumulate(hashVec.begin(), hashVec.end(), hashVec.size()) + (int)_inputValue[0]*6969/(_inputValue.length()+2) * 69;
            std::mt19937 rand(seed + 69.69);
            std::uniform_int_distribution<int> variant(0,2);
            std::uniform_int_distribution<int> number(48, 57);
            std::uniform_int_distribution<int> letter(97, 102);
            std::uniform_int_distribution<int> sletter(65, 70);
            std::stringstream hashStream;
            for (int i=0;i<64;i++){
                int var = variant(rand);
                if(var == 0)
                    hashStream << (char)number(rand);
                else if(var == 1)
                    hashStream << (char)letter(rand);
                else
                    hashStream << (char)sletter(rand);
            }
            _hashedValue = hashStream.str();
        };
    public:
        string hashThis(string in) {
            divideToBlocks(in);
            getHashedValue();
            return _hashedValue;
        };
    };

}

#endif //VUBLOCKCHAIN_HASH_H
