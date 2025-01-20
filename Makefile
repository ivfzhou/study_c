CC = gcc

# -g0：不生成调试信息。
# -g1：生成基本的调试信息，通常是最小的调试信息。
# -g3：生成更详细的调试信息，包括宏定义和其他信息。
# -Wall：启用所有的警告信息。
# -Winline：启用关于内联函数的警告。
# -O2：优化级别设置。
# -Dxxx=xxx：定义预处理宏。
# -Wno-unused：禁用所有未使用的警告（包括函数、参数等）。
CFLAGS = -std=c18 -finput-charset=UTF-8 -fexec-charset=UTF-8 --all-warnings -pedantic -Winline -O0 -Wall -g3 \
	-Wno-unused-variable -Wno-unused-function

TARGET = main
SOURCES = alignment.c array.c assertion.c bit_field.c bitwise.c const.c enumeration.c flow_statement.c func.c \
	generic.c io.c macro.c sort.c string.c struct.c type.c typedef.c union.c varargs.c variable_scope.c main.c
OBJECTS = $(SOURCES:.c=.o)
DEL_PARAMETERS = $(OBJECTS) $(TARGET).exe
RM_PARAMETERS = $(OBJECTS) $(TARGET)

# 如果是 Windows 系统，且没有运行环境没有 sh.exe 可使用，则使用 del 命令清理文件。
# 否则使用 rm 命令清理文件。
CLEAN_COMMAND = rm -f $(RM_PARAMETERS);
ifeq ($(OS), Windows_NT)
	HAS_SH = $(shell sh.exe --version > NUL 2>&1 && echo 1 || echo 0)
	ifeq ($(HAS_SH), 0)
		CLEAN_COMMAND = del /Q $(DEL_PARAMETERS);
	endif
endif

.PHONY: debug clean

debug: $(TARGET)
# 编译每个源代码。
%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
# 链接代码。
$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^
clean:
	@$(CLEAN_COMMAND)
