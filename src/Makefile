TARGET = SmartCalc

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
OS = $(shell uname)
CONTROLLER = smart_calc
MODULES = $(wildcard under_hood/*.c)
OBJECTS = $(patsubst %.c, %.o, $(MODULES))
TEST_CONTROLLER = test_controller
TEST_FUNC = functions_test

ifeq ($(OS), Linux)
	LDLIBS = -lcheck_pic -pthread -lrt -lm -lsubunit
else
	LDLIBS = -lcheck -lm
endif

all: clean install

%.o:%.c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $< $(LDLIBS) -o $(patsubst under_hood%, obj%, $@)

$(CONTROLLER).o: $(CONTROLLER).c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $(CONTROLLER).c $(LDLIBS) -o obj/$(CONTROLLER).o

install: 
	@echo "Wait a minute, your calculator is installing"
	@mkdir -p ../build
	@cd front && qmake && make && make clean && rm -rf Makefile && mv S21_Smart_Calc.app ../../build/$(TARGET).app
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "Installation complete successfully"

uninstall:
	@rm -rf ~/Desktop/SmartCalc.app ../build
	@echo "You deleted the SmartCalc"

dvi:
	@open ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist 
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md
	@echo "Archiving was successful"

test: $(CONTROLLER).o $(OBJECTS)
	@mkdir -p tests/log
	@$(CC) $(CFLAGS) tests/test_controller.c $(LDLIBS) obj/*.o -o $(TEST_CONTROLLER)
	@$(CC) $(CFLAGS) tests/functions_test.c $(LDLIBS) obj/*.o -o $(TEST_FUNC)
	@mv $(TEST_CONTROLLER) ./tests && mv $(TEST_FUNC) ./tests
	@echo "Tests for functions start"
	@tests/$(TEST_FUNC)
	@echo "Tests for controller start"
	@tests/$(TEST_CONTROLLER)

gcov_report: $(CONTROLLER).o $(OBJECTS)
	@echo "HTML report is generated"
	@$(CC) --coverage $(CFLAGS) ./tests/functions_test.c $(LDLIBS) ./under_hood/*.c smart_calc.c -o ./tests/$(TEST_FUNC)
	@./tests/$(TEST_FUNC)
	@mkdir -p ./tests/functions_gcov
	@mv *.gcno ./tests/functions_gcov && mv *.gcda ./tests/functions_gcov 
	@lcov -t "test_coverage" -o coverage.info -c -d .
	@$(CC) --coverage $(CFLAGS) ./tests/test_controller.c $(LDLIBS) ./under_hood/*.c smart_calc.c -o ./tests/$(TEST_CONTROLLER)
	@./tests/$(TEST_CONTROLLER)
	@mkdir -p ./tests/controller_gcov
	@mv *.gcno ./tests/controller_gcov && mv *.gcda ./tests/controller_gcov 
	@lcov -t "test_coverage" -o coverage.info -c -d .
	@genhtml -o report coverage.info
	@open report/index.html
	@rm -rf *.gcda *.gcno report/coverage.info tests/controller_gcov tests/functions_gcov

clean:
	@rm -rf tests/log/*.log tests/$(TEST_CONTROLLER) tests/$(TEST_FUNC) obj *.dSYM **/*.dSYM log test_coverage.info

fclean: clean
	@rm -rf ../build ../dist ~/Desktop/$(TARGET).app controller_tests_vg.log module_tests_tests_vg.log report coverage.info

.PHONY: all install uninstall dvi dist test gcov_report valgrind_check style_check format_style fonts clean fclean