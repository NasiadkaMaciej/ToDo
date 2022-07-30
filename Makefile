todo: *.c *.h
	cc *.c -o todo
clean:
	-rm todo
install:
	@install -v -m 755 todo /usr/bin/
uninstall :
	@rm /usr/bin/todo