
SRC := include/v8util.h src/v8util.cc
OBJ := libv8util.so
TEST := v8test
PREFIX := /usr/local
FLAGS := -Iinclude -I$(PREFIX)/include/v8
LINKS := -lv8
OUTDIR := out

test:
	@g++ $(SRC) $(FLAGS) $(LINKS) test.cc -o $(TEST)
	@$(TEST)
	@rm -rf $(TEST)

build:
	@if test -d; then rm -rf $(OUTDIR)/ && mkdir $(OUTDIR)/; else mkdir $(OUTDIR)/; fi;
	g++ -fpic -c $(SRC) $(FLAGS)
	@g++ $(SRC) $(FLAGS) $(LINKS) -shared -o $(OUTDIR)/$(OBJ)

install: test build
	@cp ./include/*.h $(PREFIX)/include
	@cp ./$(OUTDIR)/$(OBJ) $(PREFIX)/lib

.PHONY: test build