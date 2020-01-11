#include "ex3_q2.h"
#define DEBUG 1
#define DEB if(DEBUG) printf("func: %s, line: %d\n",__func__, __LINE__);
//=============================GLOBAL============================================
//Main Buffer
lluint g_buffer[BUF_SIZE] = {};
//global Counters & also pointers to the place in the buffer
int g_total_msgs_created = 0;
int g_total_msgs_read = 0;
//Used For ID's of threads.
Uint g_created_consumer_id = 1;
Uint g_created_producer_id = 1;
//Consumer and producer threads array
pthread_t threads_t[N_CONS + N_PROD];
//Mutex declaration
pthread_mutex_t array_Lock_mutex;
pthread_mutex_t print_Lock_mutex;
//Semaphore declaration
sem_t* sem_start_timing;
sem_t* sem_sync_awalibale_work;
sem_t* sem_sync_awalibale_space;
sem_t* sem_amt_of_read_msgs;
sem_t* sem_amt_of_writed_msgs;
//=============================PROTOTYPES========================================
void* producer(void *ptr);
void* consumer(void *ptr);
void unlink_all_sem(void);
void open_all_sem(void);
void executiion__initialization(void);
void executiion_destruction(void);
void initialize_and_start_consumers_and_producers(void);
void initialize_and_start_consumers(void);
void initialize_and_start_producers(void);
void calc_rand_prime_numbers(lluint *n1, lluint *n2, lluint *prod);
void write_remove_from_buf_consumer(int thread_num, lluint n1, lluint n2, lluint prod);
//===============================================================================

int 
main(void)
{	
	executiion__initialization();
	initialize_and_start_consumers_and_producers();
	
	for (int i=0 ; i < (N_PROD + N_CONS) ; i++)
	{
		pthread_join(threads_t[i], NULL);
		
		if(i == (N_PROD - 1))
		{
			printf("all producers terminated\n");
		}
	}
	
	printf("all consumers terminated\n");			
					
	executiion_destruction();
	return 0;	
}

void 
executiion__initialization(void)
{
	array_Lock_mutex = PTHREAD_MUTEX_INITIALIZER;
	print_Lock_mutex = PTHREAD_MUTEX_INITIALIZER;
	open_all_sem();
}


void 
executiion_destruction(void)
{
	pthread_mutex_destroy(&array_Lock_mutex);	
	pthread_mutex_destroy(&print_Lock_mutex);
	unlink_all_sem();
}

void 
initialize_and_start_consumers_and_producers(void)
{
	initialize_and_start_producers();
	printf("main thread created all producer threads\n");
	
	initialize_and_start_consumers();
	printf("main thread created all consumer threads\n");
	
	for (int i=0 ; i < (N_PROD + N_CONS)  ; i++)
	{
		sem_post(sem_start_timing);
	}
}

void 
initialize_and_start_producers(void)
{
	for (int i=0 ; i < N_PROD ; i++)
	{
		pthread_create(&threads_t[i], NULL, producer, NULL);
	}
}

void 
initialize_and_start_consumers(void)
{
	for (int i=N_PROD ; i < (N_PROD + N_CONS) ; i++)
	{
		pthread_create(&threads_t[i], NULL, consumer, NULL);
	}
}

void* 
producer(void *ptr)
{
	sem_wait(sem_start_timing);
	
	Uint prod_id = g_created_producer_id++;
	lluint rand_1, rand_2, mult;
	
	srand((unsigned int)pthread_self() * time(NULL));
	
	while(1)
	{		
		calc_rand_prime_numbers(&rand_1, &rand_2, &mult);
		add_to_buf(mult);
		
		pthread_mutex_lock(&print_Lock_mutex);    //get the lock
		write_add_to_buf_msg(prod_id, rand_1, rand_2, mult);
		pthread_mutex_unlock(&print_Lock_mutex);  //release the lock	

		pthread_mutex_lock(&print_Lock_mutex);    //get the lock		
		write_producer_is_done(prod_id);
		pthread_mutex_unlock(&print_Lock_mutex);  //release the lock		
	}	
	
	return NULL;
}

void 
add_to_buf(lluint prod)
{	
	if (sem_trywait(sem_amt_of_writed_msgs) != 0) 
	{
		pthread_exit(NULL);
	}
	
	sem_wait(sem_sync_awalibale_space);	
	pthread_mutex_lock(&array_Lock_mutex);    //get the lock
	g_buffer[g_total_msgs_created % BUF_SIZE] = prod;
	g_total_msgs_created++;
	pthread_mutex_unlock(&array_Lock_mutex);  //release the lock
	sem_post(sem_sync_awalibale_work);
}

void 
calc_rand_prime_numbers(lluint *i_n1, lluint *i_n2, lluint *i_prod)
{	
	while(1)
	{
		while(1)
		{
			*i_n1 = get_random_in_range();
			if(is_prime(*i_n1))
			{
				break;
			}
		}
		
		*i_n2 = get_random_in_range();
		if(is_prime(*i_n2))
		{
				break;
		}
	}	
	
	*i_prod = (*i_n1) * (*i_n2);
}

void* 
consumer(void *ptr)
{
	sem_wait(sem_start_timing);
	
	Uint cons_id = g_created_consumer_id++;
	lluint mult, factor_1, factor_2;
	
	while(1)
	{		
		remove_from_buf(&mult);
		
		pthread_mutex_lock(&print_Lock_mutex);    //get the lock					
		write_remove_from_buf_msg(cons_id, &mult);
		pthread_mutex_unlock(&print_Lock_mutex);  //release the lock			
		
		find_two_factors(mult, &factor_1, &factor_2);					
		
		pthread_mutex_lock(&print_Lock_mutex);    //get the lock		
		write_remove_from_buf_consumer(cons_id, factor_1, factor_2, mult);	
		pthread_mutex_unlock(&print_Lock_mutex);  //release the lock						
		
		pthread_mutex_lock(&print_Lock_mutex);    //get the lock			
		write_consumer_is_done(cons_id);
		pthread_mutex_unlock(&print_Lock_mutex);  //release the lock	
	}
	
	return NULL;
}

void 
remove_from_buf(lluint* prod)
{		
	if (sem_trywait(sem_amt_of_read_msgs) != 0) 
	{
		pthread_exit(NULL);
	} 

	sem_wait(sem_sync_awalibale_work);
	pthread_mutex_lock(&array_Lock_mutex);    //get the lock
	*prod = g_buffer[g_total_msgs_read % BUF_SIZE];	
	g_total_msgs_read++;
	pthread_mutex_unlock(&array_Lock_mutex);  //release the lock
	sem_post(sem_sync_awalibale_space);
}

void 
write_remove_from_buf_consumer(int thread_num, lluint n1, lluint n2, lluint prod)
{
  printf("consumer #%d ", thread_num); fflush(stdout);
  my_sleep();
  write_product("", n1, n2, prod);
  my_sleep(); 
}

void 
open_all_sem(void)
{
	unlink_all_sem();
	
	sem_start_timing = sem_open("/sem_start_timing", 
								O_CREAT, 
								S_IRWXU, 
								0);
								
	if (sem_start_timing == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_start_timing\n");
		exit(EXIT_FAILURE);
	}	
	
	sem_sync_awalibale_work = sem_open("/sem_sync_aval_work", 
								O_CREAT, 
								S_IRWXU, 
								AVALIBLE_ITEMS_AT_START);
	
	if (sem_sync_awalibale_work == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_sync_aval_work\n");
		exit(EXIT_FAILURE);
	}	
	
	sem_sync_awalibale_space = sem_open("/sem_sync_aval_space", 
								O_CREAT, 
								S_IRWXU, 
								AVALIBLE_SPACE);
	
	if (sem_sync_awalibale_space == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_sync_aval_space\n");
		exit(EXIT_FAILURE);
	}	
	
	sem_amt_of_read_msgs = sem_open("/sem_sync_amt_of_read_msgs", 
								O_CREAT, 
								S_IRWXU, 
								TOTAL_MSG);
	
	if (sem_sync_awalibale_space == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_sync_amt_of_read_msgs\n");
		exit(EXIT_FAILURE);
	}	
	
	sem_amt_of_writed_msgs = sem_open("/sem_sync_amt_of_writed_msgs", 
								O_CREAT, 
								S_IRWXU, 
								TOTAL_MSG);
	
	if (sem_sync_awalibale_space == SEM_FAILED)
	{
		perror("failed to open semaphore /sem_sync_amt_of_writed_msgs\n");
		exit(EXIT_FAILURE);
	}	
}

void 
unlink_all_sem(void)
{
	sem_unlink("/sem_start_timing");
	sem_unlink("/sem_sync_aval_work");
	sem_unlink("/sem_sync_aval_space");
	sem_unlink("/sem_sync_amt_of_read_msgs");
	sem_unlink("/sem_sync_amt_of_writed_msgs");
}