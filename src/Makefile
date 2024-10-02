#Makefile by Casscurs Hunturek

PROJECT_NAME = 3DViewer
VERSION = 2.0

# Цвета для оформления вывода
COLOR_TITLE = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m
# Исходники
NAME = viewer.a

SRC_FILES = $(wildcard ./Backend/model/*.cc) 
HEADER_FILES = $(wildcard ./Backend/model/*.h)

OBJ_FILES = $(patsubst %.cc, %.o, $(SRC_FILES))
DEP_FILES = $(patsubst %.cc, %.d, $(SRC_FILES))

MATRIX_OBJ_FILES = $(wildcard ./Backend/matrix/*.o)

CPP_FILES = $(wildcard ./3D_Viewer/*.cc)
CPP_HEADERS = $(wildcard ./3D_Viewer/*.h)
# Тесты
TESTS_DIR = Backend/model/model_tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.cc)
TESTS_OBJ = $(patsubst %.cc,%.o,$(TESTS_SRC))
# Флаги
CXX = g++ -std=c++17
CXXFLAGS = -Wall -Wextra -O2

AR = ar rcs
LIBS = -lgtest
# Документация .dvi
SRC_DIR = documentation
# Дистрибутируемый архив 
DIST_DIR = dist/$(PROJECT_NAME)-$(VERSION)
DIST_FILES = $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) $(CPP_HEADERS) $(TESTS_SRC) $(SRC_DIR)/html/index.html Makefile

all : tests

txt:
	mv models/katana.txt models/katana.obj
	mv models/pumpkin.txt models/pumpkin.obj
	mv models/skull.txt models/skull.obj
	mv Backend/model/model_tests/examples_for_tests/empty.txt Backend/model/model_tests/examples_for_tests/empty.obj
	mv Backend/model/model_tests/examples_for_tests/error.txt Backend/model/model_tests/examples_for_tests/error.obj
	mv Backend/model/model_tests/examples_for_tests/nenormal.txt Backend/model/model_tests/examples_for_tests/nenormal.obj
	mv Backend/model/model_tests/examples_for_tests/normal.txt Backend/model/model_tests/examples_for_tests/normal.obj

gcovr_report: clean add_coverage tests
	mkdir gcovr/
	gcovr --html-details gcovr/report.details.html
	rm -rf ./*.gc*
	open gcovr/report.details.html

add_coverage:
	$(eval CXXFLAGS += --coverage)

tests: $(NAME) $(TESTS_OBJ)
	$(CXX) $(CXXFLAGS) $(TESTS_OBJ) $(LIBS) $(NAME) -o $@
	./tests

$(NAME) : matrix_lib $(OBJ_FILES)
	$(AR) $(NAME) $(MATRIX_OBJ_FILES) $(OBJ_FILES)
	@echo "$(COLOR_SUCCESS)=== Build complete ===$(COLOR_RESET)"

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD

matrix_lib:
	@$(MAKE) -C ./Backend/matrix -f Makefile obj

matrix_lib_clean:
	@$(MAKE) -C ./Backend/matrix -f Makefile clean

include $(wildcard $(D_FILES))

install: $(NAME)
	cd 3D_Viewer && mkdir -p build && cd build && cmake .. && make
	mv 3D_Viewer/build ../src 
	
uninstall:
	rm -rf build 

dvi:
	rm -rf $(SRC_DIR)
	mkdir -p $(SRC_DIR)
	doxygen Doxyfile
	@mv html latex $(SRC_DIR)
	open documentation/html/index.html

undvi:
	@rm -rf $(SRC_DIR)

dist: dvi
	@echo "$(COLOR_TITLE)=== Creating distribution archive ===$(COLOR_RESET)"
	mkdir -p $(DIST_DIR)
	cp -r $(DIST_FILES) $(DIST_DIR)/
	tar czvf $(DIST_DIR).tar.gz -C dist $(PROJECT_NAME)-$(VERSION)/
	rm -r $(DIST_DIR)
	@echo "$(COLOR_SUCCESS)=== Distribution archive created ===$(COLOR_RESET)"

distclean:
	@rm -rf dist

clean : uninstall undvi distclean matrix_lib_clean
	@echo "$(COLOR_TITLE)=== Cleaning ===$(COLOR_RESET)"
	@rm -rf *.a *.o gcovr *.gcda *.gcno $(DEP_FILES) $(NAME) tests
	@rm -rf ./Backend/model/model_tests/*.d ./Backend/model/model_tests/*.o ./Backend/model/model_tests/*.gcda ./Backend/model/model_tests/*.gcno
	@rm -rf ./Backend/model/*.d ./Backend/model/*.o ./Backend/model/*.gcda ./Backend/model/*.gcno

cppcheck :
	@echo "$(COLOR_TITLE)=== Running cppcheck ===$(COLOR_RESET)"
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_FILES) $(HEADER_FILES) $(TESTS_SRC)

format :
	@echo "$(COLOR_TITLE)=== Formatting code ===$(COLOR_RESET)"
	clang-format -i -style=Google $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) $(CPP_HEADERS) $(TESTS_SRC)


check-format :
	@echo "$(COLOR_TITLE)=== Checking code formatting ===$(COLOR_RESET)"
	clang-format -n -style=Google $(SRC_FILES) $(HEADER_FILES) $(CPP_FILES) $(CPP_HEADERS) $(TESTS_SRC)

.PHONY : all clean cppcheck cpplint format check-format dvi undvi dist distclean start tests matrix_lib matrix_lib_clean
