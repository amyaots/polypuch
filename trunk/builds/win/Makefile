export CC = g++
export CC_FLAGS = -O3 -g
export AR = ar rvs
export UNAR = ar xv
export BUILD_DIR = builds/win
export SDL_CFLAGS = `C:/MinGW/msys/1.0/local/bin/sdl-config --cflags`
export SDL_LIBS = `C:/MinGW/msys/1.0/local/bin/sdl-config --libs` -lSDL_image -lboost_math_tr1-mgw45-mt-1_44
export STRIP = strip
export CP = cp
export CLEAN = rm -f

export DRAW_LIB_NAME = libsdldrawutils.a
export DRAW_LIB_SHORT_NAME = sdldrawutils

export POLYGON_LIB_NAME = libsdlpolygon.a
export POLYGON_LIB_SHORT_NAME = sdlpolygon

export RENDER_LIB_NAME = libsdlrender.a
export RENDER_LIB_SHORT_NAME = sdlrender

export SEGMENTS_LIB_NAME = libsdlsegments.a
export SEGMENTS_LIB_SHORT_NAME = sdlsegments

export EXAMPLE_1_NAME = simplePointAdder.exe
export EXAMPLE_2_NAME = simplePointConstructor.exe
export EXAMPLE_3_NAME = simplePointInside.exe
export EXAMPLE_4_NAME = convexPointConstructor.exe
export EXAMPLE_5_NAME = convexPointAdder.exe
export EXAMPLE_6_NAME = convexPointInside.exe
export EXAMPLE_7_NAME = generalSegmentsAndBeam.exe
export EXAMPLE_8_NAME = simpleSegmentsAndBeam.exe

all: $(EXAMPLE_1_NAME) $(EXAMPLE_2_NAME) $(EXAMPLE_3_NAME) $(EXAMPLE_4_NAME) $(EXAMPLE_5_NAME) $(EXAMPLE_6_NAME) $(EXAMPLE_7_NAME) $(EXAMPLE_8_NAME)
	@echo "success"

$(EXAMPLE_1_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_1_NAME)

$(EXAMPLE_2_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_2_NAME)

$(EXAMPLE_3_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_3_NAME)

$(EXAMPLE_4_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_4_NAME)

$(EXAMPLE_5_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_5_NAME)

$(EXAMPLE_6_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_6_NAME)

$(EXAMPLE_7_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_7_NAME)

$(EXAMPLE_8_NAME): $(POLYGON_LIB_NAME) $(DRAW_LIB_NAME) $(RENDER_LIB_NAME) $(SEGMENTS_LIB_NAME)
	$(MAKE) -C examples $(EXAMPLE_8_NAME)

$(POLYGON_LIB_NAME):
	$(MAKE) -C ../../src/libs $(POLYGON_LIB_NAME)

$(DRAW_LIB_NAME):
	$(MAKE) -C ../../src/libs $(DRAW_LIB_NAME)

$(RENDER_LIB_NAME):
	$(MAKE) -C ../../src/libs $(RENDER_LIB_NAME)

$(SEGMENTS_LIB_NAME):
	$(MAKE) -C ../../src/libs $(SEGMENTS_LIB_NAME)

clean:
	$(MAKE) -C examples clean
	$(MAKE) -C ../../src/libs clean
	$(MAKE) -C ../../src/examples clean