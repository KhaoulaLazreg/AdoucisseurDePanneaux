CC := gcc
#CFLAGS := -std=gnu99 -O2 -I.
CFLAGS := -std=gnu99 -Wall -g -I.

LD := gcc
LDFLAGS := -L.

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)
OUTPUT := adoucisseur

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) $(OUTPUT)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^