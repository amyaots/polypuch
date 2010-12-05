general.a: general.o general_have.o
	$(AR) $@ $^

general.o: general.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

general_have.o: general_have.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

clean:
	$(CLEAN) general.a
	$(CLEAN) general.o
	$(CLEAN) general_have.o