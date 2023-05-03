# CXX		  := gcc
# CXX_FLAGS := -g -pthread -c -lrt

# BIN		:= bin
# SRC		:= src
# INCLUDE	:= include
# LIB		:= lib

# LIBRARIES	:=
# EXECUTABLE	:= main


# all: $(BIN)/$(EXECUTABLE)

# run: clean all
# 	clear
# 	./$(BIN)/$(EXECUTABLE)

# $(BIN)/$(EXECUTABLE): $(SRC)/*.c
# 	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES)

# clean:
# 	-rm $(BIN)/*



# CXX= gcc $(CCFLAGS)
# MAIN=	src/main.c
# FUNC=	src/func.c
# SPEND_TIME=	src/spend_time.h
# OBJS = $(MAIN) $(FUNC) $(SPEND_TIME)

# LIBS= -pthread

# CCFLAGS= -g -c -lrt

# all:		main func spend_time

# main:	$(MAIN)
# 		$(CXX) -o main $(MAIN) $(LIBS)

# func:	$(FUNC)
# 		$(CXX) -o func $(FUNC) $(LIBS)

# spend_time:	$(SPEND_TIME)
# 		$(CXX) -o spend_time $(SPEND_TIME) $(LIBS)

# clean:
# 		rm -f $(OBJS) $(OBJS:.o=.d)

# realclean:
# 		rm -f $(OBJS) $(OBJS:.o=.d) main func spend_time



# CC=gcc
# CFLAGS=-pthread -g -c -lrt
# SRC=src/main.c src/func.c 
# HDRS=func.h 
# OBJ=$(SRC:.c=.o)
# TARGET=program

# .PHONY: all clean

# all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CC) $(CFLAGS) -o $@ $^

# %.o: %.c $(HDRS)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# clean:
# 	rm -f $(OBJ) $(TARGET)



all: func
func: func.o main.o 
	gcc -o func src/func.o src/main.o
func.o: src/main.c
	gcc -o src/func.o -c src/func.c -pthread -g -c -lrt
main.o: src/main.c src/func.h
	gcc -o src/main.o -c src/main.c -pthread -g -c -lrt
clean:
	rm -rf *.o
mrproper: clean
	rm -rf func

