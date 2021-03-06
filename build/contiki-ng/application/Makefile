#####################################################
# 				Configurable Parameters             #
#####################################################
# Accepted values: 0 1 2 3 4
LOGGER_VERBOSITY ?= 4
# Accepted values: NULL, TINYDTLS, CRYPTOAUTHLIB, TINYCRYPT
SEC_LIB ?= TINYCRYPT
#####################################################
#   		   End Configurable Parameters          #
#####################################################
# This Makefiles assumes that you already have a saved target
include ../Makefile.target
include ../target/$(TARGET)/$(BOARD)/Makefile.conf
include ../target/$(TARGET)/$(BOARD)/Makefile.board
include ../target/$(TARGET)/$(BOARD)/Makefile.export

CONTIKI_PROJECT=runner
all: ota

# Contiki-NG Size optimizations
SMALL = 1
WERROR=0

# Add libpull sources
ROOTDIR = ../../..
BOARDDIR = ../target/$(TARGET)/$(BOARD)

PROJECT_SOURCEFILES += update_process.c

LIBPULL_APPLICATION=1
MODULES += os/net/app-layer/coap

CFLAGS += -DWITH_UPDATE_AGENT=1

include ../makefiles/Makefile.libpull

# Security Configurations
ext= $(ROOTDIR)/ext
ifeq ($(SEC_LIB),TINYDTLS)
	include ../makefiles/Makefile.tinydtls
else ifeq ($(SEC_LIB),CRYPTOAUTHLIB)
	include ../makefiles/Makefile.cryptoauthlib
else ifeq ($(SEC_LIB),TINYCRYPT)
	include ../makefiles/Makefile.tinycrypt
endif

CFLAGS += -DSEC_LIB=$(SEC_LIB)
CFLAGS += -DOTA=1

OTA_OFFSET="$(INITIAL_MEMORY_OFFSET)+($(BOOTLOADER_START_PAGE)*$(PAGE_SIZE))"
OTA_LENGTH="($(BOOTLOADER_END_PAGE)-$(BOOTLOADER_START_PAGE))*$(PAGE_SIZE)"
CFLAGS += -DOTA_OFFSET=$(OTA_OFFSET) -DOTA_LENGTH=$(OTA_LENGTH)

ota:
	$(Q)$(LD) -P -E $(LINKER_DEFINES) $(BOARDDIR)/linker_script.c -o linker_script.ld
	$(MAKE) $(CONTIKI_PROJECT) SOURCE_LDSCRIPT=$(BOARDDIR)/linker_script.c

# Include Contiki Makefile
CONTIKI = ../ext/contiki-ng
include $(CONTIKI)/Makefile.include
