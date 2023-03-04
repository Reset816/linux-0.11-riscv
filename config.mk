ifneq ($(wildcard $(foreach p,$(subst :, ,$(PATH)),$(p)/riscv64-linux-gnu-*)),)
	PREFIX := riscv64-linux-gnu
else
	PREFIX := riscv64-unknown-elf
endif

CC := $(PREFIX)-gcc
LD := $(PREFIX)-ld
AR := $(PREFIX)-ar
OBJCOPY := $(PREFIX)-objcopy
OBJDUMP := $(PREFIX)-objdump
READELF := $(PREFIX)-readelf
NM := $(PREFIX)-nm
AS := $(PREFIX)-as
GDB := riscv64-unknown-elf-gdb
TMUX := tmux
QEMU := qemu-system-riscv64
 
CFLAGS := -mcmodel=medany # -mcmodel=medany 适用于64位RISC-V的CPU（RV64I指令集），使一些C语言代码中的寻址操作可以被编译为auipc指令，用于相对寻址，可使程序的运行与程序被加载的位置无关
CFLAGS += -g3 # -g3 添加适用于gdb的调试信息
CFLAGS += -fno-builtin # -fno-builtin 不使用 GCC 内建函数
CFLAGS += -fno-stack-protector # -fno-stack-protector 不使用栈保护
CFLAGS += -fno-strict-aliasing # -fno-strict-aliasing 允许未定义的类型间强制转换
CFLAGS += -O
CFLAGS += -fstrength-reduce
CFLAGS += -fomit-frame-pointer
CFLAGS += -fno-defer-pop
