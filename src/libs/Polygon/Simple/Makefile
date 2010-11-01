simple.a: simple_add.o simple_have.o
	$(AR) $@ $^

simple_add.o: simple_add.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

simple_have.o: simple_have.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

clean:
	$(CLEAN) simple.a
	$(CLEAN) simple_add.o
	$(CLEAN) simple_have.o