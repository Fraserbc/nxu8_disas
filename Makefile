TARGET = disas

OBJDIR = obj
SRCDIR = src

CC = gcc
CFLAGS = -g
LDFLAGS = -g -lm

SOURCES     := $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS     := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))

DIRS := $(shell find ${SRCDIR} -type d)
DIRS := $(patsubst ${SRCDIR}%, ${OBJDIR}%, ${DIRS})

all: ${DIRS} $(TARGET)

${DIRS}:
	@mkdir -p $@

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<