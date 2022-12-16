#include <stdint.h>
#include <stdarg.h>

#include "libs/ports.c"

#include "libs/sys/strings.c"
#include "libs/sys/math.c"

#include "libs/io/output.c"
#include "libs/io/input.c"

#include "libs/disk.c"
#include "libs/sys/kernel.c"

extern kernel_app_t __test_appmain__;
extern kernel_app_t __interpretermain__;

#include "terminal.c"


void main()
{
    systemInit();
    applicationPromote(__test_appmain__, "test");
    applicationPromote(__interpretermain__, "interpreter");
    //putd(123.446);
    enter_terminal();
}