# The following lines are used to define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Werror -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Executable name
BIN = sparse_matrix

# Object files
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/SparseMatrix.o \
       $(OBJ_DIR)/COO_SparseMatrix.o \
       #$(OBJ_DIR)/CSR_SparseMatrix.o

# Header files
HEADERS = $(INC_DIR)/SparseMatrix.hpp \
          $(INC_DIR)/COO_SparseMatrix.hpp \
          #$(INC_DIR)/CSR_SparseMatrix.hpp

# The following lines are used to pass arguments to the executable
ARGS = "$(filter-out $@,$(MAKECMDGOALS))"

# The first target is the one that is executed when you invoke the Makefile
all: build

.PHONY: build
build: $(BIN)

# Create the executable by linking the object files
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ $^

# Create the object files

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Remove the executable and the object files

.PHONY: clean
clean:
	rm -f $(BIN) $(OBJS)

# Run the executable

.PHONY: run
run: $(BIN)
	./$(BIN) $(ARGS)

# Prevents Make from interpreting the arguments as targets
%:
	@: