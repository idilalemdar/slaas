CC = g++
CFLAGS_COMMON = -O3 -std=c++14 -Wall -Iinclude
CFLAGS_TEST = -lgtest -lpthread
SRC = src/*.cpp

run: main.cpp
	$(CC) -o main main.cpp $(SRC) $(CFLAGS_COMMON)
test:
	$(CC) -o test tests/*.cpp $(SRC) $(CFLAGS_TEST) $(CFLAGS_COMMON)
debug:
    $(CC) -o debug main.cpp $(SRC) $(CFLAGS_COMMON) -g
clean_main:
	rm main
clean_test:
	rm test
clean_debug:
    rm debug
