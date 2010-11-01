$(RENDER_LIB_NAME): polygon.o
	$(AR) $@ \
	./Polygon/polygon.o

polygon.o:
	$(MAKE) -C Polygon polygon.o

clean:
	$(CLEAN) $(RENDER_LIB_NAME)
	$(MAKE) -C Polygon clean