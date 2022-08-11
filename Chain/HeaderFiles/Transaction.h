#ifndef Transaction_h
#define Transaction_h

#include<string>
#include<unordered_map>

//transaction data
struct TransactionData 
{
    std::unordered_map<std::string, int> totalVotes;
    std::unordered_map<std::string, int> voteChanges;
    std::string chainKey;
    time_t timeStamp;


    TransactionData(){};
    

    TransactionData(std::unordered_map<std::string, int> ttlVts, std::unordered_map<std::string, int> vtChgs, std::string key, time_t time)
    {
        totalVotes = ttlVts;
        voteChanges = vtChgs;
        chainKey = key;
        timeStamp = time;
    };
};

#endif