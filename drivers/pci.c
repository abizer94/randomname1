#include "pci.h"

uint16_t pciReadWord(uint8_t bus ,uint8_t device, uint8_t func, uint8_t reg){
    uint32_t addr;
    uint32_t lbus = (uint32_t)bus; //8 bits for bus
    uint32_t ldev = (uint32_t)device;// 5 bits for device number 
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
    address | (reg&252)register has to have the last 2 bits 0 we can also do (reg&0xfc) 
    */
    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (reg & 0xFC) | ((uint32_t)0x80000000));
    
    port_byte_out(0xCF8,address);
    ret = (uint16_t)((port_byte_in(0xCFC)>>((offset&2)*8)) & 0xFFFF);//so we may wanto to read either the first or second 16 bits the offset depending on the register offset so if offset is 1 we read the 16 msb but if its 0 we read the 16 lsb  
    return ret;
}
