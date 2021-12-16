CC = clang
CFLAGS = -std=gnu11 -O2 -Wall -Werror -Wconversion -pedantic -Wno-unused-result
MCFLAGS = -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
L5_SRC = *.c
L5_H = *.h
L5 = l5

TAR_NAME = l5.tar
JOJ_L5 = https://joj.sjtu.edu.cn/d/ve482_fall_2021/homework/6173161ec5c4050006b03f24/617523bac5c4050006b052b7
JOJ_L5_MC = https://joj.sjtu.edu.cn/d/ve482_fall_2021/homework/6173161ec5c4050006b03f24/61752dffc5c4050006b053aa

all: clean $(L5)
	@echo l5 successfully constructed

tar:
	rm -f $(TAR_NAME)
	tar -cvzf $(TAR_NAME) lab5_dlist.c

joj: tar
	joj-submit $(JOJ_L5) $(TAR_NAME) make

mc: tar
	joj-submit $(JOJ_L5_MC) $(TAR_NAME) make

$(L5): $(l5_SRC) $(L5_H)
	$(CC) $(CFLAGS) $(MCFLAGS) -o $(L5) $(L5_SRC)

clean:
	rm -f l5 *.o