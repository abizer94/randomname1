1.  Before we can make a shell we need the keyboard to be able to do more than just print the key value 
    we need it to store said value in a buffer ie add some actual functionality to the keyboard driver
    
    a. make a array of characters to sotre the string 
    b. make a lookup table for scancode vs char 
    c. make a backspace function in display driver 
    d. make a backspace function in the kerybaord driver 
    e. change callback function to add to array and then pprint the character 
    
2. now we need to make a parser basically something that on pressing enter checks if the string in buffer matches a known command and then executes it 

	a. make compare string function
	b. compare the buffer with known commands andexecute the appropriate one where necessary 
	
3. Now we need some memory management so that we can actually have useful commands
	
	a.For memory allocation we need to be able to dynamically allocate memory but malloc is actually 
	something that works with the os so we need to create a memory allocation system traditionally 
	we use heap to do this but that is too bigbrain for a first os maker so we will be using a simple 
	linked list where in our memory every chunk will have a node of linked list at the beginning ie a 
	request for 1024 byte chunk will have allocate 1040 byte 1024 for the actual memory and an extra 
	16 for the node  (the node would have 8 bytes for the pointer 4 for the int and 1 for the bool we will 
	also be adding a padding of 3 bytes making the total 16 bytes because our cpus are designed in a way 
	where it is more efficient to access bytes with address that is a multiple of its size idk why really 
	hopefully ill learn in the next 7 sems)
	
	b. we will statically allocate a very large chunk of memory and then we will add a node at the 
	beginning with its size
	
	c. we want to allocate the smallest free chunk in memory that we can since we dont want wasted space
	so memory requested < size of free chunk and free chunk must be the minimum possible free chunk 
	
	d. given the chunk we want to use we first need to decrease the size in the list by size of req + 16  
	   this is an easy implementation
	   
4. now we want the commands to have arguments i will use ' ' as a delimiter because its just easy to do for the same reason i am not adding pipes forks etc beacuase i am not making this os with multiple threads rn i might do that after i am done with all the drives or it might just be easier to make a new one idk
	a. change the compare func to compare to a list of commands 
	(later we want it to compare to all executables in the path of our env but i dont really have 
	storage so i cant really do that)
	b. if the first word is a valid command then look at the arguments and feed it to the process
	




