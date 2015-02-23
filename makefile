
TARGET= thebol
SOURCES=main.cpp tuki.cpp roi.cpp scenario.cpp tile.cpp aux.cpp
OBJS=$(SOURCES:.cpp=.o)  ./geometry/shape.o ./geometry/circle.o ./geometry/rectangle.o

all: $(SOURCES) $(TARGET) clean

$(TARGET):$(OBJS)
	g++  -g  $(OBJS) -lSDL -o $@
	
$(SOURCES:.cpp=.o):
	g++ -g -c $(SOURCES) 

clean:
	rm -rf *.o
