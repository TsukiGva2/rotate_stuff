
.PHONY: all
all: rotate_stuff

rotate_stuff: main.c
	gcc -Ofast -std=c99 -Wshadow -fsanitize=address,undefined -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable main.c -o rotate_stuff -I./raylib-linux/include -L./raylib-linux/lib -l:libraylib.a -lm

.PHONY: debug
debug: main.c
	gcc -g -pg -std=c99 -Wshadow -fsanitize=address,undefined -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable main.c -o rotate_stuff -I./raylib-linux/include -L./raylib-linux/lib -l:libraylib.a -lm

.PHONY: clean
clean:
	rm -f rotate_stuff

