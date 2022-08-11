#include "ChainServer.h"
#include<iostream>
#include<string>
#include<sstream>

int ChainServer::init()
{
    //initialize winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    
    int wsok = WSAStartup(ver, &wsData);
    if (wsok != 0)
    {
        return wsok;
    }

    //create socket
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == INVALID_SOCKET)
    {
        return WSAGetLastError();
    }

    //bind ip address and port to the socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ipAddress, &hint.sin_addr); 

    if (bind(m_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
    {
        return WSAGetLastError();
    }

    //tell winsock the socket is for listening
    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        return WSAGetLastError();
    }

    //create master fiel descriptor set and zero the set
    FD_ZERO(&m_master);

    //add the first socket we want to interact with: the listening socket, we need this to hear the incoming messages
    FD_SET(m_socket, &m_master);

    return 0;
}

int ChainServer::run()
{
    //quit command will stop the server from running
    bool running = true;
    
    while(running)
    {
        //make a copy to the master file descriptor, since the call to select() is _DESTRUCTUVE_.
        //the copy only contains sockets which are accepting inbound connection requests or messages

        //for example, a server with a master file descriptor that contains 4 items
        //the lsitening socket and 3 clients. when this is passed into select(), only the sockets that are intereacting with the server are returned.
        //if only one client is sending a message at a time, the contents of 'copy' will be one socket. we would have lost all other sockets.

        //therefore we make a copy of the master list to pass into select()

        fd_set copy = m_master;

        //see who is talking to us
        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

        //loop through all the current connections/ potential connections
        for (int i = 0; i < socketCount; i++)
        {
            //makes its easier by doing this assignment
            SOCKET sock = copy.fd_array[i];

            //is it an inbound connection
            if (sock == m_socket)
            {
                //acept new conenction
                SOCKET client = accept(m_socket, nullptr, nullptr);

                //add the new connection to the list of connected clients
                FD_SET(client, &m_master);

                //client connected
                onClientConnected(client);
            }
            else //inbound message
            {
                char buf[4096];
                ZeroMemory(buf, 4096);

                //receive message
                int bytesIn = recv(sock, buf, 4096, 0);
                if (bytesIn <= 0)
                {
                    //drop the client
                    //client disconnected
                    onClientDisconnected(sock);
                    closesocket(sock);
                    FD_CLR(sock, &m_master);
                }
                else
                {
                    onMessageReceived(sock, buf, bytesIn);
                    //check to see if it is a command. \quit kills the server
                    if (buf[0] == '\\')
                    {
                        std::string cmd = std::string(buf, bytesIn);
                        if (cmd == "\\quit")
                        {
                            running = false;
                            break;
                        }

                        //unknown command
                        continue;
                    }

                    //send message to other clients, and definitely not the listening socket
                    std::ostringstream ss;
                    ss << "SOCKET #" << sock << ": " << buf << "\r\n";
                    std::string strOut = ss.str();
                    broadcastToClients(sock, strOut.c_str(), strOut.size() + 1);
                }
            }
        }
    }

    //remove the listening socket from the master file list and close it, to prevent anyone else trying to connect
    FD_CLR(m_socket, &m_master);
    closesocket(m_socket);

    //message to let use know what is happening
    std::string msg = "server is shutting down\r\n";
    
    while (m_master.fd_count > 0)
    {
        //get socket number
        SOCKET sock = m_master.fd_array[0];

        //send goodbye message
        sendToClient(sock, msg.c_str(), msg.size() + 1);

        //remove it from the master file list and close the socket
        FD_CLR(sock, &m_master);
        closesocket(sock);
    }

    //cleanup winsock
    WSACleanup();
    return 0;
}