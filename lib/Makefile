SRC := $(wildcard *.c)

BIN = $(SRC:%.c=%.o)

cc = gcc

CPPFLAGS += -I ../include

liblog.so:$(BIN)
	@$(cc) -shared -fPIC $^ -o $@ 
$(BIN):%.o:%.c
	@$(cc) $^ -o $@ -c -fPIC $(CPPFLAGS)

clean:
	-@$(RM) $(BIN)
distclean:clean
	-@$(RM) liblog.so
