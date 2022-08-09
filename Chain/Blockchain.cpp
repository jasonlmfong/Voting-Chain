#include<stdio.h>
#include<ctime>
#include<vector>
#include<string>
#include<unordered_map>

#include "Block.h"
#include "Blockchain.h"

//Blockchain class constructor
Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock()
{
    time_t current;
    
    std::unordered_map<std::string, int> emptyVotes;

    TransactionData d(emptyVotes, emptyVotes, "genesisKey", "voting", time(&current));

    Block genesis(0, d, 0);
    return genesis;
}

std::vector<Block> Blockchain::getChain() {
    return chain;
}

//get the back of the chain
Block Blockchain::getLatestBlock()
{
    return chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size() - 1;
    std::size_t previousHash = (int)chain.size() >= 0 ? getLatestBlock().getHash() : 0;
    Block newBlock(index, d, previousHash);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            return false;
        }

        //checks if this is the first item
        if (it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }
    return true;
}

void Blockchain::printChain() {
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        printf("\nBlock ===================================");
        printf("\nIndex: %d", currentBlock.getIndex());
        printf("\nVotes: %f", currentBlock.data.votes);
        printf("\nSenderKey: %s", currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s", currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %ld", currentBlock.data.timeStamp);
        printf("\nHash: %zu", currentBlock.getHash());
        printf("\nPrevious Hash: %zu", currentBlock.getPreviousHash());
        printf("\nIs Block Valid?: %d", currentBlock.isHashValid());
    }
}