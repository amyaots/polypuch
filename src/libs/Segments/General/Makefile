general.a: general.o general_beam.o
	$(AR) $@ $^

general.o: general.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

general_beam.o: general_beam.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

clean:
	$(CLEAN) general.o