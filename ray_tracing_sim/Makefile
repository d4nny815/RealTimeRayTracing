CC = g++
CFLAGS = -g -Wall -std=c++20 -Wextra -pedantic
BUILD_DIR = build

OBJS = Primitives RayTracer

PROGS = main
all : dirs $(PROGS)

$(PROGS) : $(PROGS).cpp $(OBJS:%=$(BUILD_DIR)/%.o)
	$(CC) $(CFLAGS) -o $@ $^
	./$(PROGS)

$(BUILD_DIR)/%.o : %.cpp %.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

dirs:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(PROGS)
