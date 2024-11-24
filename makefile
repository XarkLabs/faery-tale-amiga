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

CC=gcc
LD=gcc

CFLAGS  = -g -O0 -Wall -Wextra -Werror $(shell sdl2-config --cflags)
LDFLAGS =  $(shell sdl2-config --libs) -lSDL2_image

INCS = $(wildcard *.h)
SRCS = $(wildcard *.c)
OBJS = $(addsuffix .o,$(basename $(SRCS)))

all: fta

fta: $(OBJS)
	-$(LD) $(OBJS) $(LDFLAGS) -o $@

debug: all
	-killall -9 fta
	lldb -b -o run ./fta

clean:
	rm -f $(OBJS) fta

.PHONY: all debug clean
