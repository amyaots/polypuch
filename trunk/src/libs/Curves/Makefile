$(CURVES_LIB_NAME): general.o
	$(AR) $@ ./General/general.o

general.o:
	$(MAKE) -C General general.o

clean:
	$(CLEAN) $(CURVES_LIB_NAME)
	$(MAKE) -C General clean