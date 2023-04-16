CC = g++ -std=c++17 -Wall -Werror -Wextra -Wuninitialized -Wsign-conversion -Wshadow -Weffc++ -pedantic -g
DELETE = rm -rf
TEST_FLAGS =  -lgtest

FIND_VALGRIND_ERRORS = grep --color=always -n "ERROR SUMMARY" $(VALGRIND_OUTPUT) | grep -v "0 errors from 0 contexts" || true
FIND_VALGRIND_LEAKS = grep --color=always -n "definitely lost:" $(VALGRIND_OUTPUT) | grep -v "0 bytes in 0 blocks" || true
VALGRIND = valgrind --log-file="$(VALGRIND_OUTPUT)" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

VALGRIND_OUTPUT = valgrind.txt
LIB = s21_containers.a

TEST_TARGET  = s21_tests

SRC_LIB = ./source/
BUILD_PATH = ./build/
TEST_PATH = ./tests/

SRC_LIB_FILES = $(wildcard $(SRC_LIB)*.cc)
TEST_FILES = $(wildcard $(TEST_PATH)*.cc)
SRC_LIB_HEADERS = $(wildcard include/*.h)

SRC_LIB_OBJ = $(patsubst $(SRC_LIB)%.cc, $(BUILD_PATH)%.o, $(SRC_LIB_FILES))
TEST_OBJ = $(patsubst $(TEST_PATH)%.cc, $(BUILD_PATH)%.o, $(TEST_FILES))

CPPLINT = cpplint
CLANG_FORMAT = clang-format

.PHONY: all test clean style $(CLANG_FORMAT) $(CPPLINT) $(VALGRIND)

all: test

$(BUILD_PATH):
	mkdir $(BUILD_PATH)

$(TEST_TARGET): $(LIB) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(LIB) -o $(TEST_TARGET) $(TEST_FLAGS)

$(BUILD_PATH)%.o: $(SRC_LIB)%.cc
	$(CC) -c $< -o $@

$(BUILD_PATH)%.o: $(TEST_PATH)%.cc
	$(CC) -c $< -o $@

$(LIB): style $(BUILD_PATH) $(SRC_LIB_OBJ)
	ar rcv $(LIB) $(SRC_LIB_OBJ)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	$(DELETE) $(TEST_TARGET) $(BUILD_PATH) $(VALGRIND_OUTPUT) $(LIB)

style: $(CLANG_FORMAT) $(CPPLINT)

#LIB_HEADER = s21_containers.h  TODO: UNCOMMENT
#$(CPPLINT): $(SRC_LIB_HEADERS) $(SRC_LIB_FILES) $(LIB_HEADER)
	#$(CPPLINT) $(SRC_LIB_FILES) $(SRC_LIB_HEADERS) $(LIB_HEADER)

$(CLANG_FORMAT):
	$(CLANG_FORMAT) --style=Google -i $(wildcard */*.cc *.cc */*.h *.h)

valgrind: $(TEST_TARGET)
	$(VALGRIND) ./$(TEST_TARGET) || true
	$(FIND_VALGRIND_ERRORS)
	$(FIND_VALGRIND_LEAKS)
