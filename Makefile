#
# if you want the ram-disk device, define this to be the
# size in blocks.
#
RAMDISK = #-DRAMDISK=512

include config.mk

CFLAGS  += $(RAMDISK)
CPP		 += -Iinclude

KERN_BIN := Image

QFLAGS := 	-machine virt \
			-serial mon:stdio \
			-bios ./boot/fw_jump.bin \
			-nographic \
			-device loader,file=$(KERN_BIN),addr=0x80200000

#
# ROOT_DEV specifies the default root-device when making the image.
# This can be either FLOPPY, /dev/xxxx or empty, in which case the
# default of /dev/hd6 is used by 'build'.
#
ROOT_DEV=

ARCHIVES=kernel/kernel.o mm/mm.o fs/fs.o
DRIVERS =kernel/blk_drv/blk_drv.a kernel/chr_drv/chr_drv.a
MATH	=kernel/math/math.a
LIBS	=lib/lib.a

.c.s:
	$(CC) $(CFLAGS) \
	-nostdinc -Iinclude -S -o $*.s $<
.s.o:
	$(AS) -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) \
	-nostdinc -Iinclude -c -o $*.o $<

all:	vmlinux

tools/build: tools/build.c
	$(CC) $(CFLAGS) \
	-o tools/build tools/build.c

boot/head.o: boot/head.s

vmlinux:	boot/head.o init/main.o \
		$(ARCHIVES) $(DRIVERS) $(MATH) $(LIBS)
	$(LD) -T linker.ld boot/head.o init/main.o \
	$(ARCHIVES) \
	$(DRIVERS) \
	$(MATH) \
	$(LIBS) \
	-Map=System.map -o vmlinux
	$(OBJCOPY) vmlinux --strip-all -O binary $(KERN_BIN)

kernel/math/math.a:
	(cd kernel/math; make)

kernel/blk_drv/blk_drv.a:
	(cd kernel/blk_drv; make)

kernel/chr_drv/chr_drv.a:
	(cd kernel/chr_drv; make)

kernel/kernel.o:
	(cd kernel; make)

mm/mm.o:
	(cd mm; make)

fs/fs.o:
	(cd fs; make)

lib/lib.a:
	(cd lib; make)

clean:
	rm -f $(KERN_BIN) System.map tmp_make core vmlinux
	rm -f init/*.o tools/system tools/build boot/*.o
	(cd mm;make clean)
	(cd fs;make clean)
	(cd kernel;make clean)
	(cd lib;make clean)

backup: clean
	(cd .. ; tar cf - linux | compress - > backup.Z)
	sync

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in init/*.c;do echo -n "init/";$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	(cd fs; make dep)
	(cd kernel; make dep)
	(cd mm; make dep)

### Dependencies:
init/main.o : init/main.c include/unistd.h include/sys/stat.h \
  include/sys/types.h include/sys/times.h include/sys/utsname.h \
  include/utime.h include/time.h include/linux/tty.h include/termios.h \
  include/linux/sched.h include/linux/head.h include/linux/fs.h \
  include/linux/mm.h include/signal.h include/asm/system.h include/asm/io.h \
  include/stddef.h include/stdarg.h include/fcntl.h include/kdebug.h

run: vmlinux
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS}

debug: vmlinux
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	$(TMUX) new -s debug -d "${QEMU} ${QFLAGS} -s -S" && $(TMUX) split-window -h "${GDB} -q"
	$(TMUX) attach-session -t debug
