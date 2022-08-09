#ifndef Block_h
#define Block_h

//block class
class Block
{
    private:
        int index;
        size_t blockHash;
        size_t previousHash;
        size_t generateHash();

    public:
        //constructor
        Block(int idx, TransactionData d, size_t prevHash);

        // Get Index
        int getIndex();

        //get original hash
        size_t getHash();

        //get previous hash
        size_t getPreviousHash();

        //transaction data
        TransactionData data;

        //validate hash
        bool isHashValid();
};

#endif
