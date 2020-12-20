SHELL_NAME=basic-shell
SHELL_VERSION=0.0.1

all: $(SHELL_NAME)

$(SHELL_NAME): shell.o function.o main.o
	gcc $^ -o $@

shell.o: shell.c
	gcc -c $^ -o $@ -DSHELL_VERSION=\"$(SHELL_VERSION)\"

function.o: function.c
	gcc -c $^ -o $@

main.o: main.c
	gcc -c $^ -o $@

clean:
	rm *.o 
	rm $(SHELL_NAME)
