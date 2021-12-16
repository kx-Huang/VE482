CC = clang
CFLAGS = -std=gnu11 -O2 -Wall -Werror -Wconversion -pedantic -Wno-unused-result
MCFLAGS = -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
EX2_SRC = *.c
EX2_H = *.h
EX2 = ex2

.PHONY: clean

all: $(EX2)
	@echo ex2 successfully constructed

$(EX2): $(EX2_SRC) $(EX2_H)
	$(CC) $(CFLAGS) $(MCFLAGS) -o $(EX2) $(EX2_SRC)
	# $(CC) $(CFLAGS) -o $(EX2) $(EX2_SRC)

clean:
	$(RM) *.O *.a *~ $(EX2)

tar:
	tar -cvzf ex2.tar *.c *.h
