#include "../libs/sys/extern.c"
#include "../libs/apps/string.h"

char allinput[10][10];

#define stris(is) strcmp(allinput[i], is) == 0
#define nextArg allinput[++i]

void use_input()
{
    puts("== Running... ==\n");
    for (int i = 0; i < 10; i++)
    {
        if (allinput[i] != 0)
        {
            if (stris("puts"))
            {
                puts("(PUTS) : ");
                puts(nextArg);
                putln();
            }
            else if (stris("puti"))
            {
                // needs to be casted with a stoi function
                // puti(nextArg);
            }
            else if (stris("putch"))
            {
                putch(nextArg[0]);
            }
        }
    }
    puts("==    Done!   ==\n");
}

void get_input()
{
    while (1)
    {
        char *input = (char *)0xb80000;
        char stay = 1;
        int index = 0;
        while (stay)
        {
            strclr(input, 2048);
            gets(input, 2048);
            // putch(*(input + strlen(input) - 1));
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
*  Finish the command with ';' *\n\
* Try: puts\\nhi\\nputs\\nbye;    *\n\
================================\n");
    get_input();
    return 0;
}