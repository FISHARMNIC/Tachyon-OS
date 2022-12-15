#include <stdint.h>

typedef int (kernel_app_t)(char**);

extern void* syscalls[10];
extern kernel_app_t* appcalls[10];
extern char* appcalls_names[10];

typedef uint16_t * FILEp;
extern FILEp WRITESTREAM;
extern FILEp VGA_STREAM;

#define fn(rt, id, ...) (rt(*)(__VA_ARGS__))(syscalls[id])
#define call(_fn, ...) (_fn)(__VA_OPT__(__VA_ARGS__))

static inline void putch(char ch)
{
    call(fn(void, 0, char), ch);
}
static inline void puts(char *str)
{
    call(fn(void, 1, char *), str);
}
static inline void puti(uint32_t i)
{
    call(fn(void, 2, uint32_t), i);
}
static inline void putd(double d)
{
    call(fn(void, 3, double), d);
}
static inline void putln()
{
    call(fn(void, 4));
}
static inline void clrscr()
{
    call(fn(void, 5));
}

static inline char getc()
{
    return call(fn(char, 6));
}

static inline char * gets(char * ptr, int size)
{
    return call(fn(char*, 7, char*, int), ptr, size);
}

static inline int geti()
{
    return call(fn(int, 8));
}

static inline double getd()
{
    return call(fn(double, 8));
}

#undef fn
#undef call