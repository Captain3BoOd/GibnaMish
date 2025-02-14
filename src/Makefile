ifeq ($(OS), Windows_NT)
	uname_S := Windows
else
	uname_S := $(shell uname -s)
endif

ifeq ($(uname_S), Darwin)
	TARGET = -mcpu=apple-a14
else
	TARGET = -march=native
endif

CXX ?= g++
CXXFLAGS = -Wall -std=c++20 -static -O3 -DNDEBUG -mtune=native -Wcast-qual -lm -fno-exceptions -fno-rtti -Wextra -Wno-unused-variable -Wno-unused-result -Wno-unused-but-set-variable -Wno-maybe-uninitialized -pedantic -funroll-loops -flto

ifneq ($(findstring clang++,$(CXX)),)
	ifeq ($(uname_S), Windows)
		# CXXFLAGS +=
	else
		CXXFLAGS += -fPIC -lm -pie
	endif
else ifneq ($(findstring g++,$(CXX)),)
	CXXFLAGS += -static-libgcc -static-libstdc++ -pie
endif

OBJ_DIR := obj
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

GibnaMish: $(OBJ_DIR) $(OBJS)
	$(CXX) -o GibnaMish $(OBJS) $(CXXFLAGS)
ifeq ($(OS), Windows_NT)
	-rmdir /S /Q $(OBJ_DIR)
else
	rm -rf $(OBJ_DIR)
endif

$(OBJ_DIR):
ifeq ($(OS), Windows_NT)
	mkdir $(OBJ_DIR)
else
	mkdir -p $(OBJ_DIR)
endif

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -flto $(TARGET) -std=c++20 -Wall $< -o $@

clean:
ifeq ($(OS), Windows_NT)
	-del /Q $(OBJ_DIR)\*.o GibnaMish.exe
	-rmdir /S /Q $(OBJ_DIR)
else
	rm -f $(OBJ_DIR)/*.o GibnaMish
	rm -rf $(OBJ_DIR)
endif