# GNU make >= 3.81 required

PREFIX=/usr/local
CC:=cc
CFLAGS:=-O3 -Iinclude
LD_FLAGS:=

.DEFAULT_GOAL:=all

SRC_FILES := $(wildcard src/**/*.c)
EXMAMPLE_FILES := $(wildcard example/**/*.c)
TEST_FILES := $(wildcard test/**/*.c)
OBJ_FILES := $(SRC_FILES:src/%.c=obj/%.o)

$(OBJ_FILES): obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

libswh.a: $(OBJ_FILES)
	$(AR) rcs $@ $<

lib: libswh.a

install: lib
	cp libswh.a $(PREFIX)/lib
	cp -r include/swh $(PREFIX)/include/

example: lib $(EXMAMPLE_FILES:%.c=%.out)

test: lib

all: lib example test

.PHONY: clean
clean:
	-rm -rf obj
	-rm -rf libswh.a

