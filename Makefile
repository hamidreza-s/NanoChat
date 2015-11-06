CC = gcc

CFLAGS += -Wall
# LDFLAGS+= 

OUT_EXE = nanochat
FILES =	src/nc.c \
	src/nc_args.c \
	src/nc_util.c

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(CFLAGS) $(FILES) 

clean:
	rm -f *.o
