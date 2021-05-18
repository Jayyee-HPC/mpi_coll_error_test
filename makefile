GCC = g++ -std=c++17 
MPICC = mpicxx -std=c++17 -g
MPICC_COLL = /home/jayyee/test/2105_coll_len/mpich/build/_inst/bin/mpicxx -std=c++17 -g
MPICH = /home/jayyee/temp/mpich/build/_inst/bin/mpicxx -std=c++17 -g

MAKE_DIR = $(PWD)
OBJ_DIR  := $(MAKE_DIR)/bin
APP_DIR  := $(MAKE_DIR)
TARGET   := prog
INCLUDE  := -Iinclude

SRC      :=                      \
   $(wildcard src/*.cpp)        

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(MPICH) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(MPICH) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/$(TARGET)
