#include "../libs/sys/extern.c"
#include "../libs/apps/string.h"
#define INPUTMAXLEN 20
char allinput[20][INPUTMAXLEN];

char usermem[10][INPUTMAXLEN];

#define stris(is) strcmp(allinput[i], is) == 0
#define nextArg allinput[i + 1]
#define secNextArg allinput[i + 2]
#define replaceWord(src) strcpy((char*)&allinput[i], src)

long int power(int x, int n)
{
    int i;
    int number = 1;

    for (i = 0; i < n; ++i)
        number *= x;

    return (number);
}

int stoi(char *str)
{
    int sum = 0;
    while (*str != '\0')
    {
        sum = sum * 10 + (*(str++) - 48);
    }
    return sum;
}

char* itoa(int val){
    //https://stackoverflow.com/questions/3982320/convert-integer-to-string-without-access-to-libraries
    if(val == 0)
        return "0";
    static char buf[32] = {0};
    int i = 30;
    for(; val && i ; --i, val /= 10)
        buf[i] = "0123456789abcdef"[val % 10];
    return &buf[i+1];
}

void use_input()
{
    puts("== Running... ==\n");
    for (int i = 19; i >= 0; i--)
    {
        if (allinput[i] != 0 && strlen(allinput[i]) != 0)
        {
            if (stris("puts"))
            {
                puts("(PUTS) : ");
                puts(nextArg);
                putln();
            }
            else if (stris("puti"))
            {
                puts("(PUTI) : ");
                puti(stoi(nextArg));
                putln();
            }
            else if (stris("putch"))
            {
                puts("(PUTCH) : ");
                putch(nextArg[0]);
                putln();
            }
            else if (stris("run"))
            {
                *((int (*)(char **))(applicationSeek(nextArg)));
            }
            else if (stris("sto"))
            {
                // store memory in form of
                // snum <index> <value>
                char* arg1 = nextArg;
                char* arg2 = secNextArg;
                strcpy((char*)&usermem[stoi(arg1)], arg2);
            }
            else if(stris("rcl"))
            {
                // recall memory in form of
                // rnum <index>
                // replaces current word with the value (as a string)
                replaceWord(usermem[stoi(nextArg)]);
            }
            else if(stris("clr"))
            {
                clrscr();
            }
            else if(stris("add"))
            {
                replaceWord(itoa(stoi(nextArg) + stoi(secNextArg)));
            }
            else if(stris("sub"))
            {
                replaceWord(itoa(stoi(nextArg) - stoi(secNextArg)));
            }
            else if(stris("mul"))
            {
                replaceWord(itoa(stoi(nextArg) * stoi(secNextArg)));
            }
            else if(stris("div"))
            {
                replaceWord(itoa(stoi(nextArg) / stoi(secNextArg)));
            }
            else if(stris("mwrite"))
            {
                // store to addres in memory in form of
                // mwrite <addr> <value>
                *((uint16_t*)nextArg) = stoi(secNextArg);
            }
            else if(stris("mread"))
            {
                // read directly from memory in form of
                // mread <addr> <size>
                uint16_t buffer[100];
                uint16_t* addr = (uint16_t*) stoi(nextArg);
                int n = 0;
                for(n = 0; n < stoi(secNextArg); n++)
                {
                    buffer[n] = *(addr + n);
                }
                buffer[n] = 0;
                replaceWord((char*)&buffer);
            }
            // else 
            // {
            //     puts("(ERROR) : Unkown Command '");
            //     puts(allinput[i]);
            //     puts("'\n");
            // }
        }
    }
    puts("===== Done! ====\n");
}

void get_input()
{
    while (1)
    {
        char *input = (char *)__tempmem__;
        char stay = 1;
        int index = 0;
        strclr((char*)&allinput, 20 * 20);
        while (stay)
        {
            strclr(input, 2048);
            gets(input, 2048);
            if (input[strlen(input) - 1] == ';')
            {
                if (input[0] != ';')
                {
                    input[strlen(input) - 1] = 0;
                    strcpy(allinput[index], input);
                }
                stay = 0;
            }
            else if (strcmp(input, "exit") == 0)
            {
                return;
            }
            else
            {
                strcpy(allinput[index], input);
                putln();
                index++;
            }
        }
        putln();
        use_input();
    }
}

appmain(interpreter)(char **args)
{
    puts("\
=== Tachyon Interpreter v0.1 ===\n\
*     Type 'exit' to quit      *\n\
*  Newline for argument/method *\n\
*    Finish with ';' to run    *\n\
*   Try: puts\\nhi\\nputi\\n123;  *\n\
================================\n");
    get_input();
    return 0;
}