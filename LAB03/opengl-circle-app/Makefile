CC = g++
CXXFLAGS = -lglut -lGLU -lGL -lGL -lGLEW -lglfw -lfreetype -I/usr/include -I/usr/include/freetype2 -std=c++11
SRC = src/main.cpp src/ellipse.cpp src/triangle.cpp src/polygon.cpp src/text.cpp src/shader_utils.cpp
OBJDIR = obj
OBJ = $(SRC:src/%.cpp=$(OBJDIR)/%.o)
TARGET = labo3

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: src/%.cpp
	$(CC) $(CXXFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: all
	./$(TARGET)

re: clean run

.PHONY: all clean re run
