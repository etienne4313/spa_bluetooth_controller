PWD := $(shell pwd)
PROG := $(shell basename `pwd`)
include Config.mk

#
# Project files
#
common_objects := $(patsubst %.c,%.o,$(wildcard $(PWD)/*.c)) $(patsubst %.c,%.o,$(wildcard $(PWD)/arch/$(ARCH)/*.c))
INCLUDE = $(PWD)

all_objects := $(os_objects) $(common_objects)

all: $(all_objects)
	$(CC) -o $(PROG) $(all_objects) $(LDFLAGS)
	$(OBJCOPY) -O ihex -R .eeprom $(PROG) $(PROG).hex

debug:
	$(OBJDUMP) -D $(PROG) >diss
	$(OBJDUMP) -x $(PROG) |grep -A6 "Idx Name"
	$(OBJDUMP) -x $(PROG) |grep " .bss" |grep -v "*" |sort -nk 5  |tail -20
	$(OBJDUMP) -x $(PROG) |grep " .data" |grep -v "*" |sort -nk 5  |tail -20

clean:
	rm -f $(all_objects) $(PROG) $(PROG).hex diss

flash:
	$(FLASH)

