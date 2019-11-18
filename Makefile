CC = gcc
SRC := $(PWD)/src
SOURCES := \
	$(SRC)/main.c \
	$(SRC)/data_load.c \
	$(SRC)/knn.c \
	$(SRC)/matrix.c
INCLUDE_DIR := $(PWD)/include
LIBS := -lm
CFLAGS := -O2 -ftree-vectorize -msse2 -ftree-vectorizer-verbose=7
DEBUG_FOLDER := $(PWD)/build/debug
RELEASE_FOLDER := $(PWD)/build/release
EXE_NAME := knn
DEBUG_OUTPUT := $(DEBUG_FOLDER)/$(EXE_NAME)
RELEASE_OUTPUT := $(RELEASE_FOLDER)/$(EXE_NAME)

all: debug

release:
	mkdir -p build/release
	$(CC) $(CFLAGS) $(SOURCES) -o  $(RELEASE_OUTPUT) -I$(INCLUDE_DIR) $(LIBS)

debug:
	mkdir -p build/debug
	$(CC) $(CFLAGS) -g $(SOURCES) -o $(DEBUG_OUTPUT) -I$(INCLUDE_DIR) $(LIBS)


clean:
	rm -r build
