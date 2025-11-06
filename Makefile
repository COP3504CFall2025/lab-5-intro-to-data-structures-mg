build:
	g++ -Wall -Werror -Wextra -std=c++20  main.cpp -o run.out

build_test:
	g++ -std=c++20  -g main.cpp -o run.out

run:
	./run.out

clean:
	rm ./run.out

