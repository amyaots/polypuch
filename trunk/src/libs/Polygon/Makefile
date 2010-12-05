$(POLYGON_LIB_NAME): general.a simple.a convex.a
	$(UNAR) ./General/general.a
	$(UNAR) ./Simple/simple.a
	$(UNAR) ./Convex/convex.a
	$(AR) $@ *.o

general.a:
	$(MAKE) -C General general.a

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