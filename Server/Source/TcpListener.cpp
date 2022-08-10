#include "TcpListener.h"



int TcpListener::init()
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

    //add the first socket we want to interact with: the listening socket, we ened this to hear the incoming messages
    FD_SET(m_socket, &m_master);

    return 0;
}

int TcpListener::run()
{

}