CC = g++
TARGET = play
SDLFLAGS = -lpthread $(shell sdl2-config --cflags --libs)
LDFLAGS = -static-libstdc++ -lstdc++ 
CFLAGS = -std=c++17 -g -Wall 

INCLUDE_FILES := $(wildcard *.h)
SRC_FILES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRC_FILES))

.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) ${LDFLAGS} ${SDLFLAGS}


.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)