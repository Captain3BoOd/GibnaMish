ifeq ($(OS), Windows_NT)
	uname_S := Windows
else
	uname_S := $(shell uname -s)
endif

ifeq ($(uname_S), Darwin)
	TARGET = -mcpu=apple-a14
else
	TARGET = -mtune=native
endif

CXX = g++
CXXFLAGS = -std=c++20 -static -O3 -DNDEBUG -Wall -Wcast-qual -fno-exceptions -fno-rtti -Wextra -pedantic -funroll-loops -flto
LDFLAGS = -flto -pthread -lstdc++ -static -Wl,--no-as-needed

OBJ_DIR := obj
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

GibnaMish: $(OBJ_DIR) $(OBJS)
	$(CXX) -o GibnaMish $(OBJS) $(CXXFLAGS) $(LDFLAGS)
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