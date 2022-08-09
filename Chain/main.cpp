#include<iostream>
#include<ctime>
#include<vector>
#include<unordered_map>

#include "Transaction.h"
#include "Block.h"
#include "Blockchain.h"

using std::hash;

int main()
{
    //start blockchain
    Blockchain VoteChain;

    //data for first added block
    time_t data1Time;

    std::unordered_map<std::string, int> votes;
    votes["cat"] = 1;
    votes["dog"] = 1;
    
    TransactionData data1(votes, "Joe", "Sally", time(&data1Time));
    VoteChain.addBlock(data1);

    VoteChain.printChain();

    std::cout << "is chain valid?" << std::endl
        << VoteChain.isChainValid() << std::endl;

    return 0;
}