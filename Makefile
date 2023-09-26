led: led.c
	gcc led.c -o led -lncurses

.PHONY: clean
clean:
	rm -rf led
