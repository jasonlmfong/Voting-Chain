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

    std::unordered_map<std::string, int> originalVotes;
    originalVotes["cat"] = 1;
    originalVotes["dog"] = 0;

    std::unordered_map<std::string, int> changeVotes;
    changeVotes["cat"] = 1;
    changeVotes["dog"] = 0;
    
    TransactionData data1(originalVotes, changeVotes, "vote4Cats", time(&data1Time));
    VoteChain.addBlock(data1);

    VoteChain.printChain();

    std::cout << "is chain valid?" << std::endl
        << VoteChain.isChainValid() << std::endl;

    return 0;
}