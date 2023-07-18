TARGET = disas

OBJDIR = obj
SRCDIR = src

CC = gcc
CFLAGS = -g
LDFLAGS = -g -lm

SOURCES     := $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS     := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<