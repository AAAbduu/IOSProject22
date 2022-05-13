TARGET = scaperoom
MAIN = $(SRC_DIR)/myshell0.c
OBJS = $(OBJ_DIR)/investigate.o
OBJS += $(OBJ_DIR)/history.o
OBJS += $(OBJ_DIR)/myman.o
OBJS += $(OBJ_DIR)/speak.o
OBJS += $(OBJ_DIR)/inventory.o
OBJS += $(OBJ_DIR)/take.o
SRCFS = $(BIN_DIR)/investigate
SRCFS += $(BIN_DIR)/history
SRCFS += $(BIN_DIR)/myman
SRCFS += $(BIN_DIR)/speak
SRCFS += $(BIN_DIR)/inventory
SRCFS += $(BIN_DIR)/take
OBJ_DIR = ./obj
SRC_DIR = ./src
BIN_DIR = ./bin
INVENTORY_DIR = ./gameTree/inventory
PROGS = $(patsubst %.c,%,$(OBJ_DIR))
CFLAGS = -Wall


$(TARGET) : $(MAIN) $(OBJS) $(SRCFS)
	gcc $(CFLAGS) $(MAIN) -o $(TARGET)

$(SRCFS) : $(BIN_DIR)/%: $(OBJ_DIR)/%.o
	mkdir -p $(BIN_DIR)
	gcc -O2 $(CFLAGS)  -o $@ $<
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	cp -a "./assets/rawScenario/gameTree" "./"
	mkdir -p $(INVENTORY_DIR)
	gcc -c -MD $(CFLAGS) $< -o $@


#-include $(OBJ_DIR)/*.d

.PHONY: clean
clean:
	rm -f "./gameTree/history.txt"
	rm -d -r -f "./gameTree/inventory"
	rm -f scaperoom
	chmod 0755 "./gameTree/Home/MainSquare/Castle/Park" 
	chmod 0755 "./gameTree/Home/MainSquare/Castle/MainHall" 
	chmod 0755 "./gameTree/Home/MainSquare/Castle" 
	chmod -f 0755 "./gameTree/Home/MainSquare/Pub"
	rm -d -r "./gameTree"
	rm -r -f $(OBJ_DIR)
	rm -r -f $(BIN_DIR)