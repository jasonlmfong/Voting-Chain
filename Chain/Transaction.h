#ifndef Transaction_h
#define Transaction_h

#include<string>
#include<unordered_map>

//transaction data
struct TransactionData 
{
    std::unordered_map<std::string, int> totalVotes;
    std::unordered_map<std::string, int> voteChanges;
    std::string senderKey;
    std::string receiverKey;
    time_t timeStamp;


    TransactionData(){};
    

    TransactionData(std::unordered_map<std::string, int> ttlVts, std::unordered_map<std::string, int> vtChgs, std::string sender, std::string receiver, time_t time)
    {
        totalVotes = ttlVts;
        voteChanges = vtChgs;
        senderKey = sender;
        receiverKey = receiver;
        timeStamp = time;
    };
};

#endif