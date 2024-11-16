# vim: set noet ts=8 sw=8
#
# Faery Tale Adventure - Conversion to SDL2 (macOS initially)
# - 2024 Xark (https://XarkLabs.com) - MIT Licensed, see LICENSE
#
# Original Amiga Release: https://github.com/viridia/faery-tale-amiga
# This Fork:              https://github.com/XarkLabs/faery-tale-amiga (branch "macos")
# 

# Makefile "best practices" from https://tech.davis-hansson.com/p/make/ (but not all)
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.ONESHELL:
.DELETE_ON_ERROR:
MAKEFLAGS += --no-builtin-rules

CC=clang
LD=clang

CFLAGS  = -g -Os -Wall -Wextra -I AmigaOS_NDK_3.1/Includes_Libs/include_h $(shell sdl2-config --cflags)
LDFLAGS =  $(shell sdl2-config --libs) -lSDL2_image

INCS = $(wildcard *.h)
SRCS = $(wildcard *.c)
OBJS = $(addsuffix .o,$(basename $(SRCS)))

all: fta

fta: $(OBJS)
	-$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): $(INCLUDE) $(MAKEFILE_LIST)

clean:
	rm -f $(OBJS) fta

.PHONY: all clean
