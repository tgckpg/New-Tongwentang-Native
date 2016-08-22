CC=g++
CCFLAGS=-O3
OBJS=main.o wUTF8.o wconv_gtable.o
OUT=bin/s2trad

all: $(OBJS:.o=.cpp)
	$(CC) $(CCFLAGS) -o $(OUT) $(OBJS:.o=.cpp)

clean:
	rm $(OUT) $(OBJS)

TEST_INPUT = $(wildcard tests/*.in)

.PHONY: test
test: $(TEST_INPUT:.in=.exp)
	$(OUT) $(TEST_INPUT) > $(TEST_INPUT:.in=.out)
	diff $(TEST_INPUT:.in=.exp) $(TEST_INPUT:.in=.out)
