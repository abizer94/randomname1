1. Make sure cpu is in real mode since some bioses start it in protected mode idk why

2. Set origin to 7c00 since thats where the bios loads the mbr to setting org doesnt actually affect where the code will be put it is just used to calculate memory addresses correctly for the code


3. Store bootdrive (stored in dl when bios loads the mbr) and koffset in some variable to be used later

4. Load the kernel to memory
	If we do this in real mode 16bit mode we can directly call a bios interrupt to load kernel 
	int 0x13 
	*int 0x13 is originally for hard disks and may not work for specific* 
	*bios modes it must be in legacy mode and the SSD must be configured* 
	*to support BIOS-compatible sector reads*
	Arguments 
	a. Load ah with 02
	AH=00h: Resets the disk system
	AH=01h: Gets the status of the last drive operation
	AH=02h: Reads sectors from a drive
	AH=03h: Writes sectors to a drive
   	AH=04h: Verifies sectors from a drive
	AH=05h: Formats a track
	AH=06h: Formats a track and sets bad sector flags
	AH=07h: Formats a drive starting at a track
	AH=08h: Reads drive parameters
	AH=09h: Initializes drive pair characteristics
	AH=0Ah: Reads long sectors from a drive
	AH=41h: Checks extensions present
	AH=42h: Extended read sectors from a drive
	AH=43h: Extended write sectors to a drive
	AH=48h: Extended read drive parameters
	AH=4Bh: Gets the drive emulation type
	
	b. We will be using 02 so only arguments for that 
	AL: Number of sectors to read
	CH: Cylinder number (track) on the disk
	CL: Sector number and higher bits of the cylinder
	DH: Head number
	DL: Drive number
	ES:BX: Memory address to store the read data

5. Switch to 32bit protected mode

 
