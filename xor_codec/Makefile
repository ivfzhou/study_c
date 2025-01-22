CC = gcc
TARGET = xor_codec
PREFIX ?= /usr/local
CFLAGS_DEBUG = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 --all-warnings -pedantic -Winline -O0 -Wall -g3
CFLAGS_RELEASE = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 -O3 -g0
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
LIB = lib_$(TARGET).a
CLEAN_COMMAND = rm -f $(OBJECTS) $(TARGET) $(LIB);

ifeq ($(OS), Windows_NT)
	CLEAN_COMMAND = rm -f $(OBJECTS) $(TARGET).exe $(LIB);
endif

.PHONY: build test install uninstall all debug clean

build:
	@for i in $(SOURCES); do \
		$(CC) $(CFLAGS_RELEASE) -c -o $${i%.c}.o $$i; \
	done
	@ar rcs $(LIB) $(subst main.o,,$(OBJECTS))
	@$(CC) $(CFLAGS_RELEASE) -o $(TARGET) $(OBJECTS)
test:
	@echo "do nothing"
install: build
	@cp $(LIB) $(PREFIX)/lib/
	@cp $(HEADERS) $(PREFIX)/include/
uninstall:
	@rm -f $(PREFIX)/lib/$(LIB)
	@for f in $(HEADERS); do rm -f $(PREFIX)/include/$$f; done

all: debug
debug: $(TARGET)
%.o: %.c
	@$(CC) $(CFLAGS_DEBUG) -c -o $@ $<
$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS_DEBUG) -o $@ $^
clean:
	@$(CLEAN_COMMAND)
