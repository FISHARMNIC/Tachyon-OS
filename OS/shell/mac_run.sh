# run on host pc

limactl shell debian
# qemu-system-x86_64 -drive id=disk,file=/tmp/lima/bin/MyOS.iso,if=none -device ahci,id=ahci -device ide-hd,drive=disk,bus=ahci.0
# qemu-img create -f qcow2 /tmp/lima/bin/MyOS.iso 50M
qemu-system-x86_64 -machine pc -hda /tmp/lima/bin/MyOS.iso

# dd if=/dev/zero of=os.hdd bs=1024 count=30000
# dd if=/tmp/lima/bin/MyOS.iso of=os.hdd conv=notrunc seek=0
# qemu-system-i386 -hda os.hdd
# qemu-system-i386 -drive file=/tmp/lima/bin/MyOS.iso,index=0,if=ide,format=raw