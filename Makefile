PWD := $(shell pwd)
UCOS_II=~/rtos/kernel/
include .config

PROG := $(PWD)/$(shell basename `pwd`)

#
# Project files
#
INCLUDE = $(PWD)
common_objects := $(patsubst %.c,%.o,$(wildcard $(PWD)/*.c)) $(patsubst %.c,%.o,$(wildcard $(PWD)/arch/$(PLATFORM)/*.c))

export PWD PROG INCLUDE common_objects UCOS_II KDIR CPU

all:
	$(MAKE) -C $(KDIR)

debug:
	$(MAKE) -C $(KDIR) debug

clean:
	$(MAKE) -C $(KDIR) clean

flash:
	$(MAKE) -C $(KDIR) flash

