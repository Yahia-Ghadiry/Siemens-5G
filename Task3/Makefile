TARGET := program
SRC_DIR := src
BLD_DIR := build

SRC_DIRS := $(shell find $(SRC_DIR) -type d) 
SRCS := $(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
HEADERS := $(wildcard $(addsuffix /*.h,$(SRC_DIRS)))
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(SRCS))

CC := clang++
CFLAGS := -Wall

.PHONY: all clean
.SECONDEXPANSION:

all: $(OBJS) | $(BLD_DIR)/
	$(CC) $(CFLAGS) $^ -o $(TARGET).elf

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(BLD_DIR)/$$(dir %)
	@echo Building $< into $@
	$(CC) $(CFLAGS) -c $< -o $@

%/:
	mkdir -p $@

clean:
	rm -rf $(BLD_DIR) $(TARGET).hex
