.PHONY: all clean

NAME=basic-shell
SHELL_NAME="Basic Shell"
SHELL_VERSION=0.0.1

SRC=src
OBJ=obj

C_FILES=$(wildcard $(SRC)/*.c)
OBJECTS=$(C_FILES:$(SRC)/%.c=$(OBJ)/%.o)

CFLAGS=-DSHELL_VERSION=\"$(SHELL_VERSION)\" -DSHELL_NAME=\"$(SHELL_NAME)\" -Iinclude/

all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $^ -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	gcc -c $^ -o $@ $(CFLAGS)

clean:
	rm $(OBJ)/* 
	rm $(NAME)
