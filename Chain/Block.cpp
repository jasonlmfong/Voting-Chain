#include<stdio.h>
#include<string>

#include "Block.h"
#include "Transaction.h"

//constructor with parameters
Block::Block(int idx, TransactionData d, size_t prevHash)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

//private functions
int Block::getIndex()
{
    return index;
}

size_t Block::generateHash()
{
    std::hash<std::string> transDataHash;
    std::hash<std::string> prevHash;
    std::string toHash = std::to_string(data.totalVotes) + data.receiverKey + data.senderKey + std::to_string(data.timeStamp);

    return transDataHash(toHash) + prevHash(std::to_string(previousHash));
}

//public functions
size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == getHash();
}