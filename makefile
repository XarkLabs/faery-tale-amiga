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

#-Wall  -Wno-char-subscripts -Wno-pointer-sign -Wno-missing-braces
CFLAGS  = -g -Os -Wno-pointer-sign -I AmigaOS_NDK_3.1/Includes_Libs/include_h $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image

SRCS = fmain.c fmain2.c hdrive.c iffsubs.c
OBJS = fmain.o fmain2.o hdrive.o iffsubs.o
INCS = amiga39.h ftale.h fmain.p fmain2.p iffsubs.p

all: fta

fta: $(OBJS)
	ld $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): $(INCLUDE) Makefile

clean:
	rm -f $(OBJS) fta

.PHONY: all clean

