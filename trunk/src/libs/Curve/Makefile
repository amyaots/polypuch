$(CURVE_LIB_NAME): general.o ermit.o
	$(AR) $@ \
	./General/general.o \
	./Ermit/ermit.o

general.o:
	$(MAKE) -C General general.o

ermit.o:
	$(MAKE) -C Ermit ermit.o

clean:
	$(CLEAN) $(CURVE_LIB_NAME)
	$(MAKE) -C General clean
	$(MAKE) -C Ermit clean