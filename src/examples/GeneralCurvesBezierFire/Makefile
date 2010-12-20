libindex.a: sonne.o earth.o mars.o rocket.o
	$(AR) $@ \
	./Sonne/sonne.o \
	./Earth/earth.o \
	./Mars/mars.o \
	./Rocket/rocket.o

index.o: index.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ -I../../libs -I../../examples $(SDL_CFLAGS)

sonne.o:
	$(MAKE) -C Sonne sonne.o

earth.o:
	$(MAKE) -C Earth earth.o

mars.o:
	$(MAKE) -C Mars mars.o

rocket.o:
	$(MAKE) -C Rocket rocket.o

clean:
	$(CLEAN) index.o
	$(CLEAN) libindex.a
	$(MAKE) -C Sonne clean
	$(MAKE) -C Earth clean
	$(MAKE) -C Rocket clean