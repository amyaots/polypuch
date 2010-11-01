$(DRAW_LIB_NAME): common.o line.o pixel.o circle.o
	$(AR) $@ \
	./Common/common.o \
	./Line/line.o \
	./Circle/circle.o \
	./Pixel/pixel.o

common.o:
	$(MAKE) -C Common common.o

line.o:
	$(MAKE) -C Line line.o

pixel.o:
	$(MAKE) -C Pixel pixel.o

circle.o:
	$(MAKE) -C Circle circle.o

clean:
	$(CLEAN) $(DRAW_LIB_NAME)
	$(MAKE) -C Common clean
	$(MAKE) -C Line clean
	$(MAKE) -C Pixel clean
	$(MAKE) -C Circle clean