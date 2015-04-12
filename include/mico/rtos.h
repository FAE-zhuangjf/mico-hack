#ifndef RTOS_H
#define RTOS_H

#include <types.h>

#define mico_thread_sleep                 sleep

#ifdef NO_MICO_RTOS
#define mico_thread_msleep                mico_thread_msleep_no_os
#else
#define mico_thread_msleep                msleep
#endif

#define mico_rtos_suspend_all_thread      vTaskSuspendAll
#define mico_rtos_resume_all_thread       xTaskResumeAll

#define MICO_NEVER_TIMEOUT   (0xFFFFFFFF)
#define MICO_WAIT_FOREVER    (0xFFFFFFFF)
#define MICO_NO_WAIT         (0)

typedef void (*mico_thread_function_t)( void* arg );
typedef void* mico_semaphore_t;
typedef void* mico_mutex_t;
typedef void* mico_thread_t;
typedef void* mico_queue_t;
typedef void* mico_event;// MICO OS event: mico_semaphore_t, mico_mutex_t or mico_queue_t

typedef void (*timer_handler_t)( void* arg );

typedef struct
{
  void *          handle;
  timer_handler_t function;
  void*           arg;
}mico_timer_t;

#define MICO_NETWORK_WORKER_PRIORITY      (3)
#define MICO_DEFAULT_WORKER_PRIORITY     	 (5)
#define MICO_DEFAULT_LIBRARY_PRIORITY    	 (5)
#define MICO_APPLICATION_PRIORITY         	(7)

int mico_rtos_create_thread( mico_thread_t* thread, uint8_t priority, const char* name, mico_thread_function_t function, uint32_t stack_size, void* arg );

int mico_rtos_delete_thread( mico_thread_t* thread );

void mico_rtos_suspend_thread(mico_thread_t* thread);

void mico_rtos_suspend_all_thread(void);

long mico_rtos_resume_all_thread(void);

int mico_rtos_thread_join( mico_thread_t* thread );

int mico_rtos_thread_force_awake( mico_thread_t* thread );

bool mico_rtos_is_current_thread( mico_thread_t* thread );

void mico_thread_sleep(uint32_t seconds);

void mico_thread_msleep(uint32_t milliseconds);

int mico_rtos_init_semaphore( mico_semaphore_t* semaphore, int count );

int mico_rtos_set_semaphore( mico_semaphore_t* semaphore );

int mico_rtos_get_semaphore( mico_semaphore_t* semaphore, uint32_t timeout_ms );

int mico_rtos_deinit_semaphore( mico_semaphore_t* semaphore );

int mico_rtos_init_mutex( mico_mutex_t* mutex );

int mico_rtos_lock_mutex( mico_mutex_t* mutex );

int mico_rtos_unlock_mutex( mico_mutex_t* mutex );

int mico_rtos_deinit_mutex( mico_mutex_t* mutex );

int mico_rtos_init_queue( mico_queue_t* queue, const char* name, uint32_t message_size, uint32_t number_of_messages );

int mico_rtos_push_to_queue( mico_queue_t* queue, void* message, uint32_t timeout_ms );

int mico_rtos_pop_from_queue( mico_queue_t* queue, void* message, uint32_t timeout_ms );

int mico_rtos_deinit_queue( mico_queue_t* queue );

bool mico_rtos_is_queue_empty( mico_queue_t* queue );

int mico_rtos_is_queue_full( mico_queue_t* queue );

__weak uint32_t mico_get_time(void);

uint32_t mico_get_time_no_os(void);

__weak int mico_init_timer( mico_timer_t* timer, uint32_t time_ms, timer_handler_t function, void* arg );

__weak int mico_start_timer( mico_timer_t* timer );

__weak int mico_stop_timer( mico_timer_t* timer );

int mico_reload_timer( mico_timer_t* timer );

int mico_deinit_timer( mico_timer_t* timer );

bool mico_is_timer_running( mico_timer_t* timer );

int mico_create_event_fd(mico_event handle);
int mico_delete_event_fd(int fd);

#endif