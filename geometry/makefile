SOURCES=circle.cpp rectangle.cpp shape.cpp
OBJS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(OBJS) clean
	
$(OBJS):
	g++ -c $(SOURCES) 

clean:
	rm -rf *.o
