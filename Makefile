# GNU make >= 3.81 required

PREFIX := /usr/local
CC := cc

CFLAGS := -O3 -Iinclude -std=c11 -DNDEBUG
# DEBUG
# CFLAGS := -Iinclude -std=c11

LD_FLAGS :=

.DEFAULT_GOAL:=all

SRC_FILES := $(wildcard src/**/*.c)
EXMAMPLE_FILES := $(wildcard example/**/*.c)
EXAMPLE_OUT_FILES := $(EXMAMPLE_FILES:%.c=%.out)
TEST_FILES := $(wildcard test/**/*.c)
OBJ_FILES := $(SRC_FILES:src/%.c=obj/%.o)

$(OBJ_FILES): obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

libswh.a: $(OBJ_FILES)
	$(AR) rcs $@ $^

lib: libswh.a

install: lib
	cp libswh.a $(PREFIX)/lib
	cp -r include/swh $(PREFIX)/include/

$(EXAMPLE_OUT_FILES): example/%.out: example/%.c libswh.a
	$(CC) $(CFLAGS) $^ -o $@

example: lib $(EXAMPLE_OUT_FILES)

test: lib

all: lib example test

.PHONY: clean
clean:
	-rm -rf obj
	-rm -rf $(EXMAMPLE_FILES:%.c=%.out)
	-rm -rf libswh.a

