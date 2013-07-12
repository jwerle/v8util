
V8 := deps/v8/out/native/libv8.dylib
SRC := include/v8util.h src/v8util.cc
FLAGS := -Iinclude -Ideps/v8/include

test:
	g++ $(V8) $(SRC) $(FLAGS) test.cc -o v8-util-test
	@v8-util-test
	@rm -rf v8-util-test
	@echo

build:
	@if test -d; then rm -rf out/ && mkdir out/; else mkdir out/; fi;
	g++ $(FLAGS) -fpic -c $(SRC)
	g++ $(V8) $(SRC) $(FLAGS) -shared -o out/libv8util.so


.PHONY: test build