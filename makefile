CC=g++
KEY=-lpthread
PATH_HEADER=./
EXE=exe
SRC=HW29.cpp OwnWayList.cpp
OBJ=$(SRC:.cpp=.o)

#run: all
#	./$(EXE)

all: $(SRC) $(EXE) clean
 
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ -I$(PATH_HEADER) $(KEY)

%.o : %.cpp
	$(CC) -c $< -o $@ 

clean:
	rm -rf *.o *.a


