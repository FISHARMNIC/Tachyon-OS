extern int strcmp(char *str1, char *str2)
{
    char diff = 0;
    while (1)
    {
        diff = *str1 - *str2;
        if (diff != 0)
            return diff;
        if (*(str1++) == 0)
            return 0;
        str2++;
    }
}

extern void strcpy(char * dest, char * src)
{
    while(*src != 0)
        *(dest++) = *(src++);
    *dest = 0;
}

extern int strlen(char * str)
{
    int ctr = 0;
    while(*str != 0) {
        ctr++;
        str++;
    }
    return ctr;
}

void *__memclr_ptr;
int __memclr_sz;

#define memclr(mem, type, size)      \
    __memclr_sz = size;              \
    __memclr_ptr = mem;              \
    while (__memclr_sz-- > 0)        \
        *((type *)__memclr_ptr) = 0; \
    __memclr_ptr += sizeof(type);

extern void strclr(char *buff, unsigned size)
{
    while (size--)
        *(buff++) = 0;
}