CC:=C:\avr8-gnu-toolchain-win32_x86_64\bin\avr-gcc.exe
OBCP:=C:\avr8-gnu-toolchain-win32_x86_64\bin\avr-objcopy.exe
DIR:=C:\users\Brett\ATTINY85

all: demo.hex demo2.hex blink.hex idle.hex adcnr.hex pwrdn.hex t0norm.hex
adcnr.o: adcnr.c
	$(CC) -g -Os -mmcu=attiny85 -c $(DIR)\src\adcnr.c -o $(DIR)\output\adcnr.o
adcnr.elf: adcnr.o
	$(CC) -g -mmcu=attiny85 $(DIR)\output\adcnr.o -o $(DIR)\output\adcnr.elf
adcnr.hex: adcnr.elf
	$(OBCP) -j .text -j .data -O ihex $(DIR)\output\adcnr.elf $(DIR)\output\adcnr.hex
blink.o: blink.c
	$(CC) -g -Os -mmcu=attiny85 -c $(DIR)\src\blink.c -o $(DIR)\output\blink.o
blink.elf: blink.o
	$(CC) -g -mmcu=attiny85 $(DIR)\output\blink.o -o $(DIR)\output\blink.elf
blink.hex: blink.elf
	$(OBCP) -j .text -j .data -O ihex $(DIR)\output\blink.elf $(DIR)\output\blink.hex
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
idle.o: idle.c
	$(CC) -g -Os -mmcu=attiny85 -c $(DIR)\src\idle.c -o $(DIR)\output\idle.o
idle.elf: idle.o
	$(CC) -g -mmcu=attiny85 $(DIR)\output\idle.o -o $(DIR)\output\idle.elf
idle.hex: idle.elf
	$(OBCP) -j .text -j .data -O ihex $(DIR)\output\idle.elf $(DIR)\output\idle.hex
pwrdn.o: pwrdn.c
	$(CC) -g -Os -mmcu=attiny85 -c $(DIR)\src\pwrdn.c -o $(DIR)\output\pwrdn.o
pwrdn.elf: pwrdn.o
	$(CC) -g -mmcu=attiny85 $(DIR)\output\pwrdn.o -o $(DIR)\output\pwrdn.elf
pwrdn.hex: pwrdn.elf
	$(OBCP) -j .text -j .data -O ihex $(DIR)\output\pwrdn.elf $(DIR)\output\pwrdn.hex
t0norm.o: t0norm.c
	$(CC) -g -Os -mmcu=attiny85 -c $(DIR)\src\t0norm.c -o $(DIR)\output\t0norm.o
t0norm.elf: t0norm.o
	$(CC) -g -mmcu=attiny85 $(DIR)\output\t0norm.o -o $(DIR)\output\t0norm.elf
t0norm.hex: t0norm.elf
	$(OBCP) -j .text -j .data -O ihex $(DIR)\output\t0norm.elf $(DIR)\output\t0norm.hex

demo.c:
demo2.c:
blink.c:
idle.c:
adcnr.c:
pwrdn.c:
t0norm.c:
clean:
	del $(DIR)\output\*.*