$(SEGMENTS_LIB_NAME): general.a common.o
	$(UNAR) ./General/general.a
	$(AR) $@ *.o ./Common/common.o

common.o:
	$(MAKE) -C Common common.o

general.a:
	$(MAKE) -C General general.a

clean:
	$(CLEAN) $(SEGMENTS_LIB_NAME)
	$(CLEAN) *.o
	$(MAKE) -C Common clean
	$(MAKE) -C General clean