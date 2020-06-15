CXX = g++
SRCS = cost.cpp simulated.cpp test_simulated.cpp

CXXFLAGS = -Wall -std=c++11

OBJS = $(SRCS:%.cpp=%.o)

all : test_simulated

test_simulated : $(OBJS)
	$(CXX) $^ -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean :
	rm -rf *.o *.d *~ *test_simulated
