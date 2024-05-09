CC = g++
CFLAGS = -g -Wall -std=c++20 -Wextra -pedantic
BUILD_DIR = build

# OBJS = Primitives PlyFile RayTracer Display 
OBJS = Primitives PlyFile Transformation Lighting Projection Rasterization Display OffFile

PROGS = main
all : dirs $(PROGS)

$(PROGS) : $(PROGS).cpp $(OBJS:%=$(BUILD_DIR)/%.o)
	$(CC) $(CFLAGS) -o $@ $^
	./$(PROGS)


$(BUILD_DIR)/Primitives.o : Primitives/Primitives.cpp Primitives/Primitives.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/PlyFile.o : PlyFile/PlyFile.cpp PlyFile/PlyFile.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/Transformation.o : Transformation/Transformation.c Transformation/Transformation.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/Lighting.o : Lighting/Lighting.c Lighting/Lighting.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/Projection.o : Projection/Projection.c Projection/Projection.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/Rasterization.o : Rasterization/Rasterization.cpp Rasterization/Rasterization.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/Display.o : Display/Display.cpp Display/Display.hpp
	$(CC) $(CFLAGS) -c -o $@ $<	

$(BUILD_DIR)/OffFile.o : OffFile/OffFile.cpp OffFile/OffFile.hpp
	$(CC) $(CFLAGS) -c -o $@ $<


dirs:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(PROGS)
