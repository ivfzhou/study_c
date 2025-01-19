CC = gcc
CFLAGS = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 --all-warnings -pedantic -Winline -O0 -Wall -g3 \
	-Wno-unused-variable -Wno-unused-function
TARGET = main
SOURCES = another_program.c third_program.c program.c main.c
OBJECTS = $(SOURCES:.c=.o)
DEL_PARAMETERS = $(OBJECTS) $(TARGET).exe
RM_PARAMETERS = $(OBJECTS) $(TARGET)

CLEAN_COMMAND = rm -f $(RM_PARAMETERS);
ifeq ($(OS), Windows_NT)
	HAS_SH = $(shell sh.exe --version > /dev/null 2>&1 && echo 1 || echo 0)
	ifeq ($(HAS_SH), 0)
		CLEAN_COMMAND = del /Q $(DEL_PARAMETERS);
	endif
endif

.PHONY: clean all install run

all: $(TARGET)
%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^
install:
	@echo 'do nothing'
clean:
	@$(CLEAN_COMMAND)
run: all
	@./$(TARGET)
