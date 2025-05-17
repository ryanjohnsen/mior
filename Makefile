# Compiler and flags
CC        := mpicc
CFLAGS    := -Wall -Wextra -O2 -Iinclude
LDFLAGS   := 

# Directories
SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin
INC_DIR   := include
TEST_DIR  := tests

# Sources and objects
SRCS      := $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET    := $(BIN_DIR)/ior

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create necessary dirs
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# Compile and run a basic MPI "hello world" sanity check program
mpi-hello: $(BUILD_DIR)/mpi_hello.o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/mpi_hello $< $(LDFLAGS)
	mpirun -np 2 $(BIN_DIR)/mpi_hello

$(BUILD_DIR)/mpi_hello.o: $(TEST_DIR)/mpi_hello.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Test rule (example)
test: $(TARGET)
	@echo "Running tests..."
	@$(MAKE) -C $(TEST_DIR)

.PHONY: all clean test