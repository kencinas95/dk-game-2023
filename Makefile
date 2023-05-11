SRC_DIR 	:= ./source
BUILD_DIR 	:= ./build
INCLUDE_DIR	:= ./include
LIBS_DIR 	:= ./libs
TEST_DIR	:= ./test

# SDL_FLAGS 	:= $(shell sdl2-config --cflags --libs)
SDL_FLAGS 	:= -I $(LIBS_DIR) -L $(LIBS_DIR) -lSDL2 -lSDL2_image -lSDL2_mixer -llibogg-0 

BUILD		:= $(BUILD_DIR)/game
TEST_BUILD 	:= $(TEST_DIR)/test

CC 			:= gcc
CC_SRC 	 	:= $(wildcard $(SRC_DIR)/*.c)
CC_TESTS	:= $(wildcard $(TEST_DIR)/*.c)
CC_FLAGS 	:= -mwindows $(SDL_FLAGS) -I $(INCLUDE_DIR)  #-DDK_DEBUG=DK_DEBUG

OBJECTS 		:= $(patsubst %.c, %.o, $(CC_SRC))
TEST_OBJECTS 	:= $(patsubst %.c, %.o, $(CC_TESTS))
TEST_FLAGS 		:= -Wall -g

.PHONY: all run clear test

all: $(OBJECTS) $(BUILD)

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(BUILD): $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $@

run:
	cp $(LIBS_DIR)/*.dll $(BUILD_DIR)	
	$(BUILD)

%.test.o: %.test.c
	$(CC) $(TEST_FLAGS) -c $< -o $@

$(TEST_BUILD): $(TEST_OBJECTS)
	$(CC) $(TEST_FLAGS) $(TEST_OBJECTS) -o $@

test: $(TEST_OBJECTS) $(TEST_BUILD)
	$(TEST_BUILD)

clear:
	rm -rf $(OBJECTS) $(BUILD)
	