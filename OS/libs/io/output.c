#define VRAM 0xb8000

typedef uint16_t * FILEp;
extern FILEp WRITESTREAM;
extern FILEp VGA_STREAM;

FILEp VGA_STREAM = (FILEp) VRAM;
FILEp WRITESTREAM = (FILEp) VRAM;

enum vga_color
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

char vga_color_back = 0;
char vga_color_front = 15;

void putln();
void cursor_set();

// broke something
static inline char fmtvga(char bg, char fg, char ch)
{
    return (bg << 4 | fg) << 8 | ch;
}

void clrscr()
{   if(WRITESTREAM > (FILEp)VRAM && WRITESTREAM < (FILEp) (VRAM + 4000))
    while ((int)WRITESTREAM > VRAM)
        *(WRITESTREAM--) = fmtvga(vga_color_back, vga_color_front, 0);
}

void setScreenBg(char col)
{
    vga_color_back = col;
    uint16_t *i = (uint16_t *)VRAM;
    while (i < (uint16_t *)(VRAM + 2000))
    {
        *i = fmtvga(col, vga_color_front, (char)(*i));
        i++;
    }
}

/*
VGA ram consists of 2000 16bit segments, each holding a character and its highlight

bits 0-3: background highlight
bist 4-7: foreground text color
bits 8-15: character

*/
char putch(char ch)
{
    *(WRITESTREAM++) = (vga_color_back << 4 | vga_color_front) << 8 | ch;
    return ch;
}

/*
Uses mod 10 to get each digit, then converts it to a character to print
*/
void puti(uint32_t number)
{
    //number -= 2058624;
    int len = numLen(number) - 1;
    WRITESTREAM += (uint16_t)len;
    if (number == 0) {
        putch('0');
    }
    else
    {
        while (number >= 1)
        {
            putch((char)(number % 10) + 48);
            number /= 10;
            WRITESTREAM -= 2;
        }
        WRITESTREAM += ((len + 1) * 2) - 2;
    }
}

/*
Prints a sequence of characters until NULL (character 0) is found
*/
void puts(char *str)
{
    int l = 0;
    while (*str != 0)
    {
        if (*str == 10)
            putln();
        else
            putch(*str);
        *(str++);
    }
}

void k_fault(char *error)
{
    vga_color_back = BLUE;
    vga_color_front = WHITE;
    WRITESTREAM = VGA_STREAM;
    puts("\nFatal Error, execution stopped: ");
    puts(error);
    asm("hlt");
}

void verbose_state(uint32_t code, char *str)
{

    WRITESTREAM = VGA_STREAM;
    if (code == 1)
    {
        puts("1 : [FAILIURE] ");
    }
    else if (code == 2)
    {
        puts("2 : [CRITICAL] ");
        puts(str);
        putln();
        k_fault("See Above");
    }
    else
    {
        puti(code);
        puts(" : [SUCCESS]  ");
    }
    puts(str);
    putln();
}

void putd(double number)
{
    int leftHand = (int)number;
    double rightHand = number - leftHand;

    puti(leftHand);
    putch('.');
    puti((int)(rightHand * 1000000));
}

void putln()
{
    int temp = (int)WRITESTREAM - VRAM;
    temp += 160 - (temp % 160);
    if (temp >= 4000)
    {
        clrscr();
    }
    else
    {
        WRITESTREAM = (uint16_t *)(temp + VRAM);
    }
}

void printf(const char *fmt, ...)
{
    va_list vargs;
    va_start(vargs, fmt);

    char cchar;
    while ((cchar = *fmt) != 0)
    {
        if (cchar == '%') // format specifier
        {
            cchar = *(++fmt);
            switch (cchar)
            {
            case 'i':
            {
                puti(va_arg(vargs, uint32_t));
            }
            break;

            case 'f':
            {
                putd(va_arg(vargs, double));
            }
            break;

            case 's':
            {
                puts(va_arg(vargs, char *));
            }
            break;

            case 'c':
            {
                putch(va_arg(vargs, int));
            }
            break;
            }
        }
        else if (cchar == 10)
            putln();
        else
            putch(cchar);
        fmt++;
    }
}

void cursor_set()
{
    uint16_t pos = (int)WRITESTREAM - VRAM;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (char)((pos >> 8) & 0xFF));
}

void cursor_disable()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}