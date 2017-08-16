DESTDIR=
PREFIX=/usr

NAME=acternabnc
CFLAGS=-O3

all: $(NAME)

$(NAME): $(NAME).c
	gcc $(CFLAGS) -o $(NAME) $(NAME).c

clean: $(NAME).c
	rm -f $(NAME)

install: $(NAME)
	install -D -m 755 $(NAME) $(DESTDIR)$(PREFIX)/sbin/$(NAME)

