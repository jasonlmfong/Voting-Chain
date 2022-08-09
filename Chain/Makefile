Block.o: Block.cpp Block.h Transaction.h
    gcc -c Block.cpp -o Block.o

BlockChain.o: Blockchain.cpp Blockchain.h Block.h
    gcc -c Blockchain.cpp -o Blockchain.o

votechain.o: main.cpp Transaction.h Block.h Blockchain.h
    gcc -c main.cpp -o votechain.o

votechain: votechain.o Block.o BlockChain.o
    gcc votechain.o Block.o BlockChain.o -o votechain

.PHONY: clean
clean:
    rm votechain *.o