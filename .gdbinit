file vmlinux
target remote localhost:1234
layout split
b *0x80200000
b main
focus cmd
