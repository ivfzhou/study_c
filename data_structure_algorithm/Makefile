# Copyright (c) 2023 ivfzhou
# clib is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.

CC = gcc
TARGET = data_structure_algorithm
PREFIX ?= /usr/local
CFLAGS_DEBUG = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 --all-warnings -pedantic -Winline -O0 -Wall -g3
CFLAGS_RELEASE = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 -O3 -g0
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
BUILD_SOURCES = $(filter-out %_test.c, $(SOURCES))
TEST_SOURCES = $(wildcard *_test.c)
TEST_TARGETS = $(patsubst %.c,%,$(TEST_SOURCES))
ifeq ($(OS), Windows_NT)
	TEST_TARGETS = $(patsubst %.c,%.exe,$(TEST_SOURCES))
endif
BUILD_OBJECTS = $(BUILD_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
LIB = lib_$(TARGET).a
CLEAN_COMMAND = rm -f $(BUILD_OBJECTS) $(LIB) $(TEST_OBJECTS) $(TEST_TARGETS);

.PHONY: build test install uninstall all debug clean

build:
	@for i in $(BUILD_SOURCES); do \
		$(CC) $(CFLAGS_RELEASE) -c -o $${i%.c}.o $$i; \
	done
	@ar rcs $(LIB) $(BUILD_OBJECTS)
test: build
	@for i in $(TEST_SOURCES); do \
		$(CC) $(CFLAGS_RELEASE) -o $${i%.c} $$i $(BUILD_OBJECTS); \
    done
	@for i in $(TEST_TARGETS); do \
		echo "start running $$i"; \
		./$$i; \
		echo "end running $$i"; \
	done
install: build
	@mkdir -p $(PREFIX)/lib/
	@cp $(LIB) $(PREFIX)/lib/
	@mkdir -p $(PREFIX)/include/
	@cp $(HEADERS) $(PREFIX)/include/
uninstall:
	@rm -f $(PREFIX)/lib/$(LIB)
	@for f in $(HEADERS); do rm -f $(PREFIX)/include/$$f; done

all: debug
debug: $(TARGET)
%.o: %.c
	@$(CC) $(CFLAGS_DEBUG) -c -o $@ $<
$(TARGET): $(OBJECTS)
	@echo "do nothings"
clean:
	@$(CLEAN_COMMAND)
