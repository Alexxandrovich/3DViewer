FLAGS = -std=c++17 -Wall -Wextra -Werror
LFLAGS = -lm -lgtest
APPNAME = 3DViewer.app
TEX2DVI = texi2dvi

ifeq ($(shell uname), Linux)
	LFLAGS = -lm -lcheck -lsubunit
	APPNAME = 3DViewer
endif

all: clean uninstall install gcov_report

tests:
	g++ $(FLAGS) ./tests/s21_googletest.cc ./3DViewer/model/s21_3d_viewer.cc $(LFLAGS) -o test
	./test

gcov_report: clean add_coverage tests
	lcov -t "test" -o test.info -c -d . --no-external --ignore-errors inconsistent
	genhtml -o report test.info --ignore-errors inconsistent
	open report/index.html

install:
	mkdir build
	cd build && qmake ../3DViewer && make

uninstall:
	rm -rf build

dist:
	rm -rf dist.tar
	tar -czf dist.tar build/$(APPNAME)

dvi:
	$(TEX2DVI) readme.texi
	open ./readme.dvi

add_coverage:
	$(eval FLAGS += --coverage)

clean:
	rm -rf report html build
	rm -f *.o *.gcno *.gcda *.info *.out test
	rm -f dist.tar

style_check:
	clang-format -n --style=Google 3DViewer/*/*.h 3DViewer/*/*.cc tests/*.cc tests/*.h

style_fix:
	clang-format -i --style=Google 3DViewer/*/*.h 3DViewer/*/*.cc tests/*.cc tests/*.h

.PHONY:  clean tests gcov_report install uninstall dvi dist add_coverage all