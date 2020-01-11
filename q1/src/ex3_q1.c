/* ======================================================== */
/*   ex3_q1.c 				      						    */
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/ex3_q1.h"

//Declaration of fileno() MACRO for disabling the warning about it.
int fileno(FILE *stream);

//---------------------------------------------------------------------------
//----------------------------- Global Variables ----------------------------
//---------------------------------------------------------------------------
int **g_pipes;
Uint g_size_of_pipes_array;

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
void 
usage_err(int i_num_of_rcvd_args);

Uint 
get_min_length(char *i_str1, char *i_str2);

int**
allocate_pipe_array(int elem_count, int i_fd_out);

int
file_loader(char* i_f_name);

void
allocate_pipe(int *i_pipe_to_allocate);

void
redirect_input(int i_input_fd);

void
redirect_output(int i_output_fd);

void
initialize_and_execute_son(char** i_args_to_subst, size_t i_idx);

char**
generate_arguments(char i_to_look_for, char i_to_replace_with);

int
load_output_file(char* i_filename);

void
close_irrelevant_pipes(size_t i_curr_idx, size_t i_size_of_pipe_array);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE 
void
initialize_and_execute_son(char** i_args_to_subst, size_t i_idx)
{		
	close_irrelevant_pipes(i_idx, g_size_of_pipes_array);
	
	//redirection before launching new instance of SUBST
	redirect_input(g_pipes[i_idx][PIPE_READ_END]);
	redirect_output(g_pipes[i_idx + 1][PIPE_WRITE_END]);
	
	execve(i_args_to_subst[0], i_args_to_subst, NULL);
	fprintf(stderr, "*** ERROR: *** EXEC of %s FAILED\n", i_args_to_subst[0]);
	exit(EXIT_ERROR_IN_EXECVE);
}

PRIVATE 
int
load_output_file(char* i_filename)
{
	return file_loader(i_filename);
}

PRIVATE 
char**
generate_arguments(char i_to_look_for, char i_to_replace_with)
{
	char **generated_arguments = malloc(sizeof(char*) * 4);
	
	generated_arguments[0] = SUBST_PROG;
	generated_arguments[1] = malloc(2);
	generated_arguments[2] = malloc(2);
	generated_arguments[1][0] = i_to_look_for;
	generated_arguments[1][1] = '\0';
	generated_arguments[2][0] = i_to_replace_with;
	generated_arguments[2][1] = '\0';
	generated_arguments[3] = NULL;
	
	return generated_arguments;
}

PRIVATE 
void 
usage_err(int i_num_of_rcvd_args)
{
  fprintf(stderr, "Expecting three arguments, got %d arguments\n", --i_num_of_rcvd_args);
  fprintf(stderr, "the arguments should be 2 strings and 1 filename: The first is the origin string\n");
  fprintf(stderr, "the second is the string from witch te program  takes the replacement charachters\n");
  exit(EXIT_ERROR_WRONG_ARGS);
}

PRIVATE 
Uint 
get_min_length(char *i_str1, char *i_str2)
{
	return (strlen(i_str1) > strlen(i_str2)) ? strlen(i_str1) : strlen(i_str2);
}

PRIVATE 
int**
allocate_pipe_array(int elem_count, int i_fd_out)
{
	int i;
	int** new_arr = malloc(sizeof(int*) * (elem_count + 1));
	
	for(i = 0; i <= elem_count;i++)
	{
		new_arr[i] = malloc(sizeof(int)*2);
	}
	
	for(i = 1; i < elem_count;i++)
	{
		allocate_pipe(new_arr[i]);
	}
	
	//Definition of what's happening in the edjes of the pipes
	new_arr[0][0] = STDIN_FILENO;
	new_arr[0][1] = UNDEF_FD;
	new_arr[elem_count][0] = UNDEF_FD;
	new_arr[elem_count][1] = i_fd_out;
	
	return new_arr;
}

PRIVATE 
int
file_loader(char* i_f_name)
{
	int opened_fd = fileno(fopen(i_f_name, "w"));
	
	if (opened_fd < 0)  // open failed
	{
		fprintf(stderr, 
				"ERROR: open \"%s\" failed (%d). Exiting\n", 
				i_f_name, 
				opened_fd);
				
		exit(EXIT_ERROR_OPENING_OUTPUT_FILE);
	}
	return opened_fd;
}

PRIVATE 
void
allocate_pipe(int *i_pipe_to_allocate)
{
	if (pipe(i_pipe_to_allocate) == -1)
		{
			fprintf( stderr, "cannot open pipe\n") ;
			exit(EXIT_ERROR_OPENING_PIPE) ;
		}
}

PRIVATE 
void
redirect_input(int i_input_fd)
{
	if(dup2(i_input_fd, STDIN_FILENO) < 0) { perror("Error redirecting stdin...\n"); }
}

PRIVATE 
void
redirect_output(int i_output_fd)
{
	if(dup2(i_output_fd, STDOUT_FILENO) < 0) { perror("Error redirecting stdout...\n"); }
}

PRIVATE
void
close_irrelevant_pipes(size_t i_curr_idx, size_t i_size_of_pipe_array)
{	
	close(g_pipes[i_curr_idx][PIPE_WRITE_END]);
	close(g_pipes[++i_curr_idx][PIPE_READ_END]);
			
	for(int i = ++i_curr_idx; i <= i_size_of_pipe_array ;i++)
	{			
		close(g_pipes[i][PIPE_READ_END]);
		close(g_pipes[i][PIPE_WRITE_END]);
	}
}

int main(int argc, char* argv[])
{
	int pid;
	size_t i;
	char **argv_to_subst;
	
	if (argc != REQUIRED_AMOUNT_OF_ARGS) { usage_err(argc); }

	int fd_out = load_output_file(argv[3]);

	g_size_of_pipes_array = get_min_length (argv[1], argv[2]);
	g_pipes = (int**)allocate_pipe_array(g_size_of_pipes_array, fd_out);

	for(i = 0; i < g_size_of_pipes_array ; ++i)
	{	
		argv_to_subst = generate_arguments(argv[1][i], argv[2][i]);
		pid = fork();
		
		if (pid <0)								//Error Section
		{
			perror("Cannot fork()");
			exit(EXIT_FORCING);
		}
		else if (pid == 0)						//Child Section
		{
			initialize_and_execute_son(argv_to_subst, i);
		}
		
		close(g_pipes[i][PIPE_WRITE_END]);
		close(g_pipes[i][PIPE_READ_END]);
		free(g_pipes[i]);
		free(argv_to_subst);
	}
	
	for(i = 0; i < g_size_of_pipes_array ; ++i) 
	{ 
		wait(NULL); 
	}
	
	//close the outputfile & release pipes array
	close(g_pipes[i][PIPE_WRITE_END]);
	close(g_pipes[i][PIPE_READ_END]);
	
	exit(0);
}