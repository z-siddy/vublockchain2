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
    std::vector < Block > master;
    Block block(hash.hashThis("starterBlock"), getTimestamp(), 1, diff);
    Transaction First(0, hash.hashThis("Bit"), hash.hashThis("Kojine"), 0);
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
        Block newBlock(master.back().getHash(), getTimestamp(), 1, diff);
        newBlock.genTestTransactions(transactions);
        newBlock.setMerkle();
        newBlock.mine(diff);
        newBlock.printBlock();
        master.push_back(newBlock);
        cycle++;
    }
    return 0;
}