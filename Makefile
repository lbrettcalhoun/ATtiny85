CC:=C:\avr8-gnu-toolchain-win32_x86_64\bin\avr-gcc.exe
OBCP:=C:\avr8-gnu-toolchain-win32_x86_64\bin\avr-objcopy.exe
DIR:=C:\users\Brett\ATTINY85

all: demo.hex demo2.hex
demo.o: demo.c
	$(CC) -g -Os -mmcu=attiny85 -c $(DIR)\src\demo.c -o $(DIR)\output\demo.o
demo2.o: demo2.c
	$(CC) -g -Os -mmcu=attiny85 -c $(DIR)\src\demo2.c -o $(DIR)\output\demo2.o
demo.elf: demo.o
	$(CC) -g -mmcu=attiny85 $(DIR)\output\demo.o -o $(DIR)\output\demo.elf
demo2.elf: demo2.o
	$(CC) -g -mmcu=attiny85 $(DIR)\output\demo2.o -o $(DIR)\output\demo2.elf
demo.hex: demo.elf
	$(OBCP) -j .text -j .data -O ihex $(DIR)\output\demo.elf $(DIR)\output\demo.hex
demo2.hex: demo2.elf
	$(OBCP) -j .text -j .data -O ihex $(DIR)\output\demo2.elf $(DIR)\output\demo2.hex
demo.c:
demo2.c:

clean:
	del $(DIR)\output\*.*