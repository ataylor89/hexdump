clean:
	if [ -d bin ]; then rm bin/*; rmdir bin; fi;

install:
	if [ ! -d bin ]; then mkdir bin; fi;
	gcc src/main/*.c -I src/main -o bin/hexdump