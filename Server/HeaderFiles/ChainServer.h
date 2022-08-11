#pragma once
#include "WebServer.h"
#include "Blockchain.h"
#include<string>
#include<unordered_map>

class ChainServer : public WebServer
{
    private:
        const char* m_ipAddress; //ip address for the server
        int m_port; //port number for service
        int m_socket; //internal socket file descriptor for listening socket

        fd_set m_master; //master file descriptor set

    public:
        // initialize the listener
        virtual int init();

        //run listener
        virtual int run();

        ChainServer(const char* ipAddress, int port) : 
            WebServer(ipAddress, port) { }

        // Get latest block total votes
        std::unordered_map<std::string, int> getTotalVotes();

        // build block and add to the end of the chain
        void addBlock(Blockchain chain, std::unordered_map<std::string, int> change, std::string key, time_t time);

    protected:
        //handler for client connections
        virtual void onClientConnected(int clientSocket);

        //handler for client disconnections
        virtual void onClientDisconnected(int clientSocket);

        //handler for when a message is received from the client
        virtual void onMessageReceived(int clientSocket, const char* msg, int length);

        Blockchain Votechain;
};