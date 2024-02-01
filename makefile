target:
	gcc -g game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wextra -o bin

run:
	./bin