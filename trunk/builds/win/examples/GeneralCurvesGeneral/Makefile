$(EXAMPLE_10_NAME): index.o
	$(CC) $(CC_FLAGS) -o $@ \
	../../../../src/examples/GeneralCurvesGeneral/index.o \
	-L../../../../src/libs/Render -l$(RENDER_LIB_SHORT_NAME) \
	-L../../../../src/libs/Polygon -l$(POLYGON_LIB_SHORT_NAME) \
	-L../../../../src/libs/Segments -l$(SEGMENTS_LIB_SHORT_NAME) \
	-L../../../../src/libs/Curves -l$(CURVES_LIB_SHORT_NAME) \
	-L../../../../src/libs/Curve -l$(CURVE_LIB_SHORT_NAME) \
	-L../../../../src/libs/SDL -l$(DRAW_LIB_SHORT_NAME) \
	$(SDL_LIBS)

	$(STRIP) $@

index.o:
	$(MAKE) -C ../../../../src/examples/GeneralCurvesGeneral index.o

clean:
	$(CLEAN) $(EXAMPLE_10_NAME)