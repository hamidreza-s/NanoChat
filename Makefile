CC = gcc

CFLAGS += -Wall
LDFLAGS+= -L/usr/local/lib -I/usr/local/include -lpthread -lnanomsg

OUT_EXE = nanochat
FILES =	src/nc.c \
	src/nc_param.c \
	src/nc_utils.c \
	src/nc_disco.c \
	src/nc_shell.c \
	src/nc_conf.c \
	src/nc_log.c

build: config $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) $(CFLAGS) $(LDFLAGS) 

clean:
	rm -f *.o

config:
	@mkdir -p ./var
	@rm -f ./var/nanochat.conf
	@echo "log_file=./var/nanochat.log" >> ./var/nanochat.conf
	@echo "foo=bar" >> ./var/nanochat.conf
