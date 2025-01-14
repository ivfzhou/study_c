# Copyright (c) 2023 ivfzhou
# clib is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.

.PHONY:
testall: array_list_test circle_linked_list_test double_linked_list_test linked_list_test polynomial_test static_linked_list_test string_test stack_test circle_queue_test linked_queue_test list_test

%: %.c
	@gcc -std=c18 --all-warnings --pedantic -finput-charset=utf-8 -fexec-charset=utf-8 $^ common.c -o $@
	@./$@
	@echo "$@ end"

polynomial_test: polynomial_test.c list.c static_linked_list.c double_linked_list.c circle_linked_list.c linked_list.c array_list.c common.c
	@gcc -std=c18 --all-warnings --pedantic -finput-charset=utf-8 -fexec-charset=utf-8 $^ -o polynomial_test
	@./polynomial_test
	@echo "polynomial_test end"

list_test: static_linked_list.c double_linked_list.c circle_linked_list.c linked_list.c array_list.c list_test.c common.c
	@gcc -std=c18 --all-warnings --pedantic -finput-charset=utf-8 -fexec-charset=utf-8 $^ -o list_test
	@./list_test
	@echo "list_test end"

.PHONY:
clean: 
	@rm *_test
