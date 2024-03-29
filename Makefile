CC=gcc
EXEC=quadtree
VAL_FILE=valgrind-result.out
SRC=src
CFLAGS=-Wall -lm -std=c99 -g -I $(SRC)/rgb/ -I $(SRC)/utils/ -I $(SRC)/tree/

all: clean build

build: clean $(EXEC)

$(EXEC): $(SRC)/main.o $(SRC)/utils/utils.o $(SRC)/tree/tree.o $(SRC)/rgb/rgb.o
	@$(CC) -o $@ $^ $(CFLAGS)

main.o: $(SRC)/main.c $(SRC)/utils/utils.c $(SRC)/tree/tree.c $(SRC)/rgb/rgb.c
	@$(CC) -c $^

run: clean build
	@./$(EXEC)

clean: 
	@rm -rf *.o $(SRC)/*.o $(EXEC) $(SRC)/*/*.o
	@rm -rf $(VAL_FILE)
	@rm -rf *.ppm
	@rm -rf *.out*
	
memcheck: build
	valgrind --leak-check=full --show-leak-kinds=all --log-file=$(VAL_FILE) --track-origins=yes --verbose ./$(EXEC) -d out.out output.ppm