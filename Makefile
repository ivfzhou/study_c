CC = gcc

# -g0：不生成调试信息。
# -g1：生成基本的调试信息，通常是最小的调试信息。
# -g3：生成更详细的调试信息，包括宏定义和其他信息。
# -Wall：启用所有的警告信息。
# -Winline：启用关于内联函数的警告。
# -O2：优化级别设置。
# -Dxxx=xxx：定义预处理宏。
CFLAGS = -std=c18 -finput-charset=utf-8 -fexec-charset=utf-8 --all-warnings -pedantic -Winline -O2 -Wall -g3

TARGET = main
SOURCES = align.c array.c assert.c bit_field.c bitwise.c bitwise_negation.c const.c enum.c flow_statement.c func.c \
	generic.c io.c macro.c main.c sort.c string.c struct.c type.c typedef.c union.c varargs.c variable_scope.c \
	xor_codec.c
OBJECTS = $(SOURCES:.c=.o)

ifeq ($(OS), Windows_NT)
	CLEAN_COMAND=del /Q $(OBJECTS) $(TARGET).exe;
else
	CLEAN_COMAND=rm -f $(OBJECTS) $(TARGET);
endif

.PHONY: clean all install run

all: $(TARGET)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^

install:

clean:
	@$(CLEAN_COMAND)

run: all
	@$(TARGET)
