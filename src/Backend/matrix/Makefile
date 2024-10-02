#Makefile by Casscurs

# Цвета для оформления вывода
COLOR_TITLE = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m

NAME = s21_matrix_oop.a
SRC_FILES = $(wildcard *.cc)
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(patsubst %.cc, %.o, $(SRC_FILES))
DEP_FILES = $(patsubst %.cc, %.d, $(SRC_FILES))

TESTS_DIR = tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.cc)
TESTS_HEADERS = $(wildcard $(TESTS_DIR)*.h)
TESTS_OBJ = $(patsubst %.cc,%.o, $(TESTS_SRC))

CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -Werror -pedantic -g -I /opt/homebrew/Cellar/googletest/1.14.0/include # -fsanitize=address,undefined,unreachable \
# -fno-sanitize-recover

AR = ar rcs 
LIBS = -L/opt/homebrew/Cellar/googletest/1.14.0/lib -lgtest_main -lgtest -lpthread
COVERAGE = 

all : $(NAME)

gcovr_report : add_coverage test
	mkdir gcovr/
	gcovr --html-details gcovr/report.details.html
	rm -rf ./*.gc*
	open gcovr/report.details.html

add_coverage :
	$(eval COVERAGE += --coverage)

test : $(NAME) $(TESTS_OBJ)
	$(CC) $(CFLAGS) -c $(TESTS_SRC)
	$(CC) $(CFLAGS) $(COVERAGE) $(LIBS) $(NAME) -o $@ $(TESTS_OBJ)
	@echo "$(COLOR_TITLE)=== Running tests ===$(COLOR_RESET)"
	./test
	@echo "$(COLOR_TITLE)=====================$(COLOR_RESET)"

$(NAME) : $(OBJ_FILES)
	$(AR) $(NAME) $?
	@echo "$(COLOR_SUCCESS)=== Build complete ===$(COLOR_RESET)"

%.o : %.cc
	@echo "$(COLOR_TITLE)=== Compiling $< ===$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(COVERAGE) -c $< -o $@
	$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) $<
	@echo "$(COLOR_SUCCESS)=== Compilation successful ===$(COLOR_RESET)"

-include $(DEP_FILES)

obj : $(OBJ_FILES)

leaks: test
	leaks -atExit -- ./test

clean :
	@echo "$(COLOR_TITLE)=== Cleaning ===$(COLOR_RESET)"
	@rm -rf *.a *.o gcovr *.gcda *.gcno $(DEP_FILES) test
	@ cd ./tests && rm -rf *.a *.o *.gcda *.gcno *.d


cppcheck :
	@echo "$(COLOR_TITLE)=== Running cppcheck ===$(COLOR_RESET)"
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_FILES) $(HEADER_FILES) $(TESTS_SRC) $(TESTS_HEADERS)

format :
	@echo "$(COLOR_TITLE)=== Formatting code ===$(COLOR_RESET)"
	clang-format -i -style=Google $(SRC_FILES) $(HEADER_FILES) $(TESTS_SRC) $(TESTS_HEADERS)

check-format :
	@echo "$(COLOR_TITLE)=== Checking code formatting ===$(COLOR_RESET)"
	clang-format -n -style=Google $(SRC_FILES) $(HEADER_FILES) $(TESTS_SRC) $(TESTS_HEADERS)
	cpplint $(SRC_FILES) $(HEADER_FILES) $(TESTS_SRC) $(TESTS_HEADERS)

.PHONY : all gcovr_report add_coverage test leaks clean cppcheck format check-format obj