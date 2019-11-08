
LOCAL_PATH:=$(shell pwd)

LOCAL_SRC:=$(wildcard $(LOCAL_PATH)/source/*.s)


LOCAL_OBJ:=$(subst .s,.o,$(LOCAL_SRC))

LOCAL_OUT_PATH:=$(LOCAL_PATH)/output
LOCAL_TARGET:=$(LOCAL_OUT_PATH)/main.out

$(LOCAL_TARGET):$(LOCAL_OBJ)
	ld -o $@ $^

$(LOCAL_OBJ):$(LOCAL_SRC)
	nasm -g -f elf64 -o $@ $^

.PHONY: clean

clean:
	rm -rf $(LOCAL_TARGET) $(LOCAL_OBJ)

run:
	$(LOCAL_TARGET)

