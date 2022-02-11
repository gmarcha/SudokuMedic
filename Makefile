all:	build
		./sudokuMedic grids/simple

build:
		clang -Wall -Wextra -Werror -I incs/ -o sudokuMedic -lm srcs/parser.c srcs/utils.c srcs/main.c