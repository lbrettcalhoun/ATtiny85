all: demo.o demo2.o
demo.o: demo.c
	avr-gcc -g -Os -mmcu=attiny85 -c C:\users\brett\ATTINY85\src\demo.c -o C:\users\brett\ATTINY85\output\demo.o
demo2.o: demo2.c
	avr-gcc -g -Os -mmcu=attiny85 -c C:\users\brett\ATTINY85\src\demo2.c -o C:\users\brett\ATTINY85\output\demo2.o
demo.c:
demo2.c:
clean:
	del C:\Users\Brett\ATtiny85\output\*.*