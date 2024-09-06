CC = gcc
BIN_DIR = bin
BUILD_DIR = build
SRC_DIR = src

ifeq ($(OS),Windows_NT)
    EXT = .exe
else
    EXT = .o
endif

# Ensure bin/ and build/ directories are created
all: $(BIN_DIR)/test_output${EXT}

# Customer-related build
$(BUILD_DIR)/customer_output.o: $(SRC_DIR)/customer.c | $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/customer.c -o $(BUILD_DIR)/customer_output.o

$(BUILD_DIR)/lib_customer.a: $(BUILD_DIR)/customer_output.o
	ar rcs $(BUILD_DIR)/lib_customer.a $(BUILD_DIR)/customer_output.o

# Admin-related build
$(BUILD_DIR)/admin_output.o: $(SRC_DIR)/admin.c | $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/admin.c -o $(BUILD_DIR)/admin_output.o

$(BUILD_DIR)/lib_admin.a: $(BUILD_DIR)/admin_output.o
	ar rcs $(BUILD_DIR)/lib_admin.a $(BUILD_DIR)/admin_output.o

# Linking both libraries into the final executable
$(BIN_DIR)/test_output${EXT}: $(SRC_DIR)/main.c $(BUILD_DIR)/lib_customer.a $(BUILD_DIR)/lib_admin.a | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/test_output${EXT} $(SRC_DIR)/main.c -L. $(BUILD_DIR)/lib_customer.a $(BUILD_DIR)/lib_admin.a -lm

# Create bin/ directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Create build/ directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up all build and bin files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Compile and run the program
run: $(BIN_DIR)/test_output${EXT}
	./$(BIN_DIR)/test_output${EXT}
