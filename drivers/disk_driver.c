#include "disk_driver.h"
#include "pci.h"

ide_struct get_bar_addresses(uint8_t bus,uint8_t devnum){
    ide_struct bars;
    bars.BAR0 = pciReadWord(bus,devnum,0,0x10);
    bars.BAR1 = pciReadWord(bus,devnum,0,0x14);
    bars.BAR2 = pciReadWord(bus,devnum,0,0x18);
    bars.BAR3 = pciReadWord(bus,devnum,0,0x1C);
    bars.BAR4 = pciReadWord(bus,devnum,0,0x20);
    bars.BAR5 = pciReadWord(bus,devnum,0,0x24);
    return bars;
    
}
void initIDE(uint8_t bus,uint8_t slot){
    

}
