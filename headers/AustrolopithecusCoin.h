//
// Created by zygsi on 10/24/2019.
//

#ifndef VUBLOCKCHAIN2_AUSTROLOPITHECUSCOIN_H
#define VUBLOCKCHAIN2_AUSTROLOPITHECUSCOIN_H

#include "hash.h"

#include "main.h"

#include "Timer.h"


using namespace hash;

namespace aCoin {

    class User {

    private:
        string _name;
        double _balance;
        string _public_key;

    public:
        User(string name, double balance, string public_key): _name(std::move(name)), _balance(std::move(balance)), _public_key(std::move(public_key)) {};
        string getKey() {
            return _public_key;
        }
        string getName() {
            return _name;
        }

    };

    class Transaction {

    private:
        unsigned long int _tid;
        string _sender;
        string _recipient;
        double _amount;
        string _thash;

    public:
        Transaction(unsigned long int id, string sender, string recipient, double amount): _tid(std::move(id)),
                                                                                _sender(std::move(sender)), _recipient(std::move(recipient)), _amount(std::move(amount)) {
            Hash obj;
            _thash = obj.hashThis(std::to_string(id) + std::to_string(amount) + sender + recipient);
        };

        string hashedValue() {
            return _thash;
        }

    };

    class Block {

    private:
        std::vector < Transaction > _transactions;
        string _previousHash;
        string _timestamp;
        int _version;
        string _merkleHash = "";
        long int _nonce = 0;
        int _difficultyTarget;

    public:
        Block(string previousHash, string timestamp, int version, int diff): _previousHash(std::move(previousHash)),
                                                                                  _timestamp(std::move(timestamp)), _version(version), _difficultyTarget(diff) {};

        void push_transaction(Transaction t) {
            _transactions.push_back(t);
        }
//
        void genTestTransactions(std::vector < Transaction > & t) {
            std::random_device rand;
            std::mt19937 generate(rand());
            if (t.size() >= 100) {
                for (int i = 0; i < 100; i++) {
                    std::uniform_int_distribution < int > r(0, t.size() - 1);
                    int pos = r(generate);
                    _transactions.push_back(t[pos]);
                    t.erase(t.begin() + pos);
                }
            } else {
                std::cout << "Not enough transactions to form a block!" << std::endl;
            }

        }
//
        string merkleHash(std::vector < string > transHashes) {
            if (transHashes.size() == 1) {
                return transHashes[0];
            }
            std::vector < string > temp;

            for (int i = 0; i < transHashes.size() - 1; i = i + 2) {
                Hash obj;
                temp.push_back(obj.hashThis(transHashes[i] + transHashes[i + 1]));
            }
            if (transHashes.size() % 2 == 1) {
                Hash obj;
                temp.push_back(obj.hashThis(transHashes[transHashes.size() - 1]));
            }
            return merkleHash(temp);
        }
//
        string getHash() {
            Hash obj;
            string in = _previousHash + obj.hashThis(_timestamp) + _merkleHash + std::to_string(_difficultyTarget + _version + _nonce);
            return obj.hashThis(in);
        }
//
//
        void setMerkle() {
            std::vector < string > transHashes;
            for (auto it = begin(_transactions); it != end(_transactions); ++it) {
                transHashes.push_back(it -> hashedValue());
            }
            _merkleHash = merkleHash(transHashes);
        }
//
        void mine(int difficulty) {
            string substring(difficulty, '0');
            while (strncmp(Block::getHash().c_str(), substring.c_str(), substring.size()) != 0) {
                _nonce++;
            }
        }
//
        void printBlock() {
            Hash obj;
            string in = _previousHash + obj.hashThis(_timestamp) + _merkleHash + std::to_string(_difficultyTarget + _version + _nonce);
            std::cout << _previousHash + "\t" + std::to_string(_difficultyTarget) + "\t" + std::to_string(_nonce) + "\t" + _merkleHash + '\t';
            std::cout << obj.hashThis(in) << std::endl;
        }

    };

    void generateUsers(int size, std::vector < User > & users) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution < std::mt19937::result_type > dist(1, 1000000);
        for (int i = 1; i <= size; i++) {
            string name = "vardas" + std::to_string(i);
            double balance = dist(rng);
            hash::Hash temp;
            string key = temp.hashThis(name);
            User user(name, balance, key);
            users.push_back(user);
        }
    }

    void generateTransactions(int numberOfTransactions, std::vector<User> &userList, std::vector<Transaction> &list){
        std::random_device r;
        std::mt19937 generate(r());
        std::uniform_int_distribution<unsigned long long int> random(0,userList.size()-1);
        std::uniform_int_distribution<int> randomTrans(0,10000);
        Hash obj;
        std::vector<Transaction> tempTransList;

        for (int i = 0; i < numberOfTransactions; i++)
        {
            string senderKey = userList[random(generate)].getKey();
            string recipientKey = userList[random(generate)].getKey();
            Transaction tmpTrans(i, obj.hashThis(senderKey), obj.hashThis(recipientKey), randomTrans(generate));
            tempTransList.push_back(tmpTrans);
        }
        std::cout<<"Transactions generated"<<std::endl;
        list = tempTransList;
    }

    string getTimestamp(){
        using namespace std::chrono;
        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) %  10000000;
        auto timer = system_clock::to_time_t(now);
        std::tm bt = *std::localtime(&timer);
        std::ostringstream oss;
        oss << std::put_time(&bt, "%H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }


}

#endif