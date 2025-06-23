So the tutorial i was following along ended in the last part and now i am free styling meaning i will be making a whole lot of mistakes 
first make a .img disk using qemu-img switch make file to first output the os image to this disk and use this diskimg as drive instead of the os-image.bin directly 
now we need to make a driver i will use PCI IDE controller for the drive

before we can make a PCI IDE disk driver we need to initialise the PCI BUS 

PCI Bus provides a purely software initialisation for any device on the PCI Bus via the Configuration Address Space 
All devices on the bus first provide 256 bytes of configuration registers for this
these registers are inside the pci device itself we read and write to this configuration space via the 
PCI CONFIG_ADDRESS(0xCF8) and PCI CONFIG_DATA (0xCFC)

Config Address layout (32 bit) :
bit 31: enable bit must be 1 to access read or write if 0 nothing happens
bit 30 - 24: must be 0 
bit 23-16: Bus number 
bit 15-11 : device number 
bit 10-8: function number
bit 7-2: register number
bit 1-0: alwasy 0 for 4 bit alignment

make a config space controller to do this

