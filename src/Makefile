CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c++17 
FIN_FLAGS=-lstdc++
SANITIZE=-fsanitize=address -g
TST_LIBS=-pedantic -lgtest

ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt 
endif

LIB_NAME=s21_matrix_oop

SRCS=$(wildcard s21_*.cc)

OBJS=$(SRCS:.cc=.o)
 
TEST_SRCS=$(wildcard tests/test*.cc)

TEST_OBJS=$(TEST_SRCS:.cc=.o)

%.o: %.cc
	$(CC) $(FLAGS) -c $< -o $@

all: clean test

clean:
	rm -rf *.o tests/*.o test *.a *.gcno *.gcda *.gcov *.html *.css Main SANITIZE *.dSYM

clang-format:
	clang-format -i *.cc *.h tests/*.cc tests/*.h



$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a
	rm -rf *.o

test: clean $(LIB_NAME).a $(TEST_OBJS) check.o
	$(CC) $(FLAGS) $(TST_LIBS) $(FIN_FLAGS) $(TEST_OBJS) check.o $(LIB_NAME).a  -o test

sanitize: clean $(LIB_NAME).a $(TEST_OBJS) check.o
	$(CC) $(FLAGS) -pedantic -lgtest $(SANITIZE) -lstdc++ $(TEST_OBJS) check.o $(LIB_NAME).a  -o  SANITIZE

main: $(LIB_NAME).a main.o
	$(CC) $(FLAGS) $(FIN_FLAGS) $(LIB_NAME).a main.o -o Main
	./Main

add_coverage_flag:
	$(eval FLAGS += --coverage )

gcov_report: add_coverage_flag test 
	./test
	rm -rf tests/test_*.gcda tests/test_*.gcno check*.gcda check*.gcno
	gcov -b -l -p -c s21_*.gcno 
	gcovr  -o gcov_report.html --html --html-details 

#cppcheck --enable=all --suppress=missingIncludeSystem src/