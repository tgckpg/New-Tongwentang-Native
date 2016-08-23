CC=g++
CCFLAGS=-O3
OBJS=main.o wUTF8.o wconv_gtable.o
OUT=bin/s2trad

all: $(OBJS:.o=.cpp)
	$(CC) $(CCFLAGS) -o $(OUT) $(OBJS:.o=.cpp)

clean:
	rm $(OUT) tests/*.out
#	rm $(OUT) $(OBJS) tests/*.out

TEST_INPUT = $(wildcard tests/*.in)

.PHONY: test
test: $(TEST_INPUT:.in=.out)

tests/%.out: tests/%.in tests/%.exp $(OUT)
	$(OUT) $< > $@
	diff $@ $(word 2, $?)
