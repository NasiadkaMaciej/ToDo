todo: *.c *.h
	cc *.c -o todo

clean:
	-rm todo

install:
	@install -v -m 755 todo $(DESTDIR)/usr/bin/

uninstall :
	@rm /usr/bin/todo