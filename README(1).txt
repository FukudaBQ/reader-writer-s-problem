/*Beau QU
 *CSE 2431
 *README for lab2
 */

1. How to compile this program: 
	download lab2.c and buffer.h
	put buffer.h in the same directory with lab2.c
	use the command "gcc lab2.c -lpthread -lrt"
	a file called a.out will appear
2. How to run the program
	type
		a.out argv1 argv2 argv3
	where argv1 is how long to sleep before terminating
	argv2 is the number of producer threads
	argv3 is the number of consumer threads