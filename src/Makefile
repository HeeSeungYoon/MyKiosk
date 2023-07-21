.SUFFIXES: .c .o

CC =gcc
CFLAGS=

SRC_DIR=./src
OBJ_DIR=../obj

LDFLAGS=-lncursesw

OBJS_CLNT=init.o client.o client1.o menu.o
OBJS_SERV=server.o menu.o
OBJECTS_CLNT=$(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS_CLNT))
OBJECTS_SERV=$(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS_SERV))

SRCS_CLNT=$(OBJS_CLNT:.o=.c)
SRCS_SERV=$(OBJS_SERV:.o=.c)

DEPS=$(OBJECTS_CLNT:.o=.d) $(OBJECTS_SERV:.o=.d)

all : client1 server

$(OBJ_DIR)/%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@ -MD

client1 : $(OBJECTS_CLNT)
		$(CC) $(CFLAGS) $(OBJECTS_CLNT) -o client1 $(LDFLAGS)

server : $(OBJECTS_SERV)
		$(CC) $(CFLAGS) $(OBJECTS_SERV) -o server

.PHONY: clean all
clean:	
		rm -f $(OBJECTS_CLNT) $(OBJECTS_SERV) $(DEPS) client1 server

-include $(DEPS)