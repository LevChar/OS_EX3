# Makefile of #3 exercise - Semester A (winter) 2019

OS := $(shell uname)
CC = @gcc -std=c99
$ TIME = $(shell date +"%T.%3N")
SRC = $(wildcard *.c)
obj = $(SRC:.c=.o)
CFLAGS = -Wall
PROG = ex3_q2$(EXT)

ifneq (,$(findstring CYGWIN,$(OS)))
  EXT = .exe
else
  EXT =
endif

all : $(PROG) test

$(PROG) : $(obj)
	@echo ===========================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===========================================================
	
	@$(CC) $^ $(CFLAGS) -o $(PROG)
	
	@echo ===========================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===========================================================
	
clean:
	@rm -f $(PROG) *.exe out.log *.o
	@echo ===========================================================
	@echo Binary and Obj files were cleaned!
	@echo ===========================================================

test:
	@echo ===========================================================
	@echo -e Execution of "\\e[5;41m$@\\e[0m" "\\e[5;41m$(PROG)\\e[0m" started at: "\\e[5;41m$(TIME)\\e[0m"
	@echo ===========================================================
	
	@./$(PROG) > out.log
	
	@echo ===========================================================
	@echo -e Execution of "\\e[5;41m$@\\e[0m" "\\e[5;41m$(PROG)\\e[0m" finished at: "\\e[5;41m$(TIME)\\e[0m"
	@echo ===========================================================
	@echo
	@echo
	@echo ===========================================================
	@echo -e "\\e[1;43mResults:\\e[0m"
	@echo ===========================================================
	@cat out.log