PWD=$(shell pwd)
BIN=maze
CC=g++
SRC=main.cpp maze.cpp
#LIB_PATH=$(PWD)/stack_lib
#INC_PATH=$(PWD)/stack_lib
#LIB=-L$(LIB_PATH) -I$(INC_PATH) -lmystack


$(BIN): $(SRC)
	$(CC) -o $@ $^ $(LIB)  $(OPT)
.PHONY:clean
clean:
	rm  -rf $(BIN)
