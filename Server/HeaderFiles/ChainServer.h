#pragma once
#include "WebServer.h"
#include "Blockchain.h"
#include<string>
#include<unordered_map>
#include<chrono>
#include<ctime>

class ChainServer : public WebServer
{
    private:
        const char* m_ipAddress; //ip address for the server
        int m_port; //port number for service
        int m_socket; //internal socket file descriptor for listening socket

        fd_set m_master; //master file descriptor set

        Blockchain voteChain;

    public:
        // initialize the listener
        virtual int init();

        ChainServer(const char* ipAddress, int port) : 
            WebServer(ipAddress, port) { }

        //get latest amount of votes
        std::unordered_map<std::string, int> getLatestVotes();

        // build block and add to the end of the chain
        void addVoteBlock(std::unordered_map<std::string, int> change, std::string key, time_t time);

    protected:
        //handler for when a message is received from the client
        virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};