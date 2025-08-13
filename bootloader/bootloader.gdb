target remote localhost:3333
file build/bootloader/bootloader.elf
monitor reset halt
b main
continue