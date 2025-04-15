todo: *.c *.h
	gcc *.c -o todo -Wall -Wextra -pedantic -O2
clean:
	-rm todo
install:
	@install -v -m 755 todo /usr/bin/
uninstall :
	@rm /usr/bin/todo