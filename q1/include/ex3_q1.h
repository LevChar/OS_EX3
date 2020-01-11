/* ======================================================== */
/*   ex3_q1.h 				      						    */
/* ======================================================== */
#ifndef SUBST_H_
#define SUBST_H_

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdio.h>		//for fprintf(), perror()
#include <stdlib.h>		//for exit()
#include <unistd.h>		//for read()
#include <string.h> 	//for strlen()
#include <sys/wait.h> 	//for wait()

//---------------------------------------------------------------------------
//----------------------------- General Defines -----------------------------
//---------------------------------------------------------------------------
#define EXIT_ERROR_WRONG_ARGS 1
#define EXIT_ERROR_OPENING_OUTPUT_FILE 2
#define EXIT_ERROR_OPENING_PIPE 3
#define EXIT_FORCING 4
#define EXIT_ERROR_IN_EXECVE 5
#define PRIVATE
#define PUBLIC
#define REQUIRED_AMOUNT_OF_ARGS 4
#define SUBST_PROG "subst.exe"

//alias for read & write ends of pipe
#define PIPE_READ_END 0
#define PIPE_WRITE_END 1
#define UNDEF_FD -1

//---------------------------------------------------------------------------
//----------------------------- General typedefs ----------------------------
//---------------------------------------------------------------------------
typedef unsigned int Uint;

#endif // !SUBST_H_