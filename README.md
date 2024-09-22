Simple experiments with ATtiny85 using C (MS Visual Studio Code) and avr-libc library.

make all
make target.hex

avrdude -p attiny85 -C "C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf" -b 19200 -c stk500v1 -P com4  -U flash:w:.\output\target.hex -v
