BIN=match_check
SRC=match_check.cpp
LIB_PATH=stack_lib
CC=g++

$(BIN):$(SRC)
	$(CC) -o $(BIN) $(SRC) -L$(LIB_PATH) -I$(LIB_PATH) -lmystack
.PHONY:clean
clean:
	rm -rf $(BIN)
