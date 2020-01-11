# OS_EX3
Third project(Exercise) in OS course.

## **Purpose:**
Those two Programs were written as part of
assignment number 3 in OS course. 

## **First program:**
The first program, which consists of two sub-programs, is making substitution
of letters of input, according to a series of given substitutions.
The program "subst", which is a helper program of the program "ex3_q1", receives 2
arguments - the first is the original char, the second is the substitution char, the
program receives input strings until CTRL+D is pressed. It switches each original char
to substitution char inside each input string.
The program "ex3_q1" receives 3 arguments -  the first is a string of original characters,
the second is a string of substitution characters and the third is an output filename,
where the results of the execution will be stored. the program receives input strings until
CTRL+D is pressed. It switches all the original characters to substitution characters
inside each input string, using the "subst" program. If we denote the length of the original
characters string with 'n', then "ex3_q1" launches 'n' instances of "subst" program, each
one is responsible for substitution of one original character to the substitution character,
the multiprocessing of "subst" programs are communicating using pipes that connect each 
process to the next one, the first instance is connected to STDIN and the last is connected
to the file, which name we received inside the 3rd argument, as mentioned above.

## **Second program:**
The second program is an implementation of a version of the producer-consumer problem.
In this program, there are 2 producers and 3 consumers, Each producer grills prime numbers
and puts their multiplication to a common cyclic buffer, which can hold up to 4 members at 
the same time. all of the producers should produce a total of 7 messages, which will be 
"consumed" by the consumers. By "consumed", I mean that the consumer will remove one 
multiplication from the buffer and find the two prime numbers from which it was made.
This exercise trains for simultaneous execution of threads, while scheduling access to shared
resources through use of Mutexes and Semaphores.

## **To run the programs:**
Download \ clone the whole repo & run make command from 
each of the folders - "q1" and "q2".

## **Compatibility:**
The programs were compiled and tested in Linux (Ubunto) environment 
and in cygwin environment (under windows 10 OS).
