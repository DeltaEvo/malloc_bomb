malloc.dylib: src/common.c src/dyld.c Makefile
	clang -dynamiclib -fPIC -o malloc.dylib src/dyld.c

clean:
	rm malloc.so

.PHONY: clean
