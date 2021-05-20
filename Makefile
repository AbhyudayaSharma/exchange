exchange: exchange.c
	gcc -O2 -Wall -pedantic -std=c11 -Werror -o exchange $^

.PHONY: clean install

install: exchange
	cp exchange /usr/local/bin/

clean: 
	rm -f exchange
