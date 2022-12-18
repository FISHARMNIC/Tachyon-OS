void comm_echo();
void comm_help();
void comm_ata_send_id();
void comm_run_app();

#define commandIs(str) strcmp(comm, str) == 0
#define parse_break(type)                    \
    counter = 0;                             \
    while (*command != ' ' && *command != 0) \
        type[counter++] = *(command++);      \
    if (*command == 0)                       \
        return;                              \
    type[counter] = 0;                       \
    command++

#define term_numCommands 5
static char comm[256];
static char par1[256];
static char par2[256];

#define _i_comm__(c) if (commandIs(c))
#define __ei_comm__(c) else if (commandIs(c))

char term_commands[term_numCommands][15] = {
    "help",
    "identify",
    "echo",
    "clr",
    "run",
};

char inputBuffer[2048];

static void parse_command(char *command)
{
    int counter = 0;
    parse_break(comm);
    parse_break(par1);
    parse_break(par2);
}

void term_run_command(char *command)
{
    strclr(comm, 256);
    strclr(par1, 256);
    strclr(par2, 256);

    parse_command(command);
    _i_comm__("help")
    {
        comm_help();
    }
    __ei_comm__("echo")
    {
        comm_echo();
    }
    __ei_comm__("identify")
    {
        comm_ata_send_id();
    }
    __ei_comm__("clr")
    {
        clrscr();
    }
    __ei_comm__("run")
    {
        comm_run_app();
    }
    else
    {
        printf("Unknown Command '%s'", comm);
    }
}

void enter_terminal()
{
    printf("---Boot Successful---\nEnter 'help' for a list of commands");
    while (1)
    {
        printf("\n> ");
        strclr(inputBuffer, 2048);
        gets(inputBuffer, 2048);
        putln();
        term_run_command(inputBuffer);
    }
}

void comm_echo() {
    puts(par1);
}

void comm_help() {
    for (int i = 0; i < term_numCommands; i++)
        {
            puts(term_commands[i]);
            putln();
        }
}

void comm_ata_send_id()
{
    ata_send_identify();
}

void comm_run_app()
{
    if(strcmp(par1,"help") == 0)
    {
        puts("Heres a list of all applications:\n");
        for(int i = 0; i < APPCALLS_MAX; i++)
        {
            if(appcalls_names[i] == NULL) return;
            printf("* %s\n",appcalls_names[i]);
        }
    }
    kernel_app_t* app = applicationSeek(par1);
    if(app == NULL) {
        printf("Unknown application '%s'\nType 'run help' for a list of applications", par1);
        return;
    }
    (app)(NULL);
}
