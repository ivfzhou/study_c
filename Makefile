run: align.c array.c assert.c bit_field.c bitwise.c bitwise_negation.c const.c enum.c flow_statement.c func.c generic.c io.c macro.c main.c sort.c string.c struct.c type.c typedef.c union.c varargs.c variable_scope.c xor_codec.c
	@gcc -std=c18 -finput-charset=utf-8 -fexec-charset=utf-8 --all-warnings -pedantic $^ -o cc
	@./cc

clean:

all:
