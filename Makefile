CXX = g++
TARGET = play
LDFLAGS = -static-libstdc++ -static-libgcc
CXXFLAGS = -std=c++17 -g -Wall 

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -Dmain=SDL_main 
	LDFLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
else 
	CXXFLAGS += $(shell sdl2-config --cflags)
	LDFLAGS += -lpthread $(shell sdl2-config --libs)
endif

INCLUDE_FILES := $(wildcard *.h)
SRC_FILES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRC_FILES))

.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) ${CXXFLAGS} ${LDFLAGS}

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)