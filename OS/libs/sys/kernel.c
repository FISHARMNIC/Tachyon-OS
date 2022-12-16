#define SYSCALLS_MAX 10
#define APPCALLS_MAX 10
#define NULL ((void*)0)

void *syscalls[SYSCALLS_MAX]; // System call table

typedef int (kernel_app_t)(char**);
kernel_app_t* appcalls[APPCALLS_MAX]; // Application call table
char *appcalls_names[APPCALLS_MAX]; // Application call name map
uint16_t __memoryspacer[100];
uint16_t __tempmem__[1000];

extern void* syscalls[SYSCALLS_MAX];
extern kernel_app_t* appcalls[APPCALLS_MAX];
extern char*appcalls_names[APPCALLS_MAX];
extern uint16_t __tempmem__[1000];

#define syscallPromote(ind, fn) syscalls[ind] = (void*)(fn)

void syscallInit() 
{
    syscallPromote(0, putch);
    syscallPromote(1, puts);
    syscallPromote(2, puti);
    syscallPromote(3, putd);
    syscallPromote(4, putln);
    syscallPromote(5, clrscr);
    syscallPromote(6, getc);
    syscallPromote(7, gets);
    syscallPromote(8, geti);
    syscallPromote(9, getd);
}

void appcallInit()
{
    // Clear all app pointers
    for(int i = 0; i < APPCALLS_MAX; i++)
    {
        appcalls_names[i] = NULL;
        appcalls[i] = NULL;
    }
}

void systemInit()
{
    syscallInit();
    verbose_state(0, "SYSCALLS SETUP");
    appcallInit();
    verbose_state(0, "APPCALLS SETUP");
    ata_send_identify_boot_test();
}

void applicationPromote(kernel_app_t* app, char * name)
{
    for(int i = 0; i < APPCALLS_MAX; i++)
    {
        if(appcalls[i] == NULL)
        {
            appcalls[i] = app;
            appcalls_names[i] = name;
            return;
        }
    }
}

extern kernel_app_t* applicationSeek(char * name)
{
    for(int i = 0; i < APPCALLS_MAX; i++)
    {
        if(appcalls_names[i] != NULL && strcmp(appcalls_names[i], name) == 0)
        {
            return appcalls[i];
        }
    }
    return NULL;
}

#undef syscallPromote