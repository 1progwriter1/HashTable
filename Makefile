COMP=g++

%.o : %.cpp
	$(COMP) -c $< -o $@

%.out : %.o
	$(COMP) $< -o $@