# GNU make >= 3.81 required

PREFIX=/usr/local
CC:=cc
C_FLAGS:=-O3 -Iinclude
LD_FLAGS:=

SRC_FILES := $(wildcard src/**/*.c)
OBJ_FILES := $(SRC_FILES:src/%.c=obj/%.o)

$(OBJ_FILES): obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $(C_FLAGS) $< -o $@

libswh.a: $(OBJ_FILES)
	$(AR) rcs $@ $<

lib: libswh.a

install: lib
	cp libswh.a $(PREFIX)/lib
	cp -r include/swh $(PREFIX)/include/

example: lib

test: lib

all: lib example test

.PHONY: clean
clean:
	-rm -rf obj
	-rm -rf libswh.a

