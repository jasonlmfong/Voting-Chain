#include "ChainServer.h"

//run server with blockchain
void main()
{
    ChainServer chainServer("0.0.0.1", 8080);
    if (chainServer.init() != 0)
        return;
    chainServer.run();

    system("pause");
}