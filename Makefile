CC := gcc
CFLAGS := -Wall -std=c11 -g

SRC_DIR := src
OUT_DIR := out
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS))

TARGET := Dijkstra_Test

all: $(TARGET)

# Link final executable
Dijkstra_Test: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT_DIR)/$@ $^
	$(MAKE) clean

# objs
out/Dijkstra_Test.o: src/Dijkstra_Test.c
	$(CC) $(CFLAGS) -c $< -o $@
out/Dijkstra.o: src/Dijkstra.c src/Dijkstra.h
	$(CC) $(CFLAGS) -c $< -o $@
out/Graph.o: src/Graph.c src/Graph.h
	$(CC) $(CFLAGS) -c $< -o $@
out/Heap.o: src/Heap.c src/Heap.h
	$(CC) $(CFLAGS) -c $< -o $@


#$(OBJS): $(SRCS) | $(OUT_DIR)
#	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/*.d