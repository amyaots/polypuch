$(CURVE_LIB_NAME): general.o ermit.o bezier.o
	$(AR) $@ \
	./General/general.o \
	./Ermit/ermit.o \
	./Bezier/bezier.o

general.o:
	$(MAKE) -C General general.o

ermit.o:
	$(MAKE) -C Ermit ermit.o

bezier.o:
	$(MAKE) -C Bezier bezier.o

clean:
	$(CLEAN) $(CURVE_LIB_NAME)
	$(MAKE) -C General clean
	$(MAKE) -C Ermit clean
	$(MAKE) -C Bezier clean