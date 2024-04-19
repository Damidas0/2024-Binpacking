

#---------VARIABLE DE COMPILATIONS------------#
CC = g++
FLAGS = -Wall -ggdb -g

all: folder test.out

#------ OUT -------#
test.out: test.o 
	$(CC) -g $(OBJS) obj/test.o -o bin/test.out 


#------ O --------#
test.o: src/test.cpp
	$(CC) $(FLAGS) -c src/test.cpp -o obj/test.o


#---- CPP -----# 


#---------FONCTION ANNEXES------------#
folder: folder_bin folder_obj

folder_bin: 
	mkdir -p bin 

folder_obj:
	mkdir -p obj


clean:
	rm *.o

veryclean: clean
	rm *.out
