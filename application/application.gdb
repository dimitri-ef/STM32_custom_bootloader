target remote localhost:3333
file build/bootloader/bootloader.elf
monitor reset halt

add-symbol-file build/application/application.elf 0x08004000
break main
continue