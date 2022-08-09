#ifndef Transaction_h
#define Transaction_h

#include<string>
#include<unordered_map>

//transaction data
struct TransactionData 
{
    std::unordered_map<std::string, int> votes;
    std::string senderKey;
    std::string receiverKey;
    time_t timeStamp;


    TransactionData(){};
    

    TransactionData(std::unordered_map<std::string, int> vts, std::string sender, std::string receiver, time_t time)
    {
        votes = vts;
        senderKey = sender;
        receiverKey = receiver;
        timeStamp = time;
    };
};

#endif