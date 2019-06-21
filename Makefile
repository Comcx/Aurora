
CPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = Loader.o \
          GDT.o \
          Port.o \
          Interrupts.o \
          IDT.o \
          Keyboard.o \
          Kernel.o

%.o: %.cpp
	g++ $(CPPPARAMS) -o $@ -c $<

%.o: %.s
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
	echo 'set timeout=0' >  iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "Aurora.OS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/Kernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

clean:
	rm *.o
	rm *.bin
	rm Aurora.iso











