TARGET = scaperoom
MAIN = $(SRC_DIR)/myshell0.c
OBJS = $(OBJ_DIR)/investigate.o
OBJS += $(OBJ_DIR)/history.o
OBJS += $(OBJ_DIR)/myman.o
SRCFS = $(BIN_DIR)/investigate
SRCFS += $(BIN_DIR)/history
SRCFS += $(BIN_DIR)/myman
INC_DIR = ./inc
OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin
PROGS = $(patsubst %.c,%,$(OBJ_DIR))
CFLAGS = -Wall


$(TARGET) : $(MAIN) $(OBJS) $(SRCFS)
	gcc $(CFLAGS) $(MAIN) -o $(TARGET)

$(SRCFS) : $(BIN_DIR)/%: $(OBJ_DIR)/%.o
	mkdir -p $(BIN_DIR)
	gcc -O2 $(CFLAGS)  -o $@ $<
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	gcc -c -MD $(CFLAGS) $< -o $@


#-include $(OBJ_DIR)/*.d

.PHONY: clean
clean:
	rm -f "./gameTree/history.txt"
	rm -f scaperoom
	rm -r -f $(OBJ_DIR)
	rm -r -f $(BIN_DIR)