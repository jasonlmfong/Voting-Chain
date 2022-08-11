#include "ChainServer.h"
#include "Blockchain.h"
#include<iostream>
#include<istream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<iterator>

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

    //create master file descriptor set and zero the set
    FD_ZERO(&m_master);

    //add the first socket we want to interact with: the listening socket, we need this to hear the incoming messages
    FD_SET(m_socket, &m_master);

    voteChain = Blockchain();

    return 0;
}

void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
    //TODO: when client side sends "\\getTotalVotes", send back voteChain.getLatestBlock().data.totalVotes
    //TODO: when client side sends "\\voteCat", call addVoteBlock() and vote for cat
    //TODO: when client side sends "\\voteDog", call addVoteBlock() and vote for dog

    //GET /index.html HTTP/1.1

    //parse out the document requested
    std::istringstream iss(msg);
    std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    //if the document is not good, then the followign 404 will be returned to client
    std::string content = "<h1>404 Not Found</h1>";
    std::string htmlFile = "/main.html";
    int errorCode = 404;

    if (parsed.size() >= 3 && parsed[0] == "GET")
    {
        htmlFile = parsed[1];
        if (htmlFile == "/")
        {
            htmlFile = "/main.html";
        }
    }

    //open the document in the local file system
    std::ifstream f(".\\Web" + htmlFile);

    if (f.good())
    {
        //if document is good, then write the document to content
        std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        content = str;
        errorCode = 200;
    }

    f.close();

    //send content back to the client
    std::ostringstream oss;
    oss << "HTTP/1.1 " << errorCode << " OK\r\n";
    oss << "Cache-Control: no-cache, private\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "\r\n";
    oss << content;

    std::string output = oss.str();
    int size = output.size() + 1;

    sendToClient(clientSocket, output.c_str(), size);
}

// build block and add to the end of the chain
void ChainServer::addVoteBlock(std::unordered_map<std::string, int> change, std::string key, time_t time)
{
    TransactionData data(voteChain.getLatestBlock().data.totalVotes, change, key, time);
    voteChain.addBlock(data);
}