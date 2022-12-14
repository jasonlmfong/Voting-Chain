#pragma once
#include "TcpListener.h"

class WebServer : public TcpListener
{
    public:
        WebServer(const char* ipAddress, int port) : 
            TcpListener(ipAddress, port) { }

    protected:
        //handler for client connections
        virtual void onClientConnected(int clientSocket);

        //handler for client disconnections
        virtual void onClientDisconnected(int clientSocket);

        //handler for when a message is received from the client
        virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};