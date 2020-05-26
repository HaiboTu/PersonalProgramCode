
ifdef M
	LOCAL_PATH = $(M)
else
	LOCAL_PATH = $(shell pwd)
endif

LOCAL_MODULE = mod_delete# module name

LOCAL_SRC = $(filter-out *.mod.c, $(wildcard $(LOCAL_PATH)/*.c))

LOCAL_OBJ = $(patsubst %.c, %.o, $(notdir $(LOCAL_SRC)))

KVERSION = $(shell uname -r)

KBUILD_PATH := /lib/modules/$(KVERSION)/build
$(info $(KBUILD_PATH))

KBUILD = $(shell readlink -f $(KBUILD_PATH))

#$(LOCAL_MODULE)-m := avic_test.o 

#obj-y := $(patsubst %, %.o, $(LOCAL_MODULE))
obj-m := mod_delete.o

LOCAL_INTERMEDIATE_COMPILE := $(LOCAL_OBJ)
LOCAL_INTERMEDIATE_COMPILE += $(LOCAL_OBJ) $(obj-m)
LOCAL_INTERMEDIATE_COMPILE += $(patsubst %, %.mod.c, $(LOCAL_MODULE))
LOCAL_INTERMEDIATE_COMPILE += $(patsubst %, %.mod.o, $(LOCAL_MODULE))
LOCAL_INTERMEDIATE_COMPILE += modules.order Module.symvers

all:
	make -C $(KBUILD) M=$(LOCAL_PATH) modules

.PHONY: clean

clean:
	-rm -f $(LOCAL_INTERMEDIATE_COMPILE)

