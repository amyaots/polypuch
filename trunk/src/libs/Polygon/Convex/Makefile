convex.a: convex.o convex_graham.o convex_add.o convex_have.o convex_jarvis.o convex_intersect.o convex_hoare.o
	$(AR) $@ $^

convex.o: convex.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_graham.o: convex_graham.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_add.o: convex_add.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_have.o: convex_have.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_jarvis.o: convex_jarvis.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_intersect.o: convex_intersect.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

convex_hoare.o: convex_hoare.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $^ $(SDL_CFLAGS)

clean:
	$(CLEAN) convex.a
	$(CLEAN) convex.o
	$(CLEAN) convex_graham.o
	$(CLEAN) convex_add.o
	$(CLEAN) convex_have.o
	$(CLEAN) convex_jarvis.o
	$(CLEAN) convex_intersect.o
	$(CLEAN) convex_hoare.o