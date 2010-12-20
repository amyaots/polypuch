$(RENDER_LIB_NAME): general.o polygon.o segments.o curves.o custom.o
	$(AR) $@ \
	./General/general.o \
	./Polygon/polygon.o \
	./Segments/segments.o \
	./Curves/curves.o \
	./Custom/custom.o

general.o:
	$(MAKE) -C General general.o

polygon.o:
	$(MAKE) -C Polygon polygon.o

segments.o:
	$(MAKE) -C Segments segments.o

curves.o:
	$(MAKE) -C Curves curves.o

custom.o:
	$(MAKE) -C Custom custom.o

clean:
	$(CLEAN) $(RENDER_LIB_NAME)
	$(MAKE) -C Polygon clean
	$(MAKE) -C Segments clean
	$(MAKE) -C Curves clean
	$(MAKE) -C General clean
	$(MAKE) -C Custom clean