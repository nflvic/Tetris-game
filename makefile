target:
	gcc game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o bin

run:
	./bin