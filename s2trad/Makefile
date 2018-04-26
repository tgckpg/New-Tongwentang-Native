OUT=../bin/ntw-tr
TEST=../bin/test

clean:
	rm tests/*.out

TEST_INPUT = $(wildcard tests/*.in)

.PHONY: test
test: $(TEST_INPUT:.in=.out)

tests/%.out: tests/%.in tests/%.exp $(OUT)
	@echo
	$(OUT) $< > $@
	-diff $@ $(word 2, $?)
