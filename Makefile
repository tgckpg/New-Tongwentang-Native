DEBUG_CXXFLAGS=-g
OBJS=main.o shared/utils.o shared/ahocrsk.o
OUT=bin/ntw-tr
TEST_DIRS=s2trad t2simp

all: $(OBJS:.o=.cpp)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(OBJS:.o=.cpp)

debug: $(OBJS:.o=.cpp)
	$(CXX) $(CXXFLAGS) $(DEBUG_CXXFLAGS) -o $(OUT) $(OBJS:.o=.cpp)

clean:
	@for dir in $(TEST_DIRS); \
	do \
		$(MAKE) -C $${dir} $@ clean || exit $$?; \
	done
	rm $(OUT)

test:
	@for dir in $(TEST_DIRS); \
	do \
		$(MAKE) -C $${dir} $@ test || exit $$?; \
	done
