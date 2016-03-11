CC=g++
lib=libmystack.a

SRC=$(shell ls *.cpp)
OBJ=$(SRC:.cpp=.o)

$(lib):$(OBJ)
	ar -rcv $@ $^
%.o:%.cpp
	$(CC) -c $< -D_DEL_MAIN_

.PHONY:clean
clean:
	rm -rf $(lib) output *.o

.PHONY:output
output:clean $(lib)
	mkdir -p output
	cp *.a output
	cp *.h output
