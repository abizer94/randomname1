#include "resolvepci.h"
#include "pci.h"
#include "disk_driver.h"
#include "disp.h"
#include "../shell.h"

/*
int initc0sc0(int x, int y) 
int initc0sc1(int x, int y) 
int initc01s0(int x, int y) 
int initc01s1(int x, int y) 
int (*func_matrix[2][2])(int, int) = {
    { initc0s0, initc0s1 },
    { initc01s0, initc01s1 }
};

*/

void initdevice(uint8_t bus,uint8_t slot){
    uint32_t classinfo = pciReadWord(bus,slot,0,0x08);
    uint32_t class_code = (classinfo >> 24) & 0xFF;
    uint32_t subclass_code = (classinfo >> 16) & 0xFF;
    char* stn[20];
    inttostr(class_code,*stn);
    print_s("\n");
    print_s(*stn);
    inttostr(subclass_code,*stn);
    print_s(*stn);
    if(class_code==0x01){
        print_s("classcode is 01\n");
        
        if(subclass_code==0x01){
            print_s("found disk\n");
            initIDE(bus,slot);
        }
    }
    return;
}
