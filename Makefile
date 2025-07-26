./build/phonebook: ./build/main.o
	clang -o ./build/phonebook ./build/main.o

./build/main.o: ./src/main.c
	clang -c ./src/main.c -o ./build/main.o
