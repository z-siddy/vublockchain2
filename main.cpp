#include "headers/main.h"
#include "headers/hash.h"
#include "headers/AustrolopithecusCoin.h"

using namespace hash;
using namespace aCoin;

int main() {

    std::vector<User> temp;
    generateUsers(1000, temp);
    cout << "done";

    return 0;
}
