$(EXAMPLE_15_NAME): libindex.a index.o
	$(CC) $(CC_FLAGS) -o $@ \
	../../../../src/examples/GeneralCurvesBezierFire/index.o \
	-L../../../../src/examples/GeneralCurvesBezierFire -lindex \
	-L../../../../src/libs/Render -l$(RENDER_LIB_SHORT_NAME) \
	-L../../../../src/libs/Polygon -l$(POLYGON_LIB_SHORT_NAME) \
	-L../../../../src/libs/Segments -l$(SEGMENTS_LIB_SHORT_NAME) \
	-L../../../../src/libs/Curves -l$(CURVES_LIB_SHORT_NAME) \
	-L../../../../src/libs/Curve -l$(CURVE_LIB_SHORT_NAME) \
	-L../../../../src/libs/SDL -l$(DRAW_LIB_SHORT_NAME) \
	$(SDL_LIBS)

	$(STRIP) $@

libindex.a:
	$(MAKE) -C ../../../../src/examples/GeneralCurvesBezierFire libindex.a

index.o:
	$(MAKE) -C ../../../../src/examples/GeneralCurvesBezierFire index.o

clean:
	$(CLEAN) $(EXAMPLE_15_NAME)