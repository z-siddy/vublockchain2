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

}

#endif //VUBLOCKCHAIN2_AUSTROLOPITHECUSCOIN_H
