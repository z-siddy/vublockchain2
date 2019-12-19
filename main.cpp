#include "headers/main.h"

#include "headers/hash.h"

#include "headers/AustrolopithecusCoin.h"

#define TRANSACTIONS 5000
#define USERS 1000

using namespace hash;
using namespace aCoin;

int main() {
    int diff = 1;
    int cycle = 0;
    Hash hash;
    std::vector < User > users;
    generateUsers(USERS, users);
    string time = getTimestamp();
    std::vector < Transaction > transactions;
    generateTransactions(TRANSACTIONS, users, transactions);
    validateTransactions(transactions);
    balanceValidation(transactions);
    std::vector < Block > master;
    Block block(hash.hashThis("starterBlock"), getTimestamp(), 1, diff);
    User firstUser("FirstUser", 69, hash.hashThis("FirstUser69"));
    User secondUser("SecondUser", 420, hash.hashThis("SecondUser420"));
    Transaction First(firstUser, secondUser, 0);
    block.push_transaction(First);
    block.setMerkle();
    block.mine(diff);
    block.printBlock();
    master.push_back(block);
    while (transactions.size() > 1) {
        if (cycle == 1000) {
            diff++;
            cycle = 0;
        }
        Block t1(master.back().getHash(), getTimestamp(),1, diff);
        Block t2(master.back().getHash(), getTimestamp(),1, diff);
        Block t3(master.back().getHash(), getTimestamp(),1, diff);
        Block t4(master.back().getHash(), getTimestamp(),1, diff);
        Block t5(master.back().getHash(), getTimestamp(),1, diff);
        if (doMining(t1,transactions,diff)){
            master.push_back(t1);
            std::cout<<"\t"<<"1"<<"\n";
        }
        else if (doMining(t2,transactions,diff)){
            master.push_back(t2);
            std::cout<<"\t"<<"2"<<"\n";
        }
        else if (doMining(t3,transactions,diff)){
            master.push_back(t3);
            std::cout<<"\t"<<"3"<<"\n";
        }
        else if (doMining(t4,transactions,diff)){
            master.push_back(t4);
            std::cout<<"\t"<<"4"<<"\n";
        }
        else if (doMining(t5,transactions,diff)){
            master.push_back(t5);
            std::cout<<"\t"<<"5"<<"\n";
        }
        cycle++;
    }
    return 0;
}