LOCAL_PATH:=$(shell pwd)

LOCAL_SRC:=$(wildcard $(LOCAL_PATH)/source/*.y)
LOCAL_SRC+=$(wildcard $(LOCAL_PATH)/source/*.l)

LOCAL_OUT_PATH:=$(LOCAL_PATH)/output

LOCAL_OBJ:=$(LOCAL_OUT_PATH)/calculator.tab.c
LOCAL_OBJ+=$(LOCAL_OUT_PATH)/lex.yy.c

LOCAL_CFLAGS:=-I$(LOCAL_PATH)/include -I$(LOCAL_OUT_PATH)
LOCAL_TARGET:=$(LOCAL_OUT_PATH)/main.out

LEX = flex
YYAC = bison
CC = gcc

$(LOCAL_TARGET): $(LOCAL_OBJ)
	$(CC) $(LOCAL_CFLAGS) -o $@ $^ -lfl

$(LOCAL_OUT_PATH)/lex.yy.c: $(LOCAL_PATH)/source/calculator.l
	${LEX} -o $@ $^

$(LOCAL_OUT_PATH)/calculator.tab.h: $(LOCAL_PATH)/source/calculator.y

$(LOCAL_OUT_PATH)/calculator.tab.c: $(LOCAL_PATH)/source/calculator.y
	${YYAC} -d $^ -o $@


.PHONY:clean run

clean:
	rm $(LOCAL_TARGET) $(LOCAL_OBJ) $(LOCAL_OUT_PATH)/*.h

run:
	$(LOCAL_TARGET)
