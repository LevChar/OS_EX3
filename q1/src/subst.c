/* ======================================================== */
/*   subst.c	 			      						    */
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/subst.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
void 
usage_err(int i_num_of_rcvd_args);

void 
subst_loop(char i_ch_to_look_for, char i_ch_to_replace);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE 
void 
usage_err(int i_num_of_rcvd_args)
{
  fprintf(stderr, "Expecting two arguments, got %d arguments\n", --i_num_of_rcvd_args);
  fprintf(stderr, "the arguments should be two charachters: The first is the origin charachter\n");
  fprintf(stderr, "and the second is the charachter that replaces each occurance of the first\n");
  exit(EXIT_ERROR_WRONG_ARGS);
}

PRIVATE 
void 
subst_loop(char i_ch_to_look_for, char i_ch_to_replace)
{
	char buff[MAX_LINE_LENGTH];
	size_t nbytes = 0;
	
	while (0 != (nbytes=read(STDIN_FILENO, buff, MAX_LINE_LENGTH))) 
	{ 
		buff[nbytes-1] = '\0';		
		for(int i=0; i < nbytes ;i++)
		{
			if(buff[i] == i_ch_to_look_for)
			{
				buff[i] = i_ch_to_replace;
			}
		}
		
		dprintf(STDOUT_FILENO, "%s\n", buff);
    } 
}


int 
main(int argc, char* argv[])
{
	char ch_to_look_for, ch_to_replace;
	
	if (argc != REQUIRED_AMOUNT_OF_ARGS) { usage_err(argc); }
	
	ch_to_look_for = argv[1][0];
	ch_to_replace = argv[2][0];
	
	subst_loop(ch_to_look_for, ch_to_replace);
	
	exit(0);
}