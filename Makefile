

#---------VARIABLE DE COMPILATIONS------------#
CC = g++
FLAGS = -Wall -ggdb -g

all: folder filereader.out

#------ OUT -------#
filereader.out: filereader.o 
	$(CC) -g $(OBJS) obj/filereader.o -o bin/filereader.out 


#------ O --------#
filereader.o: src/filereader.cpp
	$(CC) $(FLAGS) -c src/filereader.cpp -o obj/filereader.o


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
