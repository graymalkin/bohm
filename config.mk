VERSION = 1.2

CFLAGS = -ansi -g -D_POSIX_C_SOURCE=200809L -DVERSION='"$(VERSION)"' -Iinclude -Wall
LDLIBS = -g -lreadline
YFLAGS = -d
