//
// Created by zygsi on 10/24/2019.
//

#ifndef VUBLOCKCHAIN2_AUSTROLOPITHECUSCOIN_H
#define VUBLOCKCHAIN2_AUSTROLOPITHECUSCOIN_H

#include "hash.h"
#include "main.h"
#include "Timer.h"

namespace aCoin {

    class User {

        private:
            string _name;
            double _balance;
            string _public_key;

        public:
            User(string name, double balance, string public_key): _name(std::move(name)), _balance(std::move(balance)), _public_key(std::move(public_key)) {};
            string getKey(){ return _public_key; }

    };

    class Transaction {

        private:
            string _tid;
            string _sender;
            string _recipient;
            double _amount;

        public:
            Transaction(string id, string sender, string recipient ,double amount): _tid(std::move(id)),
                _sender(std::move(sender)), _recipient(std::move(recipient)), _amount(std::move(amount)) {};

    };

    class Block{

        private:
            std::vector<Transaction> _transactions;
            string _previousHash;
            string _timestamp;
            string _version;
            string _merkelHash;
            long int _nonce;
            long int _difficultyTarget;

        public:
            void push_transaction(Transaction a){ _transactions.push_back(a); }

    };

    void generateUsers(int size, std::vector<User> &users) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1,1000000);
        for(int i=1;i<=size;i++){
            string name = "vardas"+std::to_string(i);
            double balance = dist(rng);
            hash::Hash temp;
            temp.getInput(name);
            string key = temp.hashThis();
            User user(name, balance, key);
            users.push_back(user);
        }

    }

}

#endif //VUBLOCKCHAIN2_AUSTROLOPITHECUSCOIN_H
