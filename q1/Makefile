# Makefile of #3 exercise - Semester A (winter) 2019

.PHONY: all test clean

OS := $(shell uname)
CC:= @gcc
CFLAGS:= -std=gnu11 -Wall
TIME = $(shell date +"%T.%3N")

ifneq (,$(findstring CYGWIN,$(OS)))
  EXT = .exe
else
  EXT = .out
endif

SRC_DIR:= src
SRC:= $(wildcard $(SRC_DIR)/*.c)
OBJ:= $(SRC:.c=.o) 
PROG_LIST:= $(SRC:.c=$(EXT)) 
EXEC= $(shell cat execute.tmp | head -1)

all: $(PROG_LIST) test

%$(EXT): %.o
	@echo ===========================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===========================================================
	
	$(CC) $< $(CFLAGS) -o $(@F)
	@echo $(@F) >> execute.tmp
	
	@echo ===========================================================
	@echo -e Compilation of target "\\e[5;41m$@\\e[0m" started at "\\e[5;41m$(TIME)\\e[0m"
	@echo ===========================================================

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@
	
.PRECIOUS: $(OBJ)

test:
	@echo ===============================================================
	@echo -e Execution of "\\e[5;41m$@\\e[0m" "\\e[5;41m$(PROG)\\e[0m" started at: "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	@./$(EXEC) abc xyz out.log < in.txt 2> err.log
	@rm -f execute.tmp
	@echo ===============================================================
	@echo -e Execution of "\\e[5;41m$@\\e[0m" "\\e[5;41m$(PROG)\\e[0m" finished at: "\\e[5;41m$(TIME)\\e[0m"
	@echo ===============================================================
	@echo
	@echo
	@echo ===============================================================
	@echo -e "\\e[1;43mResults:\\e[0m"
	@echo ===============================================================
	@cat out.log
	
clean:
	@rm -f $(SRC_DIR)/*.o *.exe *.log *.tmp
	@echo ===============================================================	
	@echo Binary,Obj, Log and Tmp files were cleaned!
	@echo ===============================================================