convex.a: convex.o convex_graham.o convex_add.o convex_have.o
	$(AR) $@ $^

convex.o: convex.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_graham.o: convex_graham.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_add.o: convex_add.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_have.o: convex_have.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

clean:
	$(CLEAN) convex.a
	$(CLEAN) convex.o
	$(CLEAN) convex_graham.o
	$(CLEAN) convex_add.o
	$(CLEAN) convex_have.o