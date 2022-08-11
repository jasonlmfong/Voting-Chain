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

void ChainServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
    //when client side sends "GET Votes HTTP/1.1", send back voteChain.getLatestBlock().data.totalVotes
    //when client side sends "POST Cat HTTP/1.1", call addVoteBlock() and vote for cat
    //when client side sends "POST Dog HTTP/1.1", call addVoteBlock() and vote for dog

    //parse out the document requested
    std::istringstream iss(msg);
    std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

    //if the document is not good, then the following 404 will be returned to client
    std::string content = "404 Not Found";
    int errorCode = 404;

    if (parsed.size() >= 3 && parsed[0] == "GET")
    {
        if (parsed[1] == "Votes")
        {
            errorCode = 200;
            std::unordered_map<std::string, int> vote = getLatestVotes();
            
            std::ostringstream responseContent;
            responseContent << "{\"cat\": " << vote["cat"] << ", \"dog\": " << vote["dog"] << "}";
            std::string content = responseContent.str();

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
    }

    if (parsed.size() >= 3 && parsed[0] == "POST")
    {
        if (parsed[1] == "Cat")
        {
            errorCode = 200;
            std::unordered_map<std::string, int> voteCat;
            voteCat["cat"] = 1;
            voteCat["dog"] = 0;

            std::unordered_map<std::string, int> total = getLatestVotes();
            int counter = 1;
            counter += total["cat"];
            counter += total["dog"];
            std::string key = "vote" + counter;

            time_t timeNow;

            addVoteBlock(voteCat, key, timeNow);
        }
        if (parsed[1] == "Dog")
        {
            errorCode = 200;
            std::unordered_map<std::string, int> voteCat;
            voteCat["cat"] = 0;
            voteCat["dog"] = 1;

            std::unordered_map<std::string, int> total = getLatestVotes();
            int counter = 1;
            counter += total["cat"];
            counter += total["dog"];
            std::string key = "vote" + counter;

            time_t timeNow;

            addVoteBlock(voteCat, key, timeNow);
        }
    }
}

//get latest amount of votes
std::unordered_map<std::string, int> ChainServer::getLatestVotes()
{
    return voteChain.getLatestBlock().data.totalVotes;
}

// build block and add to the end of the chain
void ChainServer::addVoteBlock(std::unordered_map<std::string, int> change, std::string key, time_t time)
{
    std::unordered_map<std::string, int> total = getLatestVotes();
    total["cat"] += change["cat"];
    total["dog"] += change["dog"];
    TransactionData data(total, change, key, time);
    voteChain.addBlock(data);
}