AFL_CC = afl-clang-fast
AFL_CXX = afl-clang-fast++
AFL_CFLAGS = -Wall -g -fsanitize=fuzzer
INCLUDE_DIRS = -I./assimp/include
AFL_LDFLAGS = -L./assimp/lib -L./assimp/contrib/zlib

# TODO: Clean this up, the un-instrumented build of test was made speculatively to minimize extra memory usage when investigating the stack overflow errors
# that surfaced in the findings...
CC = clang
CXX = clang++
CFLAGS = -Wall -g
LDFLAGS = -L./uninstrumented/assimp/lib -L./assimp/contrib/zlib

LDLIBS = -l:libassimp.a -l:libzlibstatic.a

all: harness test

test: test.c
	$(CXX) $(CFLAGS) -o test test.c $(LDFLAGS) $(LDLIBS)

harness: harness.c
	$(AFL_CXX) $(AFL_CFLAGS) -o harness harness.c $(AFL_LDFLAGS) $(LDLIBS)

clean:
	rm -f test harness
