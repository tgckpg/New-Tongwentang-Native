BINS=native/s2trad
all: $(BINS)
	$(MAKE) -C $(BINS) $@

clean:
	$(MAKE) -C $(BINS) clean

test:
	$(MAKE) -C $(BINS) test
