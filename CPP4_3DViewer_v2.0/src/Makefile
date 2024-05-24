PROJECT			=s21_3dviewer_v2
CC					=gcc
GCOV				=gcov
CFLAGS			=-Wall -Werror -Wextra -pedantic -std=c++17
R_CFLAGS		=-Werror -O2
PROFILE_FLAGS=-fprofile-arcs -ftest-coverage
COV_FLAGS		=--coverage -g#-fno-inline -fno-inline-small-functions -fno-default-inline -O0#-O1
GCONV_FLAGS	=-r . --html --html-details -d
TST_FLAGS		=$(shell pkg-config --cflags --libs check)#		#how flags needed to check lib
L_FLAG			=-fsanitize=address#													#check memory usage
INCLUDE_LIBS=-lstdc++#-lfcgi -lgtest
LDFLAGS			=
COL_RED			=| awk '{ print "\033[1;31m" $$0"\033[0m"}'
COL_GREEN		=| awk '{ print "\033[1;32m" $$0"\033[0m"}'

INSTALL_DIR	=../install#									dir with files to install
BUILD_DIR		=../build#										dir with build files
DIST_DIR		=../dist#											dir with distributive files
DOC_DIR			=../doc#												dir with documentation's files

STATIC_LIB	=$(PROJECT).a#								#make the static lib
DYNAMIC_LIB	=$(PROJECT).so#								#make the dynamic lib
EXECUTABLE	=$(PROJECT).app#							#make the app
RELEASE			=static

MDIR				=./#												#main src dir
TDIR				=../tests/#									#tests src dir
DDIR				=../debug/#									#debug src dir
TSTLOG_DIR	=./tests_log/#							#folder for tests logging
CTRLDIR			=./controller/#							#controller src dir
MODELDIR		=./model/#										#model src dir

# MAIN_C		=$(MDIR)$(PROJECT).cpp#						#main src file
TEST_C		=$(TDIR)$(PROJECT)_tests.cc#				#src for testing
DEBUG_C		=$(DDIR)debug.cc#										#src for debuging

MAIN_SRC	=$(wildcard $(MDIR)*.cc)#					#exec for app
TEST_SRC	=$(wildcard $(TDIR)*tests.cc)#			#exec for tests 
DBG_SRC		=$(wildcard $(DDIR)*debug.cc)#			#exec for debuging
HEADERS		=$(wildcard $(MDIR)*.h)
LIB_SRC		=$(wildcard $(MODELDIR)*.cc) $(wildcard $(CTRLDIR)*.cc)
THEADERS	=$(TEST_C:.cc=.h)
DHEADERS	=$(DEBUG_C:.cc=.h)
ALL_C			=$(MAIN_SRC) $(TEST_SRC) $(DBG_SRC)
ALL_H			=$(HEADERS) $(THEADERS) $(DHEADERS)
ALL_SRC		=$(ALL_C) $(ALL_H) $(LIB_SRC)

MOBJECTS	=$(LIB_SRC:.cc=.o)#								#obj files of PROJECT
COBJECTS	=$(LIB_SRC:.cc=.co)#							#obj files with coverage
TOBJECTS	=$(TEST_SRC:.cc=.o)#								#obj files of tests
DOBJECTS	=$(DBG_SRC:.cc=.o)#								#obj files of debug


TEXECUTABLE	=$(TEST_C:.cc=.app)#							#make tests app
DEXECUTABLE	=$(DEBUG_C:.cc=.app)#						#make debug app

PLATFORM	=$(shell uname -s)
ifeq ($(PLATFORM), Darwin)
	OPEN	=open
	LEAK_CHECK +=CK_FORK=no leaks -atExit -- ./$(TEXECUTABLE) > $(TSTLOG_DIR)RESULT_VALGRIND.log
else
	OPEN	=xdg-open
	LEAK_CHECK +=CK_FORK=no valgrind \
	--tool=memcheck \
	--trace-children=yes \
	--track-fds=yes \
	--leak-check=yes \
	--show-leak-kinds=all \
	--track-origins=yes \
	--error-exitcode=1 \
	--verbose \
	--log-file=$(TSTLOG_DIR)RESULT_VALGRIND.log \
	./$(TEXECUTABLE) > $(TSTLOG_DIR)test_result.log
endif

.SUFFIXES: .cc .co
.PHONY: all build rebuild install dvi dist uninstall clean mem_leaks style_check sanitizer tests gcov_report debug debug_with_lib debug_without_sanitize debug_app push commit echo debug_lib valgrind_debug unit_test cicd_valgrind

all: clean build

build: view

rebuild: clean all

model_lib: $(RELEASE)

install: build
	@mkdir -p $(INSTALL_DIR)
	@cp -rv $(BUILD_DIR)/* $(INSTALL_DIR)$(COL_GREEN)
	@rm -fr $(BUILD_DIR)$(COL_RED)

dvi:
	@cd .. && doxygen
	$(OPEN) $(DOC_DIR)/html/index.html

# dist: $(RELEASE)
dist: build
	@mkdir -vp $(DIST_DIR)
	tar -czvf $(DIST_DIR)/$(PROJECT).tar.gz $(BUILD_DIR)/3D_Viewer.app$(COL_GREEN)
	@rm -frv $(BUILD_DIR)$(COL_RED)


uninstall:
	@rm -rvf $(INSTALL_DIR)$(COL_RED)

$(RELEASE): $(STATIC_LIB)
	@mkdir -vp $(BUILD_DIR)
	@cp -v $(STATIC_LIB) $(HEADERS) $(BUILD_DIR)$(COL_GREEN)

$(STATIC_LIB): $(MOBJECTS)								#make clean lib for enterprise
	@ar rsv $@ $^
	@rm -fv $^$(COL_RED)

clean:
	@rm -rfv $(MOBJECTS) $(DOBJECTS) $(TOBJECTS) $(COBJECTS) $(TEXECUTABLE) $(DEXECUTABLE)$(COL_RED)
	@rm -rvf $(STATIC_LIB) $(DYNAMIC_LIB) $(EXECUTABLE)$(COL_RED)
	@rm -rf $(TSTLOG_DIR) tests
	@rm -f $(MDIR)*.gc?? $(MODELDIR)*.gc?? $(CTRLDIR)*.gc??
	@rm -f $(DDIR)*.gc??
	@rm -f *.gcov
	@rm -rfv report*$(COL_RED)
	@rm -fv *.app *.a *.so$(COL_RED)
	@rm -rfv $(BUILD_DIR)*$(COL_RED)
	@rm -rfv $(INSTALL_DIR)*$(COL_RED)
	@rm -rfv $(DOC_DIR)$(COL_RED)
	@rm -rfv $(DIST_DIR)$(COL_RED)
	@rm -rfv *.s$(COL_RED)
	@rm -rfv CMakeLists.txt.user$(COL_RED)
	@echo "\033[1;42m CLEAN IS DONE \033[0m"

.cc.co:#												#make obj files with coverage
	$(CC) $(CFLAGS)  $(TST_FLAGS) $(COV_FLAGS) -c $< -o $@ 

.cc.o:#												#make obj files for enterprise
	$(CC) $(R_CFLAGS) -c $< -o $@

mem_leaks: clean tests								#check possible memory leaks
	@mkdir -pv $(TSTLOG_DIR)
	$(LEAK_CHECK)
	@tail -n 7 $(TSTLOG_DIR)RESULT_VALGRIND.log$(COL_GREEN)

style_check:
	@cp -v ../materials/linters/.clang-format .
	cppcheck --check-config --enable=all --library=posix --std=c++17 --suppress=missingIncludeSystem $(ALL_SRC)
	@clang-format --version
	clang-format -n --Werror $(ALL_SRC)
	@rm -v .clang-format

sanitizer: $(MAIN_SRC) $(TEST_SRC)					#another check memory leaks
	$(CC) $(CFLAGS) $(L_FLAG) -g $^ -lgtest -o $(TEXECUTABLE) $(INCLUDE_LIBS) $(TST_FLAGS)
	./$(TEXECUTABLE)

tests: clean style_check $(COBJECTS) $(TOBJECTS)#	#make lib with debug info and make executable tests and run it
	ar rsv $(STATIC_LIB) $(COBJECTS)
	$(CC) $(CFLAGS) $(TOBJECTS) -lgtest -o $(TEXECUTABLE) -L. $(STATIC_LIB) $(INCLUDE_LIBS) $(PROFILE_FLAGS) $(TST_FLAGS)
	@rm -fv $(MDIR)*.co *.co$(COL_RED)
	@rm -fv $(TDIR)*.o *.o$(COL_RED)
	./$(TEXECUTABLE)

only_test: clean style_check $(COBJECTS) $(TOBJECTS)#	#make lib with debug info and make executable tests and run it
	ar rsv $(STATIC_LIB) $(COBJECTS)
	$(CC) $(CFLAGS) $(TOBJECTS) -lgtest -o $(TEXECUTABLE) -L. $(STATIC_LIB) $(INCLUDE_LIBS) $(PROFILE_FLAGS) $(TST_FLAGS)
	@rm -fv $(MDIR)*.co *.co$(COL_RED)
	@rm -fv $(TDIR)*.o *.o$(COL_RED)
	./$(TEXECUTABLE) --gtest_filter=$(test)
# ./$(TEXECUTABLE) --gtest_list_tests --help


gcov_report: clean tests								#make and present test coverage report in html
	@mkdir -pv $(TSTLOG_DIR)
	$(GCOV) $(LIB_SRC)|grep --color=always -E '$$|.+%.+'
	$(GCOV) -a -f $(LIB_SRC:.c=.gcno) >> $(TSTLOG_DIR)/coverage.txt
	geninfo $(LIB_SRC:.c=.gcda) -b . -o $(TSTLOG_DIR)/coverage.info
	genhtml --title $(PROJECT) -o report --legend $(TSTLOG_DIR)/coverage.info
	@rm -fv *.gc??
	$(OPEN) report/index.html

cicd_gcov_report: tests								#make and present test coverage report in html
	@mkdir -pv $(TSTLOG_DIR)
	$(GCOV) $(LIB_SRC)|grep --color=always -E '$$|.+%.+'
	$(GCOV) -a -f $(LIB_SRC:.c=.gcno) >> $(TSTLOG_DIR)/coverage.txt
	geninfo $(LIB_SRC:.c=.gcda) -b . -o $(TSTLOG_DIR)/coverage.info
	genhtml --title $(PROJECT) -o report --legend $(TSTLOG_DIR)/coverage.info

debug_with_lib: clean style_check $(COBJECTS)
	ar rsv $(STATIC_LIB) $(COBJECTS)
	$(CC) $(CFLAGS) $(COV_FLAGS) -c $(DBG_SRC) -o $(DOBJECTS)
	$(CC) $(CFLAGS) $(COV_FLAGS) $(DOBJECTS) -o $(DEXECUTABLE) -L. $(STATIC_LIB) $(INCLUDE_LIBS) $(PROFILE_FLAGS) $(TST_FLAGS) $(L_FLAG)
	@rm -rfv $(DOBJECTS) $(COBJECTS) $(TOBJECTS)
	./$(DEXECUTABLE)

debug: clean style_check $(COBJECTS)
	@rm -fv *.gc??$(COL_RED)
	$(CC) $(CFLAGS) -g -c $(DBG_SRC) -o $(DOBJECTS)
	$(CC) $(CFLAGS) $(DOBJECTS) $(COBJECTS) -o $(DEXECUTABLE) $(COV_FLAGS) $(L_FLAG) -lm $(INCLUDE_LIBS)
	@rm -rfv $(DOBJECTS) $(COBJECTS)$(COL_RED)
	./$(DEXECUTABLE)

debug_without_sanitize: clean style_check $(COBJECTS)
	@rm -fv *.gc??
	$(CC) $(CFLAGS) -g -c $(DBG_SRC) -o $(DOBJECTS)
	$(CC) $(CFLAGS) $(DOBJECTS) $(COBJECTS) $(INCLUDE_LIBS) -o $(DEXECUTABLE) $(COV_FLAGS)
	@rm -rfv $(DOBJECTS) $(COBJECTS)
	./$(DEXECUTABLE)

#debug_app: clean style_check $(COBJECTS)
#	@rm -fv *.gc??
#	$(CC) $(CFLAGS) $(COBJECTS) $(INCLUDE_LIBS) -o $(EXECUTABLE) $(COV_FLAGS) $(L_FLAG)
#	@rm -rfv $(COBJECTS)
#	./$(EXECUTABLE)

push: clean
	git push origin
	git push mygitserver
#	git push school21

commit: clean
	git commit -am "$(shell git branch --show-current): $(m)"
	git push origin
	git push mygitserver
#	git push school21

echo:
# $(info $(MAIN_SRC))
# $(warning $(TEST_SRC))
# $(info $(DBG_SRC))
# $(info $(HEADERS) $(THEADERS) $(DHEADERS))
# $(info $(MOBJECTS) $(COBJECTS) $(TOBJECTS) $(DOBJECTS))
# $(info $(STATIC_LIB) $(DYNAMIC_LIB) $(EXECUTABLE) $(TEXECUTABLE) $(DEXECUTABLE))
# $(info $(ALL_SRC))
#	$(info $(LIB_SRC))
	$(info $(MOBJECTS))

debug_lib: 
	$(CC) $(CFLAGS) -c $(DBG_SRC) -o $(DOBJECTS)
	$(CC) $(CFLAGS) $(DOBJECTS) $(INCLUDE_LIBS) -o $(DEXECUTABLE) -L. $(STATIC_LIB) -lm
	@rm -rfv $(DOBJECTS) $(COBJECTS)$(COL_RED)
	./$(DEXECUTABLE)

valgrind_debug:
	@mkdir -pv $(TSTLOG_DIR)
	valgrind \
	--tool=memcheck \
	--trace-children=yes \
	--track-fds=yes \
	--leak-check=yes \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=$(TSTLOG_DIR)RESULT_VALGRIND.log \
	./$(DEXECUTABLE) > $(TSTLOG_DIR)test_result.log
	tail -n 2 $(TSTLOG_DIR)RESULT_VALGRIND.log$(COL_GREEN)

cicd_unit_test: $(TOBJECTS)#	#make lib with debug info and make executable tests and run it
	$(CC) $(CFLAGS) $(TOBJECTS) $(INCLUDE_LIBS) -lgtest -o $(TEXECUTABLE) -L. $(STATIC_LIB) -lm $(PROFILE_FLAGS) $(TST_FLAGS)
	@rm -fv $(MDIR)*.co *.co$(COL_RED)
	@rm -fv $(TDIR)*.o *.o$(COL_RED)
	./$(TEXECUTABLE) --gtest_output="xml:tests/report.xml"

cicd_valgrind:
	valgrind \
	--tool=memcheck \
	--leak-check=yes \
	--track-origins=yes \
	--error-exitcode=1 \
	$(TEXECUTABLE)

asm_debug:
	g++ -O0 -g0 -masm=intel -S $(DBG_SRC)

debug_clang: clean style_check $(COBJECTS)
	@rm -fv *.gc??$(COL_RED)
	clang $(CFLAGS) -g -c $(DBG_SRC) -o $(DOBJECTS)
	clang $(CFLAGS) $(DOBJECTS) $(COBJECTS) -o $(DEXECUTABLE) $(COV_FLAGS) $(L_FLAG) -lm $(INCLUDE_LIBS)
	@rm -rfv $(DOBJECTS) $(COBJECTS)$(COL_RED)
	./$(DEXECUTABLE)

fixstyle:
	@cp -v ../materials/linters/.clang-format .
	cppcheck --check-config --enable=all --library=posix --std=c++17 --suppress=missingIncludeSystem $(ALL_SRC) 
	@clang-format --version
	clang-format -i --Werror $(ALL_SRC)
	@rm -v .clang-format

example: clean
	$(info $(wildcard $(MDIR)*.*))
#	@read 
#	$(info $(ALL_SRC))
#	# $(wildcard $(MDIR)*.*)
	@cp -v ../materials/linters/.clang-format .
	@cppcheck --check-config --enable=all --library=posix --std=c++17 --suppress=missingIncludeSystem $(wildcard $(MDIR)*.*)
	@clang-format -n --Werror $(wildcard $(MDIR)*.*)
	@rm -vfr .clang-format
	g++ $(CFLAGS) $(wildcard *.*) -o example.app $(COV_FLAGS) $(L_FLAG) -lm $(INCLUDE_LIBS)

.PHONY: view 
view:
	@mkdir -vp ../build
	@cd ../build && cmake ../src
	@cd ../build && $(MAKE)
#cmake --build ../build --config Debug
start: view 
	../build/3D_Viewer.app

LEAK_CHECK2 +=CK_FORK=no valgrind \
	--tool=memcheck \
	--trace-children=yes \
	--track-fds=yes \
	--leak-check=yes \
	--show-leak-kinds=all \
	--track-origins=yes \
	--error-exitcode=1 \
	--verbose \
	--log-file=$(TSTLOG_DIR)RESULT_VALGRIND.log \
	../build/SmartCalc.app > $(TSTLOG_DIR)test_result.log

valgrind_view: view
	@mkdir -pv $(TSTLOG_DIR)
	$(LEAK_CHECK2)
	@tail -n 7 $(TSTLOG_DIR)RESULT_VALGRIND.log$(COL_GREEN)

#################
#DISTNAME      = $(PROJECT).0.0
#DISTDIR = build/.tmp/$(DISTNAME)
#TAR           = tar -cf
#COMPRESS      = gzip -9f
#MOVE          = mv -f
#DEL_FILE      = rm -f
#COPY_FILE     = cp -f
##
#dist: distdir FORCE
#	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)
#
#distdir: FORCE
#	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
#	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
#	$(COPY_FILE) --parents /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
#	$(COPY_FILE) --parents ../gui/widget.h $(DISTDIR)/
#	$(COPY_FILE) --parents ../gui/main.cpp ../gui/widget.cpp $(DISTDIR)/
#
#FORCE:
#gcov_report: clean
#	$(CC) $(FLAGS) $(GCOV) -o gcov_main.app ./private_methods/*.cc ./methods/*.cc ./tests/test.cc -lgtest $(PKG_CONFIG)
#	./gcov_main.app
#	lcov -t "gcov_main.app" -c -d ./ --output-file $(INFO)
#	genhtml $(INFO) --output-directory ./coverage
#	rm -rf *.gcda *.gcno *.info
#	open coverage/index.html

#miniverter:											#check to build project
#	cd ../materials/build && bash run.sh
