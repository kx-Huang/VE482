CC = clang
CFLAGS = -std=gnu11 -O2 -Wall -Werror -Wconversion -pedantic -Wno-unused-result
MCFLAGS = -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
EX1_SRC = list.c sort.c ui.c
MAIN_CMD = main_cmd.c
MAIN_MENU = main_menu.c
EX1_H = *.h
CMD = cmd
MENU = menu

.PHONY: clean

all: $(CMD) $(MENU)
	@echo EX1 successfully constructed

$(CMD): $(EX1_SRC) $(EX1_H)
	$(CC) $(CFLAGS) $(MCFLAGS) -o $(CMD) $(EX1_SRC) $(MAIN_CMD)

$(MENU): $(EX1_SRC) $(EX1_H)
	$(CC) $(CFLAGS) $(MCFLAGS) -o $(MENU) $(EX1_SRC) $(MAIN_MENU)

clean:
	$(RM) *.o *.a $(CMD) $(MENU) *.txt
