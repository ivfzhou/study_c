CC = gcc
CFLAGS = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 --all-warnings -pedantic -Winline -O0 -Wall -g3 \
	-Wno-unused-variable -Wno-unused-function
CFLAGS_RELEASE = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 -O3 -g0
SOURCES = xor_codec.c main.c
HEADERS = xor_codec.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = xor_codec

CLEAN_COMMAND = rm -f $(OBJECTS) $(TARGET) lib_$(TARGET).a;
ifeq ($(OS), Windows_NT)
	HAS_SH = $(shell sh.exe --version > NUL 2>&1 && echo 1 || echo 0)
	ifeq ($(HAS_SH), 0)
		CLEAN_COMMAND = del /Q  $(OBJECTS) $(TARGET).exe lib_$(TARGET).a;
	endif
endif

.PHONY: build install uninstall clean test debug

build:
	@$(CC) $(CFLAGS_RELEASE) -o $(TARGET) $(SOURCES)
	@$(CC) $(CFLAGS_RELEASE) -c -o lib_$(TARGET).a $(subst main.c,,$(SOURCES))
install: build
	@sudo cp lib_$(TARGET).a /usr/local/lib/
	@sudo cp $(TARGET) /usr/local/bin/
	@sudo cp $(HEADERS) /usr/local/include/
uninstall:
	@sudo rm -f /usr/local/lib/lib_$(TARGET).a
	@sudo rm -f /usr/local/bin/$(TARGET)
	@for f in $(TARGET); do sudo rm -f /usr/local/include/$$f.h; done
clean:
	@$(CLEAN_COMMAND)
test:
	@echo do nothing
debug: $(TARGET)
%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^
