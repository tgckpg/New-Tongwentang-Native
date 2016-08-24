BINS=native/s2trad native/t2simp
all:
	@for dir in $(BINS); \
	do \
		$(MAKE) -C $${dir} $@ || exit $$?; \
	done

clean:
	@for dir in $(BINS); \
	do \
		$(MAKE) -C $${dir} $@ clean || exit $$?; \
	done

test:
	@for dir in $(BINS); \
	do \
		$(MAKE) -C $${dir} $@ test || exit $$?; \
	done
