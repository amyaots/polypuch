$(SEGMENTS_LIB_NAME): common.o general.a simple.o
	$(UNAR) ./General/general.a
	$(AR) $@ *.o \
	./Common/common.o \
	./Simple/simple.o

common.o:
	$(MAKE) -C Common common.o

general.a:
	$(MAKE) -C General general.a

simple.o:
	$(MAKE) -C Simple simple.o

clean:
	$(CLEAN) $(SEGMENTS_LIB_NAME)
	$(CLEAN) *.o
	$(MAKE) -C Common clean
	$(MAKE) -C Simple clean
	$(MAKE) -C General clean