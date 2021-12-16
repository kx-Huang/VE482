.DEFAULT_GOAL := all

CC = clang
CFLAGS = -O2 -Wall -Wextra -Werror -pedantic -Wno-unused-result -Wconversion -Wvla
MAIN_SRC = core/list.c core/main.c core/plugin_manager.c core/plugin_utility.c core/interface.c
TXT_SRC = plugins/txt.c plugins/sort.c plugins/io.c core/plugin_manager.c core/list.c
CSV_SRC = plugins/csv.c plugins/sort.c plugins/io.c core/plugin_manager.c core/list.c
MAIN = l6
MAINMC = l6_memory_check
MAINMC_FLAGS = -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=integer
PLUGIN_TXT = ./plugins/txt.so
PLUGIN_CSV = ./plugins/csv.so

TAR_NAME = l6.zip
JOJ_L6 = https://joj.sjtu.edu.cn/d/ve482_fall_2021/homework/61768020c5c4050006b063e9/61767ff3c5c4050006b063e5
JOJ_L6_MC = https://joj.sjtu.edu.cn/d/ve482_fall_2021/homework/61768020c5c4050006b063e9/617680f5c5c4050006b063f6

.PHONY: clean

all: $(MAIN) $(MAINMC) $(PLUGIN_TXT) $(PLUGIN_CSV)
	@echo "[Success] ex3 has constructed!"

$(MAIN): $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN_SRC) -ldl

$(MAINMC): $(MAIN_SRC)
	$(CC) $(CFLAGS) $(MAINMC_FLAGS) -o $(MAINMC) $(MAIN_SRC) -ldl

$(PLUGIN_TXT): $(TXT_SRC)
	$(CC) $(CFLAGS)	-shared -fPIC -o $(PLUGIN_TXT) $(TXT_SRC)

$(PLUGIN_CSV): $(CSV_SRC)
	$(CC) $(CFLAGS) -shared -fPIC -o $(PLUGIN_CSV) $(CSV_SRC)

tar:
	rm -f $(TAR_NAME)
	zip -r l6.zip core plugins makefile

joj: tar
	joj-submit $(JOJ_L6) $(TAR_NAME) make

mc: tar
	joj-submit $(JOJ_L6_MC) $(TAR_NAME) make

clean:
	rm *.o *.a $(MAIN) $(MAINMC) $(PLUGIN_TXT) $(PLUGIN_CSV) *.tar
