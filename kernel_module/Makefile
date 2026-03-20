obj-m += hello.o
KDIR := /lib/modules/$(shell uname -r)/build

# Force clang toolchain
CC=clang
LD=ld.lld
AR=llvm-ar
NM=llvm-nm
OBJCOPY=llvm-objcopy
OBJDUMP=llvm-objdump
STRIP=llvm-strip

# Disable ftrace/mcount requirements
EXTRA_CFLAGS += -fno-graphite-identity -fno-loop-flatten -fno-tree-loop-vectorize \
                -mno-omit-leaf-frame-pointer -DDISABLE_BRANCH_PROFILING \
                -DCC_USING_FENTRY -mfentry -mrecord-mcount

all:
	make -C $(KDIR) M=$(PWD) modules CC=$(CC) LD=$(LD) AR=$(AR) NM=$(NM) \
	OBJCOPY=$(OBJCOPY) OBJDUMP=$(OBJDUMP) STRIP=$(STRIP) EXTRA_CFLAGS="$(EXTRA_CFLAGS)"

clean:
	make -C $(KDIR) M=$(PWD) clean

