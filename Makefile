# Simple makefile to compile and program an AVR chip, in this case AT90CAN64
# base on the makefile found at https://www.pololu.com/docs/0J61/6.3 adjusted for my personal needs
# Author: Henrique

PORT=usb
MCU=at90can64
F_CPU=16000000UL
CFLAGS=-g -Wall -mcall-prologues -mmcu=$(MCU) -Os -fno-exceptions -DF_CPU=$(F_CPU)
LDFLAGS=-Wl,-gc-sections -Wl,-relax
CC=avr-gcc
VPATH = /usr/lib/avr/include ../include/ 

LINK_TARGET=test_usart

OBJECT_FILES= \
$(LINK_TARGET).o \
usart.o

REBUILDABLES= \
$(LINK_TARGET).hex \
$(LINK_TARGET).elf \
$(OBJECT_FILES)

.PHONY : all flash readeeprom readflash clean

all : $(LINK_TARGET).hex
	@rm -f *.dep
	@echo All done.

clean :
	rm -f $(REBUILDABLES) *.bin *.dep *.lst
	@echo Done cleaning.

$(LINK_TARGET).lst : $(LINK_TARGET).elf
	avr-objdump -h -S $(LINK_TARGET).elf > $(LINK_TARGET).lst
	@echo dumping of lst done.

flash : $(LINK_TARGET).hex
	avrdude -p $(MCU) -c atmelice_isp -U flash:w:$(LINK_TARGET).hex
	@rm -f *.elf *.dep *.o
	@echo Done flashing.

readeeprom :
	avrdude -p $(MCU) -c atmelice_isp -P usb -U eeprom:r:eepromdump.hex:i

readflash :
	avrdude -p $(MCU) -c atmelice_isp -P usb -U flash:r:flashdump.hex:i

$(LINK_TARGET).hex : $(LINK_TARGET).elf
	avr-objcopy -R .eeprom -O ihex $< $@
	@echo $@
	@echo $<

$(LINK_TARGET).elf : $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo $@
	@echo $^

$(LINK_TARGET).o : $(LINK_TARGET).cpp
	$(CC) $(CFLAGS) -o $@ -c $<
	@echo $@
	@echo $<

usart.o : usart.c
	$(CC) $(CFLAGS) -o $@ -c $<
	@echo $@
	@echo $<

#%.dep : %.cpp
#	avr-gcc -M $(CFLAGS) $< > $@
#include $(OBJECT_FILES:.o=.dep)