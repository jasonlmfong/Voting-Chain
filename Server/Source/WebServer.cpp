#include<iostream>
#include<istream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<iterator>
#include "WebServer.h"

void WebServer::onClientConnected(int clientSocket)
{
    //send a welcome message to the connected client
    std::string welcomeMsg = "welcome to server\r\n";
    sendToClient(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1);
}

void WebServer::onClientDisconnected(int clientSocket)
{
    
}

void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
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