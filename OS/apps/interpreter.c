#include "../libs/sys/extern.c"
#include "../libs/apps/string.h"

#define MAX_LINES 20
#define MAX_WORDS_IN_LINE 20
#define MAX_WORD_LENGTH 20
#define stris(is) strcmp(word, is) == 0
#define sentence allLines[line]
#define nextArg duplicatedLine[wordN + 1]
#define secNextArg duplicatedLine[wordN + 2]
#define argOff(n) duplicatedLine[wordN + n]
#define word duplicatedLine[wordN]
#define replaceWord(src) strcpy((char *)&word, src)

// Array of lines, each containing words split by spaces
char allLines[MAX_LINES][MAX_WORDS_IN_LINE][MAX_WORD_LENGTH];
char duplicatedLine[MAX_WORDS_IN_LINE][MAX_WORD_LENGTH];
char usermem[32][MAX_WORD_LENGTH];

int current_line = 0;
int current_word = 0;

void clearAndMoveDown(int _word)
{
    /*
example index = 0
0  1  2  3  4  5  6  7  8  9
         ^
           <^ <^ <^ <^ <^ <^
    */
    // - 2 because last one should be cleared
    int times = MAX_WORDS_IN_LINE - _word - 2;
    int i = 0;
    for (; i < times; i++)
    {
        strcpy((char*)&duplicatedLine[_word + i + 1], (char*)&duplicatedLine[_word + i + 2]);
    }
    *((char*)duplicatedLine[_word + i + 1]) = 0;
}

void memcpy(char *dest, char *src, int size)
{
    while (size--)
        *(dest++) = *(src++);
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

char *itoa(int val)
{
    // https://stackoverflow.com/questions/3982320/convert-integer-to-string-without-access-to-libraries
    if (val == 0)
        return "0";
    static char buf[32] = {0};
    int i = 30;
    for (; val && i; --i, val /= 10)
        buf[i] = "0123456789abcdef"[val % 10];
    return &buf[i + 1];
}

void use_input()
{
    puts("\n== Running... ==\n");
    for (int line = 0; line < MAX_LINES; line++)
    {
        memcpy((char *)&duplicatedLine, (char *)&sentence, MAX_WORDS_IN_LINE * MAX_WORD_LENGTH);
        for (int wordN = MAX_WORD_LENGTH - 1; wordN >= 0; wordN--)
        {
            if (word[0] != 0)
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
                    char *arg1 = nextArg;
                    char *arg2 = secNextArg;
                    strcpy((char *)&usermem[stoi(arg1)], arg2);
                }
                else if (stris("rcl"))
                {
                    // recall memory in form of
                    // rnum <index>
                    // replaces current word with the value (as a string)
                    replaceWord(usermem[stoi(nextArg)]);
                    clearAndMoveDown(wordN);
                }
                else if (stris("clr"))
                {
                    clrscr();
                }
                else if (stris("add"))
                {
                    replaceWord(itoa(stoi(nextArg) + stoi(secNextArg)));
                }
                else if (stris("sub"))
                {
                    replaceWord(itoa(stoi(nextArg) - stoi(secNextArg)));
                }
                else if (stris("mul"))
                {
                    replaceWord(itoa(stoi(nextArg) * stoi(secNextArg)));
                }
                else if (stris("div"))
                {
                    replaceWord(itoa(stoi(nextArg) / stoi(secNextArg)));
                }
                else if (stris("mwrite"))
                {
                    // store to addres in memory in form of
                    // mwrite <addr> <value>
                    *((uint16_t *)nextArg) = stoi(secNextArg);
                }
                else if (stris("mread"))
                {
                    // read directly from memory in form of
                    // mread <addr> <size>
                    uint16_t buffer[100];
                    uint16_t *addr = (uint16_t *)stoi(nextArg);
                    int n = 0;
                    for (n = 0; n < stoi(secNextArg); n++)
                    {
                        buffer[n] = *(addr + n);
                    }
                    buffer[n] = 0;
                    replaceWord((char *)&buffer);
                }
                else if (stris("goif"))
                {
                    // goif <line> <num> <cmp> <num>
                    // goif 0 5 < 10
                    int jline = stoi(nextArg) - 1;
                    int n1 = stoi(secNextArg);
                    char* cmp = (char*)&argOff(3);
                    int n2 = stoi(argOff(4));
                    if(strcmp(cmp, "eq") == 0)
                    {
                        if(n1 == n2)
                        {
                            wordN = -1;
                            line = jline;
                        }
                    }
                    else if(strcmp(cmp, "gt") == 0)
                    {
                        if(n1 > n2)
                        {
                            wordN = -1;
                            line = jline;
                        }
                    }
                    else if(strcmp(cmp, "lt") == 0)
                    {
                        if(n1 < n2)
                        {
                            wordN = -1;
                            line = jline;
                        }
                    }
                    else if(strcmp(cmp, "le") == 0)
                    {
                        if(n1 <= n2)
                        {
                            wordN = -1;
                            line = jline;
                        }
                    }
                    else if(strcmp(cmp, "ge") == 0)
                    {
                        if(n1 >= n2)
                        {
                            wordN = -1;
                            line = jline;
                        }
                    }
                    else if(strcmp(cmp, "ne") == 0)
                    {
                        if(n1 != n2)
                        {
                            wordN = -1;
                            line = jline;
                        }
                    }
                }
                else if(stris("test"))
                {
                    puts(nextArg);
                    putln();
                    puts(secNextArg);
                }
            }
        }
    }
    puts("===== Done! ====\n");
}

void get_input()
{
    char *input = (char *)__tempmem__;

    while (1)
    {
        char stay = 1;
        current_line = 0;
        current_word = 0;
        strclr((char *)&allLines, 100 * 100);

        while (stay)
        {
            strclr(input, 2048);
            gets(input, 2048);
            char *lastc = &input[strlen(input) - 1];
            if (*lastc == ';')
            {
                if (input[0] != ';') // dont shove into program if only semicolon
                {
                    *lastc = 0; // replace with null term
                    strcpy(allLines[current_line++][current_word++], input);
                }
                current_word = 0;
                putln();
            }
            else if (*lastc == '.') // end of program
            {
                if (input[0] != '.')
                {
                    if (*(lastc - 1) == ';') // you typed ';.'
                        *(lastc - 1) = 0;
                    else // you did not type a semi colon
                        *lastc = 0;
                    strcpy(allLines[current_line][current_word], input);
                }
                stay = 0;
            }
            else if (strcmp(input, "exit") == 0) // exit the program
            {
                return;
            }
            else
            {
                // copy
                strcpy(allLines[current_line][current_word++], input);
                putch(' ');
            }
        }
        use_input();
        return;
    }
}

appmain(interpreter)(char **args)
{
    puts("\
=== Tachyon Interpreter v0.1 ===\n\
*     Type 'exit' to quit      *\n\
*     Enter for next word      *\n\
*    Complete line with ';'    *\n\
*    Finish program with .     *\n\
*        Try: puts hi;.        *\n\
================================\n");
    get_input();
    return 0;
}