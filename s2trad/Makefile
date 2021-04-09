OUT=../bin/ntw-tr
TEST=../bin/test

clean:
	rm -f tests/*.out tests/*.o

TEST_INPUT = $(wildcard tests/*.in)

.PHONY: test
test: $(TEST_INPUT:.in=.out)

tests/%.out: tests/%.in tests/%.exp $(OUT)
	@echo
	@grep -v "^#" $(word 1, $?) > $(word 1, $?).o
	@grep -v "^#" $(word 2, $?) > $(word 2, $?).o
	# $(basename $(notdir $(word 1, $?) ) )
	@$(OUT) $(word 1, $?).o $(word 2, $?).o > $@
	@-diff $@ $(word 2, $?).o || touch .failed
	@rm $(word 1, $?).o $(word 2, $?).o $@
