
CPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = obj/Loader.o \
          obj/GDT.o \
          obj/Module.o \
          obj/Hardware/Screen.o \
          obj/File/File.o \
          obj/Hardware/IO.o \
          obj/Interrupts.o \
          obj/Task.o \
          obj/Time.o \
          obj/IDT.o \
          obj/Hardware/Keyboard.o \
          obj/Hardware/Mouse.o \
          obj/Computer.o \
          obj/Shell/Shell.o \
          obj/Kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CPPPARAMS) -o $@ -c $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

Kernel.bin: Linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: Kernel.bin
	sudo cp $< /boot/Kernel.bin

Aurora.iso: Kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0'                >  iso/boot/grub/grub.cfg
	echo 'set default=0'                >> iso/boot/grub/grub.cfg
	echo ''                             >> iso/boot/grub/grub.cfg
	echo 'menuentry "Aurora.OS" {'      >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/Kernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot'                       >> iso/boot/grub/grub.cfg
	echo '}'                            >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

clean:
	rm -rf obj
	rm Kernel.bin
	rm Aurora.iso











