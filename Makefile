CFLAFS=-fsanitize=address,alignment -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -Werror=vla

COMP=g++

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
	$(COMP) $(CFLAFS) -c $(HASH_TABLE_SRC) $(MEASURE_SRC) src/main.cpp
	$(COMP) $(CFLAFS) $(OBJ) $(LIB_OBJ)

clean:
	rm *.out

clean_obj:
	rm *.o
