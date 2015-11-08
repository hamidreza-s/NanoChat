CC = gcc

CFLAGS += -Wall
LDFLAGS+= -L/usr/local/lib -lpthread -lnanomsg

OUT_EXE = nanochat
FILES =	src/nc.c \
	src/nc_param.c \
	src/nc_utils.c \
	src/nc_disco.c \
	src/nc_shell.c

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) $(CFLAGS) $(LDFLAGS) 

clean:
	rm -f *.o
