SRCS = main.c
LIBSRCS = open.c close.c put.c get.c skiplist.c
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LOBJS_PIC = $(LIBSRCS:.c=_pic.o)
LARS = libkvs.a
LADYN = libkvs.so


all: static dynamic

static: $(TARG)

$(TARG) : $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static

$(LARS) : $(LOBJS)
	ar rs $(LARS) $(LOBJS)

dynamic: $(TARG_DYNAMIC)

$(TARG_DYNAMIC) : $(OBJS) $(LADYN)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) -L. -lkvs

$(LADYN): $(LOBJS_PIC)
	$(CC) -shared -o $(LADYN) $(LOBJS_PIC)

static_main.o: static_main.c
	$(CC) $(OPTS) -c static_main.c -o static_main.o

dynamic_main.o: dynamic_main.c
	$(CC) $(OPTS) -c dynamic_main.c -o dynamic_main.o

%_pic.o: %.c
	$(CC) $(OPTS) -fPIC -c $< -o $@

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LOBJS) $(LOBJS_PIC) $(LARS) $(LADYN) $(TARG) $(TARG_DYNAMIC)


