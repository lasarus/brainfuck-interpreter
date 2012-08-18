CC := gcc
CCFLAGS := -pedantic -Wall -Werror -g -lSDL -lSDL_image -lm -lGL

SRCDIRS := src
SOURCES := $(foreach DIR, $(SRCDIRS), $(wildcard $(DIR)/*.c))
TARGET := bin/FreeEvolution

.PHONY: all
.PHONY: clean

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(@D)
	$(CC) -o $(TARGET) $(SOURCES) $(CCFLAGS)
