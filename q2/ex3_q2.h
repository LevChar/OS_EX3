/* ======================================================== */
/*   ex3_q2.h		        						    	*/
/* ======================================================== */
#ifndef EX3_Q2_H
#define EX3_Q2_H

#define _XOPEN_SOURCE 500
//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <semaphore.h>		 /* For usage of semaphores */
#include <sys/stat.h>        /* For mode constants */
#include <pthread.h>		 /* For usage of threads */
#include <string.h>          /* For strncat() */
#include <stdlib.h>			 /* For exit() */
#include <unistd.h>			 /* For usleep() */
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>			 /* For perror() */
#include <stdio.h>			 /* For printf() */
#include <math.h>			 /* For sqrt() */
#include "ex3_q2_given.h"

//---------------------------------------------------------------------------
//-------------------------- General Typedefs -------------------------------
//---------------------------------------------------------------------------
typedef unsigned int Uint;

//---------------------------------------------------------------------------
//---------------------- Syncronization Definitions -------------------------
//---------------------------------------------------------------------------
#define AVALIBLE_SPACE 4
#define AVALIBLE_ITEMS_AT_START 0

#endif // !EX3_Q2_H