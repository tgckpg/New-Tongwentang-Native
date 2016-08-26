CC=g++
CCFLAGS=-Ofast
OBJS=main.o wconv_gtable.o shared/Utf8Byte.o
OUT=bin/t2simp

all: $(OBJS:.o=.cpp)
	$(CC) $(CCFLAGS) -o $(OUT) $(OBJS:.o=.cpp)

clean:
	rm $(OUT) tests/*.out
#	rm $(OUT) $(OBJS) tests/*.out

TEST_INPUT = $(wildcard tests/*.in)

.PHONY: test
test: $(TEST_INPUT:.in=.out)

tests/%.out: tests/%.in tests/%.exp $(OUT)
	@echo
	$(OUT) $< > $@
	diff $@ $(word 2, $?)
