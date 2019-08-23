#SRC := $(wildcard *.c)

#BIN = $(SRC:%.c=%.o)

cc = gcc

CPPFLAGS += -I ../include

LDFIAGS += -L ../lib -llog

LDFIAGS += -Wl,-rpath=../lib

main:main.c
	@$(cc) $^ -o $@ $(CPPFLAGS) $(LDFIAGS) 
clean:
	-@$(RM) $(BIN)
