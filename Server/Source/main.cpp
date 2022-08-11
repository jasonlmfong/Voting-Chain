#include "ChainServer.h"

//run webserver with blockchain
void main()
{
    ChainServer chainServer("0.0.0.0", 8080);
    if (chainServer.init() != 0)
        return;

    chainServer.run();

    system("pause");
}