#pragma once

#include<WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class TcpListener
{   
    private:
        const char* m_ipAddress; //ip address for the server
        int m_port; //port number for service
        int m_socket; //internal socket file descriptor for listening socket

        fd_set m_master; //master file descriptor set

    public:
        TcpListener(const char* ipAddress, int port) : 
            m_ipAddress(ipAddress), m_port(port) { }

        // initialize the listener
        int init();

        //run listener
        int run();

    protected:
        //handler for client connections
        virtual void onClientConnected(int clientSocket);

        //handler for client disconnections
        virtual void onClientDisconnected(int clientSocket);

        //handler for when a message is received from the client
        virtual void onMessageReceived(int clientSocket, const char* msg, int length);

        //send a messsage to client
        void sendToClient(int clientSocket, const char* msg, int length);

        //broadcast a message from a client
        void broadcastToClients(int sendingClient, const char* msg, int length);
};