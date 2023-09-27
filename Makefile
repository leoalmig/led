led: led.o scr_buffer.o buf_line.o utils.o
	gcc -o led led.o scr_buffer.o buf_line.o utils.o -lncurses

led.o: led.c led.h scr_buffer.h
	gcc -c led.c

scr_buffer.o: scr_buffer.c scr_buffer.h buf_line.h
	gcc -c scr_buffer.c

buf_line.o: buf_line.c buf_line.h
	gcc -c buf_line.c

utils.o: utils.c utils.h
	gcc -c utils.c

.PHONY: clean
clean:
	rm -rf test.txt led
