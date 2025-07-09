#include "pci.h"
#include "io.h"
uint32_t pciReadWord(uint8_t bus ,uint8_t devicenum, uint8_t func, uint8_t offset){
    uint32_t addr;
    uint32_t lbus = (uint32_t)bus; //8 bits for bus
    uint32_t ldev = (uint32_t)devicenum;// 5 bits for device number 
    uint32_t lfunc = (uint32_t)func;//3 bits function number
    uint16_t ret = 0;
    /*
    Config Address layout (32 bit) :
    bit 31: enable bit must be 1 to access read or write if 0 nothing happens
    bit 30 - 24: must be 0 
    bit 23-16: Bus number 
    bit 15-11 : device number 
    bit 10-8: function number
    bit 7-2: register number
    bit 1-0: alwasy 0 for 4 bit alignment

    this code is expanded form of the below line
    address = lbus<<16 so that its on byte 16 to 23
    address | (ldev<<11)
    address | (func<<8)
    address | (80000000) just need to set the first bit we can also do |(1<<32)
    address | (offset&252)register has to have the last 2 bits 0 we can also do (offset&0xfc) 
    */
    addr = (uint32_t)((lbus << 16) | (ldev << 11) | (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
    
    port_byte_out(0xCF8,addr);
    ret = (uint32_t)port_byte_in(0xCFC);
    //so we may wanto to read either the first or second 16 bits the offset depending on the register offset so if offset is 1 we read the 16 msb but if its 0 we read the 16 lsb  
    return ret;
}

uint16_t pcicheckdevices(uint8_t bus,uint8_t slot){
    uint32_t input;
    input=pciReadWord(bus,slot,0,0);
//device = pciReadWord(bus,slot,0,2);
//now we want to initialize the PATA IDE drive if that it the one here


/*
for general case if other devices are used but for our case we only care about the IDE drive so we will literally just scan for the subclass code of that for now i will hopefully add more stuff later if i dont abandon this project 
if((input&0xFFFF)==0xFFFF)return;

if((pciReadWord(bus,slot,0,0xC)<<16)&0xFF!=0){
    //multiple function device 
    
}
*/
if((input&0xFFFF)!=0xFFFF)initdevice(bus,slot);


}

void checkallbuses(uint8_t bus,uint8_t devicenum){
   for(bus=0;bus<256;bus++){
        for(devicenum=0;devicenum<32;devicenum++){
            pcicheckdevices(bus,devicenum);
        } 
   }
}

