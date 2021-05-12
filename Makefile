TARGET1 = main.out
TARGET2 = test_modules.out
HDRS_DIR = project/include

SRCS1 = project/src/main.c\
		project/src/utils.c\
		project/src/read_and_write.c\
		project/src/menu.c

SRCS2 = project/src/test_modules.c\
		project/src/utils.c\
		project/src/read_and_write.c\
		project/src/menu.c


.PHONY: all clean

all: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET1) $(CFLAGS) $(SRCS1)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET2) $(CFLAGS) $(SRCS2)
clean:
	rm -rf $(TARGET1)
	rm -rf $(TARGET2)
