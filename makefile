all:main
	g++ main.cpp -o main -std=c++17 -Wall -Wextra -Wpedantic -D_GNU_SOURCE -Werror=all -O2