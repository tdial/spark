CXX=g++
CXXFLAGS=-Wall -Werror -g 

all: spark

spark: spark.o
	$(CXX) $(CXXFLAGS) -o spark spark.o

spark.o: spark.cc
	$(CXX) $(CXXFLAGS) -c spark.cc

.PHONY:
clean:
	rm -f spark *.o *~
