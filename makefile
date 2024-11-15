# vim: set noet ts=8 sw=8
#
# Faery Tale Adventure - Conversion to SDL2 (macOS initially)
# - 2024 Xark (https://XarkLabs.com) - MIT Licensed, see LICENSE
#
# Original Amiga Release: https://github.com/viridia/faery-tale-amiga
# This Fork:              https://github.com/XarkLabs/faery-tale-amiga (branch "macos")
# 

# Xark: Amiga CFLAGS = -pp -hi amiga39.pre -qf
# Xark: Amiga OBJS   = fmain.o fsubs.o narr.o fmain2.o iffsubs.o gdriver.o makebitmap.o hdrive.o
# Xark: Amiga POBJS  = fmain.p fmain2.p iffsubs.p

# Makefile "best practices" from https://tech.davis-hansson.com/p/make/ (but not forcing gmake)
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.ONESHELL:
.DELETE_ON_ERROR:
MAKEFLAGS += --no-builtin-rules

CFLAGS  = -g -Os -Wall -Wextra -I AmigaOS_NDK_3.1/Includes_Libs/include_h $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image

INCS = amiga39.h ftale.h fmain.h fmain2.h iffsubs.h
SRCS = $(wildcard *.c)
OBJS = $(addsuffix .o,$(basename $(SRCS)))

all: fta

fta: $(OBJS)
	-ld $(LDFLAGS) -o $@ $(OBJS) 2>ld.log
	@grep "referenced" ld.log | sort | uniq | cut -d "," -f 1 | tr -d "\042" | sed 's/ _/ /' >link_undef.log
	@echo === Number Remaining to Define:
	@cat link_undef.log | wc -l
	@echo === Undefined Symbols:
	@cat link_undef.log

$(OBJS): $(INCLUDE) $(MAKEFILE_LIST)

clean:
	rm -f $(OBJS) fta

.PHONY: all clean

