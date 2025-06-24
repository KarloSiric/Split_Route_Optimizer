CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -02 -Iinclude
LIBS = `pkg-config --cflags --libs cairo gtk+-3.0` -lcurl -lsqlite3 -lcjson

# DIRECTORIES
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.c $(SRCDIR)/*/*.c)
OBJECTS = $(SOURCES: $(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = split_optimizer

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/core
	mkdir -p $(OBJDIR)/api
	mkdir -p $(OBJDIR)/graphics
	mkdir -p $(OBJDIR)/ui
	mkdir -p $(OBJDIR)/utils

# Build target
$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

# Object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Commands
.PHONY: clean install run
clean:
	rm -rf $(OBJDIR) $(TARGET)

install:
	brew install cairo gtk+3 curl sqlite3 cjson pkg-config

run: $(TARGET)
	./$(TARGET)
