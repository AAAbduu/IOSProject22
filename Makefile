TARGET = scaperoom
OBJS = $(OBJ_DIR)/myshell0.o
OBJS += $(OBJ_DIR)/investigate.o
OBJS += $(OBJ_DIR)/go.o
INC_DIR = ./inc
OBJ_DIR = ./obj
SRC_DIR = ./src
CFLAGS = -Wall -DFUNCTION -I$(INC_DIR)


$(TARGET) : $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(TARGET)


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

.PHONY: clean
clean:
	rm -r $(OBJ_DIR)
	rm scaperoom