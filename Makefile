TARGET = main.out
HDRS_DIR = project/include
CC=gcc

# XXX: Don't forget backslash at the end of any line except the last one
SRCS = \
       project/src/utils.c\
       project/src/prime.c\
       project/src/main.c 

.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS) -lm

clean:
	rm -rf $(TARGET)
