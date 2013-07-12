
V8 = deps/v8/out/native/libv8.dylib
SRC = include/v8-util.h src/v8-util.cc
FLAGS = -Iinclude -Ideps/v8/include -Ldeps/v8/src

test:
	@g++ $(V8) $(SRC) $(FLAGS) test.cc -o v8-util-test
	@v8-util-test
	@rm -rf v8-util-test

.PHONY: test