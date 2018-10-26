
LOCAL_SRC:=$(wildcard *.c)
LOCAL_OBJ:=$(subst %.c,%.o,$(LOCAL_SRC))
LOCAL_TARGET:=main.out

CC:=gcc

$(LOCAL_TARGET):$(LOCAL_SRC)
	$(CC) $^ -o $@

.PHONY:clean

clean:
	rm $(LOCAL_TARGET)
