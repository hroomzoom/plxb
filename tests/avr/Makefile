MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

SRC = $(wildcard ../../*.c)
TARGET = plxb

all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f *.elf *.hex