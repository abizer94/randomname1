1. Make sure cpu is in real mode since some bioses start it in protected mode idk why

2. Set origin to 7c00 since thats where the bios loads the mbr. Setting org doesnt actually affect where the code will be put it is just used to calculate memory addresses correctly for the code


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
	a. Creating a GDT (Global Discriptor Table) basically in 32 bit system we divide memory into segments 	
	that makes it easier to use we may decide how many segments we want but conventionally we have 3 main
	segments 1 null segment the first entry just has 00 2 code segment this is the segment where we will 
	add code to be executed 3 data segment this has data to be stored
	
	A GDT has a pretty unintuitive and awkward structure imo maybe there is some 
	genius logic to why it is setup like this or i simply didnt read the wiki entirly and missed the
	part where they explained why
	
	For a specific segment (explanations in the code of gdt.asm)
	bits 0-15  Segment limit /length 
	bits 16-31 Base address(0:15) the first 16 bits of the base address
	bits 32-39 Base address(16:23) the next 8 bits of the address
	bits 40-43 Access byte (type privilage etc)
	bits 44-47 Flags and last 4 bits of segment length
	bits 48-55 Base address (24:31) 8 high bits of the address 
	
	
	
	b. after making the gdt we can finally switch to 32 bit and hand control over to the kernel
		1. disable interrupts using cli
		2. load gdt discriptor to lgdt redistor
		3. enable protected mode using cr0
		4. jmp to the code segment
		5. setup all segment registers ds ss es fs gs to point to our data segment 
		6. setup a new 32bit stack
		7. jmp back to mbr and hand over to kernel
		
		
6. Making all of these into one .bin file that we can boot from 

	

 
