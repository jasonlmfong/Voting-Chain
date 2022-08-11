#ifndef Blockchain_h
#define Blockchain_h

#include <vector>
#include "Block.h"
#include "Transaction.h"

//block chain class
class Blockchain
{
    private:
        Block createGenesisBlock();

        // private chain
        std::vector<Block> chain;

    public:
        // constructor
        Blockchain();

        //public functions
        std::vector<Block> getChain();
        Block getLatestBlock();
        void addBlock(TransactionData data);
        bool isChainValid();
        void printChain();
};

#endif