# OS_EX3
Third project(Exercise) in OS course.

## **Purpose:**
Those two Programs were written as part of
assignment number 3 in OS course. 

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

## **To run the program:**
Download \ clone the whole repo & run make command from 
each of the folders - "q1" and "q2".

## **Compatibility:**
Program was compiled and tested in Linux (Ubunto) environment 
and in cygwin environment (under windows 10 OS).
