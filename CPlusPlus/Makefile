
LOCAL_PATH:=$(shell pwd)
LOCAL_SRC:=$(wildcard $(LOCAL_PATH)/source/*.cpp)
LOCAL_OBJ:=$(subst .cpp,.o,$(LOCAL_SRC))
LOCAL_CFLAGS:=-I$(LOCAL_PATH)/include -DADDX -pthread
LOCAL_OUT_PATH:=$(LOCAL_PATH)/output
LOCAL_TARGET:=$(LOCAL_OUT_PATH)/main.out

CC:=g++

$(LOCAL_TARGET):$(LOCAL_SRC)
	$(CC) $(LOCAL_CFLAGS) $^ -o $@

.PHONY:clean run

clean:
	rm $(LOCAL_TARGET)

run:
	$(LOCAL_TARGET)
