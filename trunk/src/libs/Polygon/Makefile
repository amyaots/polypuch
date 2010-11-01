$(POLYGON_LIB_NAME): general.o simple.a convex.a
	$(CP)   ./General/general.o ./
	$(UNAR) ./Simple/simple.a
	$(UNAR) ./Convex/convex.a
	$(AR) $@ *.o

general.o:
	$(MAKE) -C General general.o

simple.a:
	$(MAKE) -C Simple simple.a

convex.a:
	$(MAKE) -C Convex convex.a

clean:
	$(CLEAN) $(POLYGON_LIB_NAME)
	$(CLEAN) *.o
	$(MAKE) -C General clean
	$(MAKE) -C Simple clean
	$(MAKE) -C Convex clean