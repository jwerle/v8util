
SRC := include/v8util.h src/v8util.cc
OBJ := libv8util.so
TEST := v8test
PREFIX := /usr/local
FLAGS := -Iinclude -I$(PREFIX)/include/v8 -lv8

test:
	g++ $(V8) $(SRC) $(FLAGS) test.cc -o $(TEST)
	@$(TEST)
	@rm -rf $(TEST)

build:
	@if test -d; then rm -rf out/ && mkdir out/; else mkdir out/; fi;
	g++ $(FLAGS) -fpic -c $(SRC)
	g++ $(V8) $(SRC) $(FLAGS) -shared -o out/$(OBJ)

install: test build
	cp ./include/*.h $(PREFIX)/include
	cp ./out/$(OBJ) $(PREFIX)/lib

.PHONY: test build