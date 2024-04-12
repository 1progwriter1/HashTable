COMP=g++
FLAGS= -DNDEBUG -O3 -mavx -mavx2
CFLAFS=-mavx -mavx2

LIB_OBJ=$(wildcard lib/*.o)

HASH_TABLE_SRC=$(wildcard src/hash_table/*.cpp)
MEASURE_SRC=$(wildcard src/measure/*.cpp)

HASH_TABLE_OBJ=$(wildcard src/hash_table/*.o)
MEASURE_OBJ=$(wildcard src/measure/*.o)

OBJ=$(wildcard *.o)

%.o : %.cpp
	$(COMP) $(CFLAFS) -c $< -o $@

%.out : %.o
	$(COMP) $(CFLAFS) $< $(LIB_OBJ) -o $@
	mv *.out ../../

all:
	$(COMP) $(FLAGS) $(CFLAFS) -c $(HASH_TABLE_SRC) src/main.cpp
	$(COMP) $(FLAGS) $(CFLAFS) $(OBJ) $(LIB_OBJ)

measure:
	$(COMP) $(CFLAFS) -c $(HASH_TABLE_SRC) $(MEASURE_SRC)
	$(COMP) $(CFLAFS) $(OBJ) $(LIB_OBJ) -o measure.out

clean:
	rm *.out

clean_obj:
	rm *.o

asm:
	nasm -f elf64 src/asciiSum.s
	mv src/asciiSum.o ../HashTable
	$(COMP) -no-pie $(FLAGS) src/main.cpp $(HASH_TABLE_SRC) $(LIB_OBJ) asciiSum.o
