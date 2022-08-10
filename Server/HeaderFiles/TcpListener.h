#pragma once

#include<iostream>
#include<WS2tcpip.h>
#include<string>
#include<sstream>

#pragma comment (lib, "ws2_32.lib")

class TcpListener
{   
    private:
        const char* m_ipAddress; //ip address for the server
        int m_port; //port number for service
        int m_socket; //internal socket file descriptor for listening socket

        fd_set m_master; //master file descriptor set

    public:
        TcpListener(const char* ipAddress, int port, int socket): 
            m_ipAddress(ipAddress), m_port(port) {}

        // initialize the listener
        int init();

        //run listener
        int run();

    protected:

};