### File Name (Source C File Name without Extention)
file_name = ADC_USART

##################################################################################################

### Paths
src_path = ./src/$(file_name).c
elf_path = ./bin/$(file_name).elf
hex_path = ./bin/$(file_name).hex

##################################################################################################

### Compiler and Commands
cc = avr-gcc
cc_obj = avr-objcopy
cc_dude = avrdude

##################################################################################################

### AVR GCC Flags

# AVR Microcontroller
avr_chip = atmega328p

cc_flags = -mmcu=$(avr_chip) -Wall -Os -o $(elf_path) $(src_path)

##################################################################################################

### AVR ObjCopy Flags
format = ihex
cc_obj_flags = -j .text -j .data -j .eeprom -O $(format) $(elf_path) $(hex_path)

##################################################################################################

### AVR dude Flags

# AVR Microcontroller Part
dude_part = m328p
# AVR Programmer
dude_prog = arduino
# Port Name
port = /dev/ttyUSB0
# Baud Rate
dude_baud = 57600
#dude_baud = 115200

cc_dude_flags = -p $(dude_part) -c $(dude_prog) -D -b $(dude_baud) -P $(port) -U flash:w:$(hex_path):i

##################################################################################################

all: upload convert_to_IHEX compile checkDirectories

upload: $(hex_path)
	sudo $(cc_dude) $(cc_dude_flags)

$(hex_path): convert_to_IHEX

convert_to_IHEX: $(elf_path)
	$(cc_obj) $(cc_obj_flags)

$(elf_path): compile

compile: checkDirectories $(src_path)
	$(cc) $(cc_flags)

checkDirectories: ./src ./bin

./bin:
	mkdir bin

clean:
	rm -rf ./bin $(hex_path)