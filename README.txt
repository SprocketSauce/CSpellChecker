=====================================================
* COMP1001: UNIX and C programming                  *  
* Semester 2, 2017                                  *
* Assignment                                        *
*-------------------------------------------------- *
* By Jack McNair                                    *
* 18927430                                          *
=====================================================

=====INSTRUCTIONS=====

   TO COMPILE:
	make

   TO RUN:
	./spellCheck <filename>

=====FILES=====

 spellCheck.c - Contains main. Run to check spelling 
                on a text file.
 linkedList.h - Describes a linked list, declares all 
                relevant methods.
 linkedList.c - Contains all functionality for 
                manipulating a linked list.
     config.h - Describes a config struct, declares 
                all relevant methods.
     config.c - Contains functionality for loading a 
                .spellconf file.
     makefile - Allows for easy compilation and 
                cleaning.
   .spellconf - Configuration file.
        words - Default dictionary file.
   README.txt - You're reading it.

=====COMPLETION=====

   As far as I am aware, all required functionality has
   been implemented and is working.

=====KNOWN BUGS=====

 - The maximum word length is 45 characters (length of
   pneumonoultramicroscopicsilicovolcanoconiosis, the
   longest word in the dictionary). Words longer than 
   this will be split up.

=====TESTED ON=====

 - 314.232: BR56HZ1
